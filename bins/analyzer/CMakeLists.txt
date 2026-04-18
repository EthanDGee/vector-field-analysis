# Auto-detect the CUDA toolkit; honour an explicit -DENABLE_CUDA=ON/OFF override.
find_package(CUDAToolkit QUIET)
option(ENABLE_CUDA "Build analyzer CUDA solver" ${CUDAToolkit_FOUND})

if(ENABLE_CUDA)
  # Default to common architectures so the build works on machines without a
  # GPU (e.g. CI runners). For local dev, override with the GPU present:
  #   cmake -B build -DCMAKE_CUDA_ARCHITECTURES=native
  # benchmark.sh and enqueue.sh do this automatically for CHPC nodes.
  if(NOT DEFINED CMAKE_CUDA_ARCHITECTURES)
    set(CMAKE_CUDA_ARCHITECTURES 70 75 80 86)
  endif()
  enable_language(CUDA)
  find_package(CUDAToolkit REQUIRED)
endif()

add_library(analyzer_lib STATIC
    src/configParser.cpp
    src/mpiStreamlineSolver.cpp
    src/openMpStreamlineSolver.cpp
    src/pthreadsStreamlineSolver.cpp
    src/sequentialStreamlineSolver.cpp
    src/solverFactory.cpp
    src/streamlineSolver.cpp
    src/streamWriter.cpp
    src/timing.cpp
)

if(ENABLE_CUDA)
  target_sources(analyzer_lib PRIVATE
                 src/cudaStreamlineSolver.cu
                 src/cudaFull.cu
                 src/cudaFullStreamlineSolver.cu
               )
endif()

target_include_directories(analyzer_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(analyzer_lib
  PUBLIC
    field
    field_io
    HighFive

  PRIVATE
    utils
    tomlplusplus::tomlplusplus
)

if(ENABLE_CUDA)
  target_link_libraries(analyzer_lib PUBLIC
                        CUDA::cudart
  )
  target_compile_definitions(analyzer_lib PUBLIC
                             ENABLE_CUDA_SOLVER=1
  )
  set_target_properties(analyzer_lib PROPERTIES
                        CUDA_SEPARABLE_COMPILATION ON
                        CUDA_STANDARD 17
                        CUDA_STANDARD_REQUIRED ON
  )
  # nvidia-cuda-toolkit 11.5.1 (Ubuntu 22.04) does not officially support
  # GCC 11. This flag suppresses the host-compiler version check; the code
  # itself is valid C++17.
  target_compile_options(analyzer_lib PRIVATE
      $<$<COMPILE_LANGUAGE:CUDA>:-allow-unsupported-compiler>
  )
endif()

find_package(MPI)
if(MPI_FOUND)
    # USE_MPI must be PUBLIC so main.cpp (which links analyzer_lib) sees the definition.
    target_compile_definitions(analyzer_lib PUBLIC USE_MPI)
    target_link_libraries(analyzer_lib PUBLIC MPI::MPI_CXX)
endif()

# On glibc 2.34+ (Ubuntu 22.04+), libpthread.a is an empty stub that nvlink
# cannot process during CUDA device linking. Point FindOpenMP at the real
# versioned shared library before it runs its search.
if(ENABLE_CUDA AND UNIX AND NOT APPLE AND NOT DEFINED OpenMP_pthread_LIBRARY)
    find_file(OpenMP_pthread_LIBRARY
        NAMES libpthread.so.0
        PATHS
            /usr/lib/x86_64-linux-gnu
            /usr/lib/aarch64-linux-gnu
            /usr/lib64
            /usr/lib
        NO_DEFAULT_PATH
    )
endif()

find_package(OpenMP)
if(OpenMP_FOUND)
    target_link_libraries(analyzer_lib PUBLIC OpenMP::OpenMP_CXX)
endif()

add_executable(analyzer src/main.cpp)
target_link_libraries(analyzer PRIVATE
                      analyzer_lib
                      utils
                      stdc++fs
                     )

add_subdirectory(tests)
