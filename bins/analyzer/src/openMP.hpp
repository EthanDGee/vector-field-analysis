#pragma once
#include "streamlineSolver.hpp"

class OpenMP : public StreamlineSolver {
  public:
    explicit OpenMP(unsigned int threadCount = 0);
    void computeTimeStep(VectorField::FieldGrid& grid) override;

  private:
    unsigned int threadCount_;
};
