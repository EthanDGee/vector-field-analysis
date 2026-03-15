#include "vector.h"
namespace Vector {

float Vector::magnitude() { return std::sqrt(x * x + y * y); }

Vector Vector::unitVector() {
    const float magnitude = Vector::magnitude();
    return Vector(x / magnitude, y / magnitude);
}
float dotProduct(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }

} // namespace Vector
