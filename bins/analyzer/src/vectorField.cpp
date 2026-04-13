#include "vectorField.hpp"

#include "vector.hpp"

#include <algorithm>
#include <cmath>
#include <ctime>
#include <utility>

namespace VectorField {

std::pair<int, int> FieldGrid::neighborInVectorDirection(int row, int col) {
    const Vector::Vec2 start = field[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)];

    const float rowSpacing = (yMax - yMin) / static_cast<float>(field.size() - 1);
    const float colSpacing = (xMax - xMin) / static_cast<float>(field[0].size() - 1);

    // Advance one step in the vector direction, then snap to the nearest grid index.
    // Clamped to valid index bounds so boundary vectors don't reference off-grid cells.
    const int nearestRow =
        std::clamp(static_cast<int>(
                       std::round(((static_cast<float>(row) * rowSpacing) + start.y) / rowSpacing)),
                   0, static_cast<int>(field.size()) - 1);
    const int nearestCol =
        std::clamp(static_cast<int>(
                       std::round(((static_cast<float>(col) * colSpacing) + start.x) / colSpacing)),
                   0, static_cast<int>(field[0].size()) - 1);

    return {nearestRow, nearestCol};
}

std::pair<int, int> FieldGrid::neighborInVectorDirection(std::pair<int, int> coords) {
    return neighborInVectorDirection(coords.first, coords.second);
}

void FieldGrid::joinStreamlines(const std::shared_ptr<Vector::Streamline>& start,
                                const std::shared_ptr<Vector::Streamline>& end) {
    if (!start || !end || start == end || start->path.empty()) {
        return;
    }

    // Absorb end's path into start and redirect all field vectors at those positions
    for (const auto& point : end->path) {
        start->path.push_back(point);
        field[static_cast<std::size_t>(point.first)][static_cast<std::size_t>(point.second)]
            .stream = start;
    }
}

// applies one tracing step when destination cell is already known
// traceStreamlineStep() did two jobs:
//  1) compute which neighboring cell the current vector points to
//  2) update/merge streamline ownership for source and dest cells
// for CPU/OpenMP/etc, both steps can still happen together
// for CUDA the GPU should do step one in parallel, then reuse the 
// existing host side streamline mutation logic for the second step
void FieldGrid::traceStreamlineStepTo(std::pair<int, int> startCoords,
                                      std::pair<int, int> destCoords) {
  // streamline currently associated with starting cell
  auto& srcStream = streams_[static_cast<std::size_t>(startCoords.first)]
                            [static_cast<std::size_t>(startCoords.second)];

  // if start cell doesn't already belong to a streamline:
  // create one at this start position
  if (srcStream == nullptr) {
    srcStream = std::make_shared<Vector::Streamline>(startCoords);
  }

  // streamline currently associated with destination cell
  auto& destStream = streams_[static_cast<std::size_t>(destCoords.first)]
                             [static_cast<std::size_t>(destCoords.second)];

  if (destStream == nullptr) {
        // Destination is unclaimed
        // extend the source streamline into that cell and mark the destination
        // as beloinging to the same streamline object
        destStream = srcStream;
        srcStream->path.push_back(destCoords);
    } else {
        // Destination already belongs to another streamline:
        // merge the source streamline into the destination streamline 
        // preserves existing behavior from traceStreamlineStep()
      joinStreamlines(destStream, srcStream);
    }
}

// original public api is unchanged for sequential, openMP, etc callers
// still computes destination from the vector field then applies the same streamline logic as before
void FieldGrid::traceStreamlineStep(std::pair<int, int> startCoords) {
  traceStreamlineStepTo(startCoords, neighborInVectorDirection(startCoords));
}

} // namespace VectorField
