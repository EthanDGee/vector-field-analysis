#pragma once
#include "vectorField.hpp"

class StreamlineSolver {
  public:
    virtual ~StreamlineSolver() = default;

    StreamlineSolver() = default;
    StreamlineSolver(const StreamlineSolver&) = delete;
    StreamlineSolver& operator=(const StreamlineSolver&) = delete;
    StreamlineSolver(StreamlineSolver&&) = delete;
    StreamlineSolver& operator=(StreamlineSolver&&) = delete;

    virtual void computeTimeStep(VectorField::FieldGrid& grid) = 0;
};
