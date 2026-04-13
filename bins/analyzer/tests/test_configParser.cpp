#include "analyzerConfigParser.hpp"

#include <catch2/catch_test_macros.hpp>
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>
#include <unistd.h>

// Write a TOML string to a temp file and return the path.
// std::string::data() returns a non-const pointer in C++17, so it serves as
// the mutable buffer that mkstemp requires.
static std::string writeTmp(const std::string& content) {
    std::string path = "/tmp/analyzer_test_XXXXXX";
    int fd = mkstemp(path.data());
    if (fd == -1) {
        throw std::runtime_error("mkstemp failed");
    }
    close(fd);
    std::ofstream out(path);
    out << content;
    return path;
}

// ---------------------------------------------------------------------------
// Valid configs
// ---------------------------------------------------------------------------

TEST_CASE("parseFile returns defaults when [analyzer] table is absent", "[config]") {
    auto path = writeTmp("# empty\n");
    const auto cfg = AnalyzerConfigParser::parseFile(path);
    std::remove(path.c_str());

    REQUIRE(cfg.inputPath == "field.h5");
    REQUIRE(cfg.solver == "all");
    REQUIRE(cfg.threadCount == 0);
}

TEST_CASE("parseFile reads input, solver, and threads from [analyzer]", "[config]") {
    auto path = writeTmp("[analyzer]\ninput = \"data.h5\"\nsolver = \"sequential\"\nthreads = 4\n");
    const auto cfg = AnalyzerConfigParser::parseFile(path);
    std::remove(path.c_str());

    REQUIRE(cfg.inputPath == "data.h5");
    REQUIRE(cfg.solver == "sequential");
    REQUIRE(cfg.threadCount == 4);
}

TEST_CASE("parseFile accepts all valid solver names", "[config]") {
    for (const auto* solver : {"sequential", "openmp", "pthreads", "mpi", "all"}) {
        auto path = writeTmp(std::string("[analyzer]\nsolver = \"") + solver + "\"\n");
        REQUIRE_NOTHROW(AnalyzerConfigParser::parseFile(path));
        std::remove(path.c_str());
    }
}

TEST_CASE("parseFile accepts threads = 0", "[config]") {
    auto path = writeTmp("[analyzer]\nthreads = 0\n");
    const auto cfg = AnalyzerConfigParser::parseFile(path);
    std::remove(path.c_str());
    REQUIRE(cfg.threadCount == 0);
}

// ---------------------------------------------------------------------------
// Invalid configs
// ---------------------------------------------------------------------------

TEST_CASE("parseFile throws on unknown solver name", "[config]") {
    auto path = writeTmp("[analyzer]\nsolver = \"gpu\"\n");
    REQUIRE_THROWS_AS(AnalyzerConfigParser::parseFile(path), std::runtime_error);
    std::remove(path.c_str());
}

TEST_CASE("parseFile throws on negative threads", "[config]") {
    auto path = writeTmp("[analyzer]\nthreads = -1\n");
    REQUIRE_THROWS_AS(AnalyzerConfigParser::parseFile(path), std::runtime_error);
    std::remove(path.c_str());
}

TEST_CASE("parseFile throws on missing file", "[config]") {
    REQUIRE_THROWS(AnalyzerConfigParser::parseFile("/tmp/does_not_exist_analyzer_test.toml"));
}
