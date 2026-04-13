#pragma once
#include "streamlineSolver.hpp"

class OpenMP : public StreamlineSolver {
  public:
    void computeTimeStep(VectorField::FieldGrid& grid) override;
};
