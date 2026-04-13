#pragma once
#include "streamlineSolver.hpp"

class SequentialCPU : public StreamlineSolver {
  public:
    void computeTimeStep(VectorField::FieldGrid& grid) override;
};
