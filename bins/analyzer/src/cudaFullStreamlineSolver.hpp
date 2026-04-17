#pragma once

#include "streamlineSolver.hpp"

class CudaFullStreamlineSolver : public StreamlineSolver {
  public:
    explicit CudaFullStreamlineSolver(unsigned int blockSize = 256)
        : m_blockSize(blockSize) {}
    void computeTimeStep(Field::Grid& grid) override;

  private:
    unsigned int m_blockSize;
};
