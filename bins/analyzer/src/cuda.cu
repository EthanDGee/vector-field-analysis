#include "cuda.hpp"

#include <cuda_runtime.h>

#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

namespace cuda {
  namespace {
    // 2D vector representation
    // host is flattened into this format before being copied to GPU
    struct DeviceVec2 {
      float x;
      float y;
    };

    // destination coord for one cell
    struct DeviceCoord {
      int row;
      int col;
    }
    
    // helper to turn cuda errors into cpp exceptions
    inline void cudaCheck(cudaError_t err, const char* what) {
      if (err != cudaSuccess) {
        throw std::runtime_error(std::string(what) + ": " + cudaGetErrorString(err));
      }
    }

    // clamp header for device code
    __device__ int clampInt(int value, int lo, int hi) {
      return value < lo ? lo : (value > hi ? hi : value);
    }

    // for each grid cell compute which neighboring cell its vector points to 
    // kernel only computes destination coords
    // does not update streamline objects directly
    __global__ void computeDestinationsKernel(const DeviceVec2* field, 
                                              int rows, 
                                              int cols, 
                                              float xMin, 
                                              float xMax, 
                                              float yMin, 
                                              float yMax,
                                              DeviceCoord* dests) {
      const int idx = blockIdx.x * blockDim.x + threadIdx.x;
      const int total = rows * cols;

      if (idx >= total) {
        return;
      }

      const int row = idx / cols;
      const int col = idx % cols;

      const DeviceVec2 v = field[idx];

      int destRow = row;
      int destCol = col;

      if (rows > 1) {
        const float rowSpacing = (yMax - yMin) / static_cast<float>(rows - 1);
        destRow = clampInt(static_cast<int>(roundf(((static_cast<float>(row) * rowSpacing) + v.y) /
                                                   rowSpacing)),
                           0, rows - 1);
      }

      if (cols > 1) {
        const float colSpacing = (xMax - xMin) / static_cast<float>(cols - 1);
        destCol = clampInt(static_cast<int>(roundf(((static_cast<float>(col) * colSpacing) + v.x) /
                                                   colSpacing)),
                           0, cols - 1);
      }

      dests[idx] = DeviceCoord{destRow, destCol};
    }
  }

  void computeTimeStep(VectorField::FieldGrid& grid) {
    const int rows = static_cast<int>(grid.field.size());
    if (rows == 0) {
      return;
    }

    const int cols = static_cast<int>(grid.field[0].size());
    if (cols == 0) {
      return;
    }

    const int total = rows * cols;

    // flatten 2D field into 1D array
    std::vector<DeviceVec2> hostField(static_cast<std::size_t>(total));
    for (int row = 0; row < rows; ++row) {
      for (int col = 0; col < cols; ++col) {
        const auto& v = grid.field[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)];
        hostField[static_cast<std::size_t>(row * cols + col)] = DeviceVec2{v.x, v.y};
      }
    }

    DeviceVec2* dField = nullptr;
    DeviceCoord* dDests = nullptr;

    cudaCheck(cudaMalloc(reinterpret_cast<void**>(&dField), 
                         sizeof(DeviceVec2) * static_cast<std::size_t>(total)),
              "cudaMalloc(dField)");
    cudaCheck(cudaMalloc(reinterpret_cast<void**>(&dDests), 
                         sizeof(DeviceCoord) * static_cast<std::size_t>(total)),
              "cudaMalloc(dDests)");

    cudaCheck(cudaMemcpy(dField,
                         hostField.data(),
                         sizeof(DeviceVec2) * static_cast<std::size_t>(total),
                         cudaMemcpyHostToDevice),
              "cudaMemcpy H2D field");

    constexpr int blockSize = 256;
    const int gridSize = (total + blockSize - 1) / blockSize;

    computeDestinationsKernel<<<gridSize, blockSize>>>(
        dField, rows, cols, 
        grid.getXMin(),
        grid.getXMax(),
        grid.getYMin(),
        grid.getYMax(),
        dDests);

    cudaCheck(cudaGetLastError(), "kernel launch");
    cudaCheck(cudaDeviceSynchronize(), "cudaDeviceSynchronize");

    std::vector<DeviceCoord> hostDests(static_cast<std::size_t>(total));
    cudaCheck(cudaMemcpy(hostDests.data(),
                         dDests,
                         sizeof(DeviceCoord) * static_cast<std::size_t>(total),
                         cudaMemcpyDeviceToHost),
              "cudaMemcpy D2H dests");

    cudaFree(dField);
    cudaFree(dDests);

    // apply already computed destinations on CPU in same row-major order as sequential version
    // so that streamline creation/merging semantics are consistent with host implementation
    for (int row = 0; row < rows; ++row) {
      for (int col = 0; col < cols; ++col) {
        const auto& dest = hostDests[static_cast<std::size_t>(row * cols + col)];
        grid.traceStreamlineStepTo(row, col, dest.row, dest.col);
      }
    }
  }
}
