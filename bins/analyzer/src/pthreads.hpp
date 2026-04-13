#pragma once
#include "streamlineSolver.hpp"

class Pthreads : public StreamlineSolver {
    unsigned int threadCount_;

  public:
    explicit Pthreads(unsigned int threadCount);

    void computeTimeStep(VectorField::FieldGrid& grid) override;
};
