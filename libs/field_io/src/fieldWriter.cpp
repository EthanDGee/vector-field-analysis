#include "fieldWriter.hpp"

#include "fieldIoCommon.hpp"

#include <highfive/highfive.hpp>
#include <stdexcept>
#include <string>
#include <vector>

namespace FieldWriter {

void write(const std::string& path, const Field::TimeSeries& field, const std::string& typeLabel,
           float dt, float viscosity) {
    const Field::GridSize gridSize = field.gridSize();
    if (field.frames.empty() || gridSize.width == 0 || gridSize.height == 0) {
        throw std::runtime_error("Cannot write empty field to: " + path);
    }

    HighFive::File file(path, HighFive::File::Overwrite);
    auto group = file.createGroup("field");

    // HDF5 requires flat numeric arrays; extract x/y components from Vec2.
    const std::size_t numFrames = field.frames.size();
    const auto numRows = static_cast<std::size_t>(gridSize.height);
    const auto numCols = static_cast<std::size_t>(gridSize.width);
    RawFieldData vx(numFrames,
                    std::vector<std::vector<float>>(numRows, std::vector<float>(numCols)));
    RawFieldData vy(numFrames,
                    std::vector<std::vector<float>>(numRows, std::vector<float>(numCols)));
    for (std::size_t frameIndex = 0; frameIndex < numFrames; ++frameIndex) {
        for (std::size_t rowIndex = 0; rowIndex < numRows; ++rowIndex) {
            for (std::size_t colIndex = 0; colIndex < numCols; ++colIndex) {
                vx[frameIndex][rowIndex][colIndex] = field.frames[frameIndex][rowIndex][colIndex].x;
                vy[frameIndex][rowIndex][colIndex] = field.frames[frameIndex][rowIndex][colIndex].y;
            }
        }
    }
    group.createDataSet("vx", vx);
    group.createDataSet("vy", vy);

    // Store grid geometry and simulation parameters as HDF5 attributes alongside
    // the data so the file is self-contained -- readers don't need the config file.
    group.createAttribute("type", typeLabel);
    group.createAttribute("steps", static_cast<int>(numFrames));
    group.createAttribute("dt", dt);
    group.createAttribute("viscosity", viscosity);
    writeGeometryAttributes(group, field.bounds, gridSize);
}

StreamingWriter::StreamingWriter(const std::string& path, const Field::Bounds& bounds,
                                 const Field::GridSize& gridSize, std::size_t numFrames,
                                 const std::string& typeLabel, float dt, float viscosity)
    : file_(path, HighFive::File::Overwrite),
      vxDs_(std::nullopt),
      vyDs_(std::nullopt),
      numRows_(static_cast<std::size_t>(gridSize.height)),
      numCols_(static_cast<std::size_t>(gridSize.width)) {
    auto group = file_.createGroup("field");

    HighFive::DataSpace space({numFrames, numRows_, numCols_});
    vxDs_.emplace(group.createDataSet<float>("vx", space));
    vyDs_.emplace(group.createDataSet<float>("vy", space));

    group.createAttribute("type", typeLabel);
    group.createAttribute("steps", static_cast<int>(numFrames));
    group.createAttribute("dt", dt);
    group.createAttribute("viscosity", viscosity);
    writeGeometryAttributes(group, bounds, gridSize);
}

void StreamingWriter::writeFrame(std::size_t frameIndex, const Field::Slice& frame) {
    // Wrap in an outer dimension so the data rank matches the 3-D file dataset.
    std::vector<std::vector<std::vector<float>>> vxBuf(
        1, std::vector<std::vector<float>>(numRows_, std::vector<float>(numCols_)));
    std::vector<std::vector<std::vector<float>>> vyBuf(
        1, std::vector<std::vector<float>>(numRows_, std::vector<float>(numCols_)));

    for (std::size_t row = 0; row < numRows_; ++row) {
        for (std::size_t col = 0; col < numCols_; ++col) {
            vxBuf[0][row][col] = frame[row][col].x;
            vyBuf[0][row][col] = frame[row][col].y;
        }
    }

    vxDs_->select({frameIndex, 0, 0}, {1, numRows_, numCols_}).write(vxBuf);
    vyDs_->select({frameIndex, 0, 0}, {1, numRows_, numCols_}).write(vyBuf);
}

} // namespace FieldWriter
