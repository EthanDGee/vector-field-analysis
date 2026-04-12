#include "pthreads.hpp"

#include "utils.hpp"

#include <pthread.h>
#include <stdexcept>

namespace pthreads {

void* computeRows(void* arg) {
    auto* data = static_cast<ThreadData*>(arg);
    VectorField::FieldGrid& timeStep = *data->field;
    const std::size_t numCol = timeStep.cols();

    for (std::size_t row = data->startRow; row < data->endRow; row++) {
        for (std::size_t col = 0; col < numCol; col++) {
            timeStep.traceStreamlineStep(static_cast<int>(row), static_cast<int>(col));
        }
    }
    return nullptr;
}

void computeTimeStep(VectorField::FieldGrid& field, const unsigned int threadCount) {
    if (threadCount == 0) {
        return;
    }

    auto splits = utils::calculateRowSplit(field.rows(), threadCount);
    const std::size_t rowsPerThread = splits.first;
    const std::size_t leftOverRows = splits.second;

    std::vector<pthread_t> threads(threadCount);
    std::vector<ThreadData> threadData(threadCount);

    std::size_t currentRow = 0;
    for (unsigned int id = 0; id < threadCount; id++) {
        threadData[id].field = &field;
        threadData[id].startRow = currentRow;

        // Last thread receives leftover rows
        if (id == threadCount - 1) {
            threadData[id].endRow = currentRow + rowsPerThread + leftOverRows;
        } else {
            threadData[id].endRow = currentRow + rowsPerThread;
        }
        currentRow += rowsPerThread;

        const int err = pthread_create(&threads[id], nullptr, computeRows, &threadData[id]);
        if (err != 0) {
            throw std::runtime_error("pthread_create failed with error code " +
                                     std::to_string(err));
        }
    }

    for (unsigned int i = 0; i < threadCount; i++) {
        const int err = pthread_join(threads[i], nullptr);
        if (err != 0) {
            throw std::runtime_error("pthread_join failed with error code " + std::to_string(err));
        }
    }
}

} // namespace pthreads
