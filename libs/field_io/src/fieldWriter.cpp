#include "fieldWriter.hpp"

#include <highfive/highfive.hpp>
#include <stdexcept>
#include <string>
#include <vector>

namespace FieldWriter {

void write(const std::string& path, const Vector::FieldTimeSeries& field,
           const FieldWriteMetadata& meta) {
    const auto [width, height] = field.gridSize();
    if (field.steps.empty() || width == 0 || height == 0) {
        throw std::runtime_error("Cannot write empty field to: " + path);
    }

    HighFive::File file(path, HighFive::File::Overwrite);
    auto group = file.createGroup("field");

    // HDF5 requires flat numeric arrays; extract x/y components from Vec2.
    using RawFieldData = std::vector<std::vector<std::vector<float>>>; // [step][row][col]
    const std::size_t numSteps = field.steps.size();
    const auto h = static_cast<std::size_t>(height);
    const auto w = static_cast<std::size_t>(width);
    RawFieldData vx(numSteps, std::vector<std::vector<float>>(h, std::vector<float>(w)));
    RawFieldData vy(numSteps, std::vector<std::vector<float>>(h, std::vector<float>(w)));
    for (std::size_t s = 0; s < numSteps; ++s) {
        for (std::size_t r = 0; r < h; ++r) {
            for (std::size_t c = 0; c < w; ++c) {
                vx[s][r][c] = field.steps[s][r][c].x;
                vy[s][r][c] = field.steps[s][r][c].y;
            }
        }
    }
    group.createDataSet("vx", vx);
    group.createDataSet("vy", vy);

    // Store grid geometry and simulation parameters as HDF5 attributes alongside
    // the data so the file is self-contained -- readers don't need the config file.
    group.createAttribute("type", meta.typeLabel);
    group.createAttribute("steps", static_cast<int>(numSteps));
    group.createAttribute("dt", meta.dt);
    group.createAttribute("viscosity", meta.viscosity);
    group.createAttribute("width", width);
    group.createAttribute("height", height);
    group.createAttribute("xMin", field.bounds.xMin);
    group.createAttribute("xMax", field.bounds.xMax);
    group.createAttribute("yMin", field.bounds.yMin);
    group.createAttribute("yMax", field.bounds.yMax);
}

} // namespace FieldWriter
