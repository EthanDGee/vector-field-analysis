#include "sequentialCPU.hpp"

void SequentialCPU::computeTimeStep(VectorField::FieldGrid& grid) {
    const std::size_t numRow = grid.rows();
    if (numRow == 0) {
        return;
    }
    const std::size_t numCol = grid.cols();
    if (numCol == 0) {
        return;
    }

    for (std::size_t row = 0; row < numRow; row++) {
        for (std::size_t col = 0; col < numCol; col++) {
            grid.traceStreamlineStep(static_cast<int>(row), static_cast<int>(col));
        }
    }
}
