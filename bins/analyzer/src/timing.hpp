#pragma once

#include <cstdint>
#include <optional>

int64_t getCurrentTimeMs();
void printTiming(const char* message, std::optional<int64_t> lastTime = std::nullopt);
