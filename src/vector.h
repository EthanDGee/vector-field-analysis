#include <cmath>

#pragma once
namespace Vector {
class Vector {
  public:
    float x;
    float y;

    Vector(float x, float y) { Vector{x, y}; };

    float magnitude();

    Vector unitVector();

    float dotProduct(Vector a, Vector b);
};
} // namespace Vector
