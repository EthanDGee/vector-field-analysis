#include "streamlineSolver.hpp"

#include <cstddef>
#include <vector>

std::vector<Field::Path>
StreamlineSolver::reconstructPathsDSU(const Field::Grid& grid,
                                      const std::vector<Field::GridCell>& neighbors) {

    const std::size_t total = neighbors.size();
    if (total == 0) {
        return {};
    }

    const int colCount = static_cast<int>(grid.cols());

    // 1. Compute roots for all cells.
    std::vector<std::size_t> roots(total);
    for (std::size_t i = 0; i < total; ++i) {
        roots[i] = grid.findRoot(i);
    }

    // 2. Count cells per root (O(n)).
    std::vector<std::size_t> counts(total, 0);
    for (std::size_t i = 0; i < total; ++i) {
        counts[roots[i]]++;
    }

    // 3. Compute write offsets via prefix sum (O(n)).
    std::vector<std::size_t> offsets(total + 1, 0);
    for (std::size_t i = 0; i < total; ++i) {
        offsets[i + 1] = offsets[i] + counts[i];
    }

    // 4. Scatter cells into a flat buffer grouped by root (O(n)).
    std::vector<Field::GridCell> buf(total);
    std::vector<std::size_t> writePos = offsets;
    for (std::size_t i = 0; i < total; ++i) {
        buf[writePos[roots[i]]++] = {static_cast<int>(i / colCount),
                                     static_cast<int>(i % colCount)};
    }

    // 5. Slice buffer into paths — one contiguous segment per non-empty root (O(n)).
    std::vector<Field::Path> output;
    for (std::size_t r = 0; r < total; ++r) {
        if (counts[r] > 0) {
            output.emplace_back(buf.begin() + static_cast<std::ptrdiff_t>(offsets[r]),
                                buf.begin() + static_cast<std::ptrdiff_t>(offsets[r] + counts[r]));
        }
    }

    return output;
}
