#pragma once
#include <string>

// Configuration for one analyzer run, parsed from a TOML config file.
// Defaults match single-process benchmark-all behaviour.
struct AnalyzerConfig {
    std::string inputPath = "field.h5";
    // "sequential" | "openmp" | "pthreads" | "mpi" | "all"
    std::string solver = "all";
    // Thread count for the Pthreads solver.  0 = hardware_concurrency.
    unsigned int threadCount = 0;
};
