#pragma once

#include "fieldTypes.hpp"

#include <vector>

namespace cuda {

// GPU-native result for one analyzed field slice
// componentId[idx]: dense connected-component / streamline label for cell idx
struct Result {
    int rows = 0;
    int cols = 0;
    std::vector<int> componentId;
};

// Computes streamline connectivity entirely on the GPU.
// rowSpacing/colSpacing must be the precomputed Grid::rowSpacing()/colSpacing()
// values so the GPU successor kernel uses the same formula as Grid::downstreamCell.
Result computeComponents(const std::vector<Vector::Vec2>& field, int rows, int cols,
                         float rowSpacing, float colSpacing, unsigned int blockSize = 256);

// Reconstructs deterministic host-side paths from the GPU-native result
std::vector<Field::Path> reconstructPaths(const Result& result);

} // namespace cuda
