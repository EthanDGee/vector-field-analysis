# cmake

CMake modules for the project.

## Contents

- **Dependencies.cmake** — fetches third-party libraries at configure time via FetchContent

## Dependencies

| Library | Version | Purpose |
|---|---|---|
| [Eigen](https://eigen.tuxfamily.org) | 3.4.0 | Linear algebra |
| [HighFive](https://github.com/BlueBrain/HighFive) | v2.10.0 | HDF5 C++ wrapper |
| [Catch2](https://github.com/catchorg/Catch2) | v3.5.3 | Testing |

HDF5 must be installed on the system before configuring. Run `mise run deps` to install it.

| Distro | Package |
|---|---|
| Arch Linux | `hdf5` |
| Ubuntu | `libhdf5-dev` |
