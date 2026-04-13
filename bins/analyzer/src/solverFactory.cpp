#include "solverFactory.hpp"

#include "mpiCPU.hpp"
#include "openMP.hpp"
#include "pthreads.hpp"
#include "sequentialCPU.hpp"

#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>

// Valid names mirror kValidSolvers in analyzerConfig.hpp — keep in sync when adding solvers.
std::unique_ptr<StreamlineSolver> makeSolver(std::string_view name, unsigned int threadCount) {
    if (name == "sequential") {
        return std::make_unique<SequentialCPU>();
    }
    if (name == "openmp") {
        return std::make_unique<OpenMP>();
    }
    if (name == "pthreads") {
        return std::make_unique<Pthreads>(threadCount);
    }
    if (name == "mpi") {
        return std::make_unique<MpiCPU>();
    }
    throw std::runtime_error("Unknown solver: \"" + std::string(name) + "\"");
}
