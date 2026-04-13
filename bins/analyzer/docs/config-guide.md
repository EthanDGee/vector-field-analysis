# Analyzer Config Guide

An analyzer config is a TOML file with a single `[analyzer]` table.

```
analyzer <config.toml>
```

See `bins/analyzer/configs/` for ready-to-run examples.

---

## `[analyzer]` Reference

| Key | Type | Default | Description |
|-----|------|---------|-------------|
| `input` | string | `"field.h5"` | HDF5 field file produced by the simulator |
| `solver` | string | `"all"` | Solver to run (see below) |
| `threads` | int | `0` | Thread count for `pthreads`. `0` = `hardware_concurrency`. |

---

## `solver` Values

| Value | Description |
|-------|-------------|
| `"all"` | Benchmark all solvers and print timings side-by-side (default) |
| `"sequential"` | Single-threaded reference implementation |
| `"openmp"` | Shared memory, OpenMP parallelism |
| `"pthreads"` | Shared memory, manual pthread parallelism |
| `"mpi"` | Distributed memory CPU via MPI (see MPI usage below) |

---

## MPI Usage

The `mpi` solver requires all ranks to call `computeTimeStep` together.
Run with `mpirun` (local) or `srun` (CHPC/Slurm):

```bash
# Local
mpirun -n 4 analyzer bins/analyzer/configs/mpi.toml

# CHPC via Slurm
srun -n 4 analyzer bins/analyzer/configs/mpi.toml
```

Each rank reads the field file independently (works on shared filesystems like Lustre).
Rank 0 performs the sequential merge pass and prints results.

---

## Examples

### Benchmark all solvers

```toml
[analyzer]
input   = "field.h5"
solver  = "all"
threads = 0
```

### Run pthreads with a fixed thread count

```toml
[analyzer]
input   = "field.h5"
solver  = "pthreads"
threads = 8
```

### MPI run

```toml
[analyzer]
input  = "field.h5"
solver = "mpi"
```
