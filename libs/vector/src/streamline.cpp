#include "streamline.hpp"

namespace Vector {

Streamline::Streamline(std::pair<int, int> startPoint) {
    path.push_back(startPoint);
}

} // namespace Vector
