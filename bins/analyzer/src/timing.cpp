#include "timing.hpp"

#include <chrono>
#include <iostream>

int64_t getCurrentTimeMs() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
}

void printTiming(const char* message, std::optional<int64_t> lastTime) {
    std::cout << message << " - ";
    auto currentTime = getCurrentTimeMs();
    std::cout << currentTime / 60000 << ":" << (currentTime / 1000) % 60 << ":"
              << currentTime % 1000;
    if (lastTime.has_value()) {
        auto elapsed = currentTime - lastTime.value();
        std::cout << " - " << elapsed << "ms";
    }
    std::cout << "\n";
}
