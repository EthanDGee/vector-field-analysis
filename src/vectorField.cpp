#include "vectorField.h"
#include "streamLine.h"
#include <cmath>
#include <utility>

namespace VectorField {

Vector::Vector VectorField::lookUp(int x, int y) { return field[x][y]; }

std::pair<int, int> VectorField::pointsTo(int x, int y) {
    Vector::Vector start = field[x][y];

    // find the nearest coordinate that the vector points to
    int nearestX = static_cast<int>(std::round(x + start.x));
    int nearestY = static_cast<int>(std::round(y + start.y));

    return {nearestX, nearestY};
}

void VectorField::mergeStreamLines(StreamLine::StreamLine *start,
                                   StreamLine::StreamLine *end) {
    // add tail to head
    start->path.insert(start->path.end(), end->path.begin(), end->path.end());

    // update stream pointers accordingly
    for (auto &point : end->path) {
        streams[point.first][point.second] = start;
    }

    // remove redundant end
    delete end;
}

void VectorField::flowFromVector(Vector::Vector &vector) {
    std::pair<int, int> destination = pointsTo(vector.x, vector.y);

    if (field[destination.first()][destination.second()].stream == nullptr)
        field[vector.x][vector.y].stream =
            std::make_shared<StreamLine::StreamLine>(destination.first,
                                                     destination.second);
}

// void VectorField::calculateRegionalStreamLine(Region region) {}
} // namespace VectorField
