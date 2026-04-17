#include "cudaFull.hpp"
#include "cudaFullStreamlineSolver.hpp"

void CudaFullStreamlineSolver::computeTimeStep(Field::Grid& grid) {
    const auto result = cudaFull::computeComponents(grid.field(), grid.bounds(), m_blockSize);
    auto paths = cudaFull::reconstructPaths(result);
    grid.setPrecomputedStreamlines(std::move(paths));
}
