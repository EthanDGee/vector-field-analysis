#include "sequentialCPU.hpp"

#include <ctime>
namespace sequentialCPU {

void computeTimeStep(VectorField::FieldGrid& timeStep) {

    const unsigned long numRow = timeStep.field.size();
    const unsigned long numCol = timeStep.field[0].size();

    for (unsigned long row = 0; row < numRow; row++) {
        for (unsigned long col = 0; col < numCol; col++) {

            timeStep.traceStreamlineStep((int)row, (int)col);
        }
    }
}

} // namespace sequentialCPU
