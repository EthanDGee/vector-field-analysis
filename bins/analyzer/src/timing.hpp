#pragma once

#include <chrono>
#include <cstdint>
#include <iostream>
#include <optional>

inline int64_t getCurrentTimeMs() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
}

inline void printTiming(const char* message, std::optional<int64_t> lastTime = std::nullopt) {
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
