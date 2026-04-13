#include "analyzerConfig.hpp"
#include "analyzerConfigParser.hpp"
#include "fieldReader.hpp"
#include "solverFactory.hpp"
#include "streamlineSolver.hpp"
#include "vectorField.hpp"

#ifdef USE_MPI
#include <mpi.h>
#endif

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

static double runSolver(StreamlineSolver& solver, const Vector::FieldTimeSeries& data) {
    auto t0 = std::chrono::steady_clock::now();
    for (const auto& step : data.steps) {
        VectorField::FieldGrid grid(data.xMin, data.xMax, data.yMin, data.yMax, step);
        solver.computeTimeStep(grid);
    }
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
}

static void printHelp() {
    std::cout << "Usage: analyzer <config.toml>\n"
              << "\nRuns vector field streamline analysis using the given TOML config file.\n"
              << "See bins/analyzer/configs/ for example configs.\n"
              << "See bins/analyzer/docs/config-guide.md for all config keys.\n"
              << "\n[analyzer] keys:\n"
              << "  input   = \"field.h5\"   HDF5 field file to read\n"
              << "  solver  = \"all\"        sequential | openmp | pthreads | mpi | all\n"
              << "  threads = 0            thread count for pthreads (0 = hardware_concurrency)\n"
              << "\nFor MPI: mpirun -n N analyzer <config.toml>  with solver = \"mpi\"\n";
}

static unsigned int resolveThreadCount(unsigned int requested) {
    if (requested > 0) {
        return requested;
    }
    const unsigned int hw = std::thread::hardware_concurrency();
    return hw > 0 ? hw : 1;
}

static void runAll(const Vector::FieldTimeSeries& data, unsigned int threadCount, int mpiRank,
                   int mpiSize) {
    auto seq = makeSolver("sequential", threadCount);
    auto omp = makeSolver("openmp", threadCount);
    auto pt = makeSolver("pthreads", threadCount);
    auto mpi = makeSolver("mpi", threadCount);

    const double seqMs = runSolver(*seq, data);
    const double ompMs = runSolver(*omp, data);
    const double ptMs = runSolver(*pt, data);
    const double mpiMs = runSolver(*mpi, data);

    if (mpiRank == 0) {
        std::cout << "sequential             " << seqMs << " ms\n"
                  << "openmp                 " << ompMs << " ms"
                  << "  (" << seqMs / ompMs << "x vs sequential)\n"
                  << "pthreads (" << threadCount << " thr)    " << ptMs << " ms"
                  << "  (" << seqMs / ptMs << "x vs sequential)\n"
                  << "mpi (" << mpiSize << " rank(s))       " << mpiMs << " ms"
                  << "  (" << seqMs / mpiMs << "x vs sequential)\n";
    }
}

static void runOne(const std::string& solverName, const Vector::FieldTimeSeries& data,
                   unsigned int threadCount, int mpiRank, int mpiSize) {
    auto analyzer = makeSolver(solverName, threadCount);
    const double ms = runSolver(*analyzer, data);

    if (mpiRank == 0) {
        std::string label = solverName;
        if (solverName == "pthreads") {
            label += " (" + std::to_string(threadCount) + " thr)";
        } else if (solverName == "mpi") {
            label += " (" + std::to_string(mpiSize) + " rank(s))";
        }
        std::cout << label << "  " << ms << " ms\n";
    }
}

int main(int argc, char* argv[]) {
#ifdef USE_MPI
    MPI_Init(&argc, &argv);
    int mpiRank = 0;
    int mpiSize = 1;
    MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
#else
    // Non-const avoids cppcheck knownConditionTrueFalse on the mpiRank == 0 guards below.
    int mpiRank = 0;
    int mpiSize = 1;
#endif

    const bool wantHelp =
        argc > 1 && (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h");
    if (wantHelp) {
        if (mpiRank == 0) {
            printHelp();
        }
#ifdef USE_MPI
        MPI_Finalize();
#endif
        return 0;
    }

    if (argc < 2) {
        if (mpiRank == 0) {
            std::cerr << "Usage: analyzer <config.toml>\n";
        }
#ifdef USE_MPI
        MPI_Finalize();
#endif
        return 1;
    }

    int exitCode = 0;
    try {
        const AnalyzerConfig config = AnalyzerConfigParser::parseFile(argv[1]);
        const unsigned int threadCount = resolveThreadCount(config.threadCount);
        const Vector::FieldTimeSeries data = FieldReader::read(config.inputPath);

        if (mpiRank == 0) {
            const int numSteps = static_cast<int>(data.steps.size());
            const int height = static_cast<int>(data.steps[0].size());
            const int width = static_cast<int>(data.steps[0][0].size());
            std::cout << "Field: " << config.inputPath << "  " << width << "x" << height << "  "
                      << numSteps << " step(s)";
            if (mpiSize > 1) {
                std::cout << "  MPI ranks: " << mpiSize;
            }
            std::cout << "\n\n";
        }

        if (config.solver == "all") {
            runAll(data, threadCount, mpiRank, mpiSize);
        } else {
            runOne(config.solver, data, threadCount, mpiRank, mpiSize);
        }
    } catch (const std::exception& e) {
        if (mpiRank == 0) {
            std::cerr << "Error: " << e.what() << "\n";
        }
        exitCode = 1;
    }

#ifdef USE_MPI
    MPI_Finalize();
#endif
    return exitCode;
}
