#include "vectorField.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <unordered_set>

namespace VectorField {

Vector::GridCell FieldGrid::downstreamCell(int row, int col) const {
    const int rows = static_cast<int>(field_.size());
    if (rows == 0) {
        throw std::runtime_error("downstreamCell called on empty field");
    }
    const int cols = static_cast<int>(field_[0].size());
    if (cols == 0) {
        throw std::runtime_error("downstreamCell called on zero-width field");
    }
    if (rows == 1 || cols == 1) {
        // A 1-cell grid has no downstream direction; return the cell itself.
        return {row, col};
    }

    const Vector::Vec2 start = field_[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)];

    const float rowSpacing = (bounds_.yMax - bounds_.yMin) / static_cast<float>(rows - 1);
    const float colSpacing = (bounds_.xMax - bounds_.xMin) / static_cast<float>(cols - 1);

    // Advance one step in the vector direction, then snap to the nearest grid
    // index. Clamped to valid index bounds so boundary vectors don't reference
    // off-grid cells.
    const float physRow = Vector::gridToWorld(row, rows, bounds_.yMin, bounds_.yMax);
    const float physCol = Vector::gridToWorld(col, cols, bounds_.xMin, bounds_.xMax);
    const int nearestRow =
        std::clamp(static_cast<int>(std::round((physRow + start.y - bounds_.yMin) / rowSpacing)),
                   0, rows - 1);
    const int nearestCol =
        std::clamp(static_cast<int>(std::round((physCol + start.x - bounds_.xMin) / colSpacing)),
                   0, cols - 1);

    return {nearestRow, nearestCol};
}

Vector::GridCell FieldGrid::downstreamCell(Vector::GridCell coords) const {
    return downstreamCell(coords.row, coords.col);
}

void FieldGrid::joinStreamlines(const std::shared_ptr<Vector::Streamline>& start,
                                const std::shared_ptr<Vector::Streamline>& end) {
    if (!start || !end || start == end || start->path.empty()) {
        return;
    }

    // Absorb end's path into start and redirect all stream entries at those positions
    for (const auto& point : end->path) {
        start->path.push_back(point);
        streams_[static_cast<std::size_t>(point.row)][static_cast<std::size_t>(point.col)] = start;
    }
}

// Greedy one-step forward trace: extend src's streamline to dest, or merge the
// two streamlines if dest is already claimed. Not thread-safe -- callers are
// responsible for calling this sequentially (see downstreamCell for
// the parallel-safe read step).
void FieldGrid::traceStreamlineStep(Vector::GridCell src, Vector::GridCell dest) {
    const auto r = static_cast<std::size_t>(streams_.size());
    const auto c = r > 0 ? streams_[0].size() : 0;
    if (static_cast<std::size_t>(src.row) >= r || static_cast<std::size_t>(src.col) >= c ||
        static_cast<std::size_t>(dest.row) >= r || static_cast<std::size_t>(dest.col) >= c) {
        throw std::out_of_range("traceStreamlineStep: cell coordinates out of grid bounds");
    }

    auto& srcStream =
        streams_[static_cast<std::size_t>(src.row)][static_cast<std::size_t>(src.col)];
    if (srcStream == nullptr) {
        srcStream = std::make_shared<Vector::Streamline>(src);
    }

    auto& destStream =
        streams_[static_cast<std::size_t>(dest.row)][static_cast<std::size_t>(dest.col)];
    if (destStream == nullptr) {
        // Destination is unclaimed: extend the source's streamline into it.
        destStream = srcStream;
        srcStream->path.push_back(dest);
    } else {
        // Destination already belongs to another streamline: the two lines
        // converge here, so merge them into one.
        joinStreamlines(destStream, srcStream);
    }
}

std::vector<Vector::Path> FieldGrid::getStreamlines() const {
    std::unordered_set<Vector::Streamline*> seen;
    std::vector<Vector::Path> result;
    for (const auto& row : streams_) {
        for (const auto& cell : row) {
            if (cell && seen.insert(cell.get()).second) {
                result.push_back(cell->path);
            }
        }
    }
    return result;
}

} // namespace VectorField
