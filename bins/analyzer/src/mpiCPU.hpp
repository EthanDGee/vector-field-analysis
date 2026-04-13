#pragma once
#include "streamlineSolver.hpp"

// Distributed memory CPU implementation using MPI.
// When compiled without USE_MPI, falls back to SequentialCPU.
// In a multi-rank run all ranks must call computeTimeStep together;
// only rank 0's FieldGrid will contain the merged streamlines after the call.
class MpiCPU : public StreamlineSolver {
  public:
    void computeTimeStep(VectorField::FieldGrid& grid) override;
};
