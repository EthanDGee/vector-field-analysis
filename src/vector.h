#include "streamLine.h"
#include <cmath>
#include <cstddef>
#include <memory>

#pragma namespace
#define PARRALEL_THRESHOLD 0.2

namespace Vector {

class Vector {
  public:
    float x;
    float y;
    std::shared_ptr<StreamLine::StreamLine> stream;

    Vector(float x, float y) : x(x), y(y), stream(nullptr) {};

    float magnitude();

    Vector unitVector();

    float dotProduct(Vector a, Vector b);

    bool almostParralel(Vector &a, Vector &b);
};
} // namespace Vector
