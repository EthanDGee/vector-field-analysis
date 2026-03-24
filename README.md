# Vector Field Analysis

A research tool for analyzing and simulating vector fields.

## Structure

**Libraries** (`libs/`)

| Library | Description |
|---|---|
| [`libs/vector`](libs/vector) | Core vector types and math utilities shared across binaries and libraries |

**Binaries** (`bins/`)

| Binary | Description |
|---|---|
| [`bins/analyzer`](bins/analyzer) | Parses vector field data and computes properties such as streamlines and flow |
| [`bins/simulator`](bins/simulator) | Generates vector fields for research and testing |

## Building

```sh
mise run build                  # build everything
mise run build:lib:vector       # build vector library only
mise run build:bin:analyzer     # build analyzer only
mise run build:bin:simulator    # build simulator only
mise run test                   # run all tests
mise run test:lib:vector        # run vector library tests
mise run test:bin:analyzer      # run analyzer tests
mise run test:bin:simulator     # run simulator tests
mise run run:bin:simulator      # generate field.h5
mise run run:bin:analyzer       # read and analyze field.h5
mise run clean                  # remove build artifacts
```
