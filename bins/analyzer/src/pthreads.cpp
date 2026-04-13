#include "pthreads.hpp"

#include <pthread.h>
#include <stdexcept>
#include <utility>
#include <vector>

namespace {

std::pair<std::size_t, std::size_t> calculateRowSplit(std::size_t rowCount, std::size_t splits) {
    if (splits == 0) {
        throw std::invalid_argument("splits must be greater than 0");
    }
    return {rowCount / splits, rowCount % splits};
}

struct ThreadData {
    const VectorField::FieldGrid* grid;
    std::pair<int, int>* neighbors;
    int colCount;
    std::size_t startRow;
    std::size_t endRow;
};

// Pass 1 worker: reads neighbor directions for an assigned row range.
// neighborInVectorDirection is const and reads no shared mutable state, so
// concurrent calls across disjoint row ranges are race-free.
void* computeNeighbors(void* arg) {
    auto* data = static_cast<ThreadData*>(arg);
    for (std::size_t row = data->startRow; row < data->endRow; row++) {
        for (int col = 0; col < data->colCount; col++) {
            data->neighbors[(row * static_cast<std::size_t>(data->colCount)) +
                            static_cast<std::size_t>(col)] =
                data->grid->neighborInVectorDirection(static_cast<int>(row), col);
        }
    }
    return nullptr;
}

} // namespace

Pthreads::Pthreads(unsigned int threadCount)
    : threadCount_(threadCount) {}

void Pthreads::computeTimeStep(VectorField::FieldGrid& grid) {
    if (threadCount_ == 0) {
        return;
    }

    const std::size_t rowCount = grid.rows();
    if (rowCount == 0) {
        return;
    }
    const int colCount = static_cast<int>(grid.cols());

    // Pass 1: parallel — compute all (src, dest) neighbor pairs.
    std::vector<std::pair<int, int>> neighbors(rowCount * static_cast<std::size_t>(colCount));

    auto splits = calculateRowSplit(rowCount, threadCount_);
    const std::size_t rowsPerThread = splits.first;
    const std::size_t leftOverRows = splits.second;

    std::vector<pthread_t> threads(threadCount_);
    std::vector<ThreadData> threadData(threadCount_);

    std::size_t threadsLaunched = 0;
    std::size_t currentRow = 0;
    for (unsigned int id = 0; id < threadCount_; id++) {
        threadData[id].grid = &grid;
        threadData[id].neighbors = neighbors.data();
        threadData[id].colCount = colCount;
        threadData[id].startRow = currentRow;

        // Last thread receives leftover rows
        if (id == threadCount_ - 1) {
            threadData[id].endRow = currentRow + rowsPerThread + leftOverRows;
        } else {
            threadData[id].endRow = currentRow + rowsPerThread;
        }
        currentRow += rowsPerThread;

        const int err = pthread_create(&threads[id], nullptr, computeNeighbors, &threadData[id]);
        if (err != 0) {
            // Join all already-running threads before propagating the error so
            // they don't outlive threadData and neighbors.
            for (std::size_t j = 0; j < threadsLaunched; j++) {
                pthread_join(threads[j], nullptr);
            }
            throw std::runtime_error("pthread_create failed with error code " +
                                     std::to_string(err));
        }
        ++threadsLaunched;
    }

    for (unsigned int i = 0; i < threadCount_; i++) {
        const int err = pthread_join(threads[i], nullptr);
        if (err != 0) {
            throw std::runtime_error("pthread_join failed with error code " + std::to_string(err));
        }
    }

    // Pass 2: sequential — apply streamline merges using the precomputed pairs.
    // traceStreamlineStep writes to streams_ and is not thread-safe.
    for (std::size_t row = 0; row < rowCount; row++) {
        for (int col = 0; col < colCount; col++) {
            grid.traceStreamlineStep({static_cast<int>(row), col},
                                     neighbors[(row * static_cast<std::size_t>(colCount)) +
                                               static_cast<std::size_t>(col)]);
        }
    }
}
