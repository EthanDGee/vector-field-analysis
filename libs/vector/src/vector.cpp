#include "vector.h"

namespace Vector {

float Vector::magnitude() const { return std::sqrt(x * x + y * y); }

Vector Vector::unitVector() const {
    const float magnitude = Vector::magnitude();
    return Vector(x / magnitude, y / magnitude);
}
float dotProduct(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }

bool almostParrallel(Vector &a, Vector &b) {

    float x_diff = std::abs(a.x - b.x);
    float y_diff = std::abs(a.y - b.y);

    return x_diff + y_diff <= PARRALEL_THRESHOLD;
};
} // namespace Vector
