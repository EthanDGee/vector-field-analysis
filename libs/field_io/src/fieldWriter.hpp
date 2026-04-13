#pragma once
#include "vector.hpp"

#include <string>

namespace FieldWriter {

struct FieldWriteMetadata {
    std::string typeLabel;
    float dt        = 0.0f;
    float viscosity = 0.0f;
};

void write(const std::string& path, const Vector::FieldTimeSeries& field,
           const FieldWriteMetadata& meta);

} // namespace FieldWriter
