#include "grid.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <unordered_set>

namespace Field {

// initialize all vectors to start out as their own successors
void Grid::initializeSuccessors() {
    const int rowCount = static_cast<int>(field_.size());
    if (rowCount == 0) {
        throw std::runtime_error("Can't properly initialize empty field");
    }
    const int colCount = static_cast<int>(field_[0].size());
    if (colCount == 0) {
        throw std::runtime_error("Can't properly initialize zero-width field");
    }

    successor.assign(static_cast<std::size_t>(rowCount),
                     std::vector<std::size_t>(static_cast<std::size_t>(colCount)));

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            successor[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)] =
                coordsToIndex(static_cast<std::size_t>(i), static_cast<std::size_t>(j));
        }
    }
}

// converts a given coordinate into a unique index so that it can be looked up in a disjoint set
std::size_t Grid::coordsToIndex(std::size_t row, std::size_t col) {
    const std::size_t colCount = field_.empty() ? 0 : field_[0].size();
    return (row * colCount) + col;
}

GridCell Grid::downstreamCell(int row, int col) const {
    const int rowCount = static_cast<int>(field_.size());
    if (rowCount == 0) {
        throw std::runtime_error("downstreamCell called on empty field");
    }
    const int colCount = static_cast<int>(field_[0].size());
    if (colCount == 0) {
        throw std::runtime_error("downstreamCell called on zero-width field");
    }
    if (rowCount == 1 || colCount == 1) {
        // A single-row or single-column grid cannot advance in that dimension; return the cell
        // itself.
        return {row, col};
    }

    const Vector::Vec2 start = field_[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)];

    const float rowSpacing = (bounds_.yMax - bounds_.yMin) / static_cast<float>(rowCount - 1);
    const float colSpacing = (bounds_.xMax - bounds_.xMin) / static_cast<float>(colCount - 1);

    // Advance one step in the vector direction, then snap to the nearest grid
    // index. Clamped to valid index bounds so boundary vectors don't reference
    // off-grid cells.
    const float physRow = indexToCoord(row, rowCount, bounds_.yMin, bounds_.yMax);
    const float physCol = indexToCoord(col, colCount, bounds_.xMin, bounds_.xMax);
    const int nearestRow =
        std::clamp(static_cast<int>(std::round((physRow + start.y - bounds_.yMin) / rowSpacing)), 0,
                   rowCount - 1);
    const int nearestCol =
        std::clamp(static_cast<int>(std::round((physCol + start.x - bounds_.xMin) / colSpacing)), 0,
                   colCount - 1);

    return {nearestRow, nearestCol};
}

GridCell Grid::downstreamCell(GridCell coords) const {
    return downstreamCell(coords.row, coords.col);
}

void Grid::joinStreamlines(std::shared_ptr<Streamline> start,
                           std::shared_ptr<Streamline> end) {
    if (!start || !end) {
        return;
    }

    auto rootStart = start->resolve();
    auto rootEnd = end->resolve();

    if (rootStart == rootEnd || rootEnd->getPath().empty()) {
        return;
    }

    // O(1) merge: transfers the entire list from end to start.
    rootStart->absorb(*rootEnd);
    rootEnd->parent = rootStart;
}

// Greedy one-step forward trace: extend src's streamline to dest, or merge the
// two streamlines if dest is already claimed. Not thread-safe -- callers are
// responsible for calling this sequentially (see downstreamCell for
// the parallel-safe read step).
void Grid::traceStreamlineStep(GridCell src, GridCell dest) {
    const auto gridRowCount = static_cast<std::size_t>(streamlines_.size());
    const auto gridColCount = gridRowCount > 0 ? streamlines_[0].size() : 0;
    if (static_cast<std::size_t>(src.row) >= gridRowCount ||
        static_cast<std::size_t>(src.col) >= gridColCount ||
        static_cast<std::size_t>(dest.row) >= gridRowCount ||
        static_cast<std::size_t>(dest.col) >= gridColCount) {
        throw std::out_of_range("traceStreamlineStep: cell coordinates out of grid bounds");
    }

    auto& srcSlot =
        streamlines_[static_cast<std::size_t>(src.row)][static_cast<std::size_t>(src.col)];
    if (srcSlot == nullptr) {
        srcSlot = std::make_shared<Streamline>(src);
    }
    auto srcStream = srcSlot->resolve();

    auto& destSlot =
        streamlines_[static_cast<std::size_t>(dest.row)][static_cast<std::size_t>(dest.col)];
    if (destSlot == nullptr) {
        // Destination is unclaimed: extend the source's streamline into it.
        destSlot = srcStream;
        srcStream->appendPoint(dest);
    } else {
        // Destination already belongs to another streamline: the two lines
        // converge here, so merge them into one.
        joinStreamlines(srcStream, destSlot);
    }
}

std::vector<Path> Grid::getStreamlines() const {
    if (hasPrecomputedStreamlines_) {
        return precomputedStreamlines_;
    }

    std::unordered_set<Streamline*> seen;
    std::vector<Path> result;
    for (const auto& row : streamlines_) {
        for (const auto& cell : row) {
            if (cell) {
                auto root = cell->resolve();
                if (!root->getPath().empty() && seen.insert(root.get()).second) {
                    result.push_back(root->getPath());
                }
            }
        }
    }
    return result;
}

} // namespace Field
