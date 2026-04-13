# Analyzer Docs

Documentation for the `analyzer` binary (`bins/analyzer`).

## What It Does

Reads a time-series vector field from an HDF5 file and, for each time step, constructs a
`FieldGrid` and traces streamlines across it using a selected parallel implementation.
All implementations share a two-pass design: a parallelisable read pass followed by a
sequential merge pass.

## Quick Start

```sh
# Generate a field first (see bins/simulator/)
simulator bins/simulator/configs/vortex.toml

# Benchmark all implementations
analyzer bins/analyzer/configs/default.toml

# Run a single implementation
analyzer bins/analyzer/configs/mpi.toml

# With MPI (N ranks)
mpirun -n 4 analyzer bins/analyzer/configs/mpi.toml
```

## Input Format

The analyzer reads HDF5 files in the format produced by the simulator:

```
field/               (group)
  vx                 (float dataset, shape [steps][height][width])
  vy                 (float dataset, shape [steps][height][width])
  xMin               (float attribute)
  xMax               (float attribute)
  yMin               (float attribute)
  yMax               (float attribute)
  steps              (int attribute)
  dt                 (float attribute)
  viscosity          (float attribute)
  type               (string attribute)
```

## Contents

- [pipeline.md](pipeline.md) — data flow, algorithm details, and source file map
- [config-guide.md](config-guide.md) — all TOML config keys and examples
