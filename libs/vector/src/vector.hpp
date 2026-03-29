#pragma once
#include "streamline.hpp"

#include <memory>

namespace Vector {

inline constexpr float kParallelThreshold = 0.2f;

class Vec2 {
  public:
    float x;
    float y;
    std::shared_ptr<Streamline> stream;

    Vec2(float x, float y)
        : x(x),
          y(y),
          stream(nullptr) {}

    [[nodiscard]] float magnitude() const;

    [[nodiscard]] Vec2 unitVector() const;
};

[[nodiscard]] float dotProduct(const Vec2& a, const Vec2& b);

// Precondition: both vectors must be near-unit. This compares component-wise
// difference, not direction - non-unit inputs give unreliable results.
[[nodiscard]] bool almostParallel(const Vec2& a, const Vec2& b);

} // namespace Vector
