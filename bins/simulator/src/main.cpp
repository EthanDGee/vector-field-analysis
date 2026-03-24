#include <highfive/highfive.hpp>
#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

static const int   WIDTH  = 64;
static const int   HEIGHT = 64;
static const float X_MIN  = -1.0f;
static const float X_MAX  =  1.0f;
static const float Y_MIN  = -1.0f;
static const float Y_MAX  =  1.0f;

// Vortex field: vectors rotate counter-clockwise around the origin.
// At point (x, y), the unit vector perpendicular to the radius is (-y, x) / r.
static Eigen::Vector2f vortex(float x, float y) {
    float r = std::sqrt(x * x + y * y);
    if (r < 1e-6f) return Eigen::Vector2f::Zero();
    return Eigen::Vector2f(-y / r, x / r);
}

int main(int argc, char* argv[]) {
    std::string outPath = argc > 1 ? argv[1] : "field.h5";

    std::vector<std::vector<float>> vx(HEIGHT, std::vector<float>(WIDTH));
    std::vector<std::vector<float>> vy(HEIGHT, std::vector<float>(WIDTH));

    for (int j = 0; j < HEIGHT; ++j) {
        for (int i = 0; i < WIDTH; ++i) {
            float x = X_MIN + (X_MAX - X_MIN) * i / (WIDTH  - 1);
            float y = Y_MIN + (Y_MAX - Y_MIN) * j / (HEIGHT - 1);
            Eigen::Vector2f v = vortex(x, y);
            vx[j][i] = v.x();
            vy[j][i] = v.y();
        }
    }

    HighFive::File file(outPath, HighFive::File::Overwrite);
    auto group = file.createGroup("field");
    group.createDataSet("vx", vx);
    group.createDataSet("vy", vy);
    group.createAttribute("width",  WIDTH);
    group.createAttribute("height", HEIGHT);
    group.createAttribute("xMin",   X_MIN);
    group.createAttribute("xMax",   X_MAX);
    group.createAttribute("yMin",   Y_MIN);
    group.createAttribute("yMax",   Y_MAX);

    std::cout << "Wrote " << outPath << " (" << WIDTH << "x" << HEIGHT << " vortex field)\n";
    return 0;
}
