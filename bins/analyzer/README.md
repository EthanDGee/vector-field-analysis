# Analyzer

Reads a time-series vector field from HDF5 and traces streamlines through each step.

## Usage

```sh
analyzer bins/analyzer/configs/all.toml        # benchmark all impls
analyzer bins/analyzer/configs/sequential.toml # single-threaded reference
mpirun -n 4 analyzer bins/analyzer/configs/mpi.toml  # MPI solver, 4 ranks
mise run run:analyzer                          # build + simulate + benchmark (recommended)
```

## What It Does

1. Reads `vx[steps][height][width]` and `vy[steps][height][width]` from an HDF5 file
2. For each time step, constructs a `FieldGrid` from that step's 2D vector slice
3. Calls `traceStreamlineStep` to follow one vector and connect it to a streamline

## Dependencies

- [`libs/vector`](../../libs/vector) - `Vec2` and `Streamline` types
- HighFive v2.10.0 - HDF5 input

## Tasks

```sh
mise run build:analyzer       # build
mise run test:analyzer        # test
mise run run:analyzer         # run simulator then benchmark all impls under mpirun -n $(nproc)
mise run run:analyzer:mpi     # MPI solver only (default 4 ranks; override with NRANKS=N)
```
