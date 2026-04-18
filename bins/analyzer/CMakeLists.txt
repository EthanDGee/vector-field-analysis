# Auto-detect the CUDA toolkit; honour an explicit -DENABLE_CUDA=ON/OFF override.
find_package(CUDAToolkit QUIET)
option(ENABLE_CUDA "Build analyzer CUDA solver" ${CUDAToolkit_FOUND})

if(ENABLE_CUDA)
  # Default covers CHPC GPUs reachable with CUDA 11.5 (the CI toolkit):
  #   sm_60/61 (kingspeak P100, lonepeak/kingspeak 1080Ti/TitanX/P40)
  #   sm_70/75 (notchpeak V100/TitanV, T4/2080Ti)
  #   sm_80/86 (notchpeak A100, A40/A6000/3090)
  # sm_89/90 (granite L40S/H100/H200) require CUDA >= 11.8 and are only
  # reachable on CHPC where native is used anyway.
  # These are compile-check targets; production runs use native:
  #   cmake -B build -DCMAKE_CUDA_ARCHITECTURES=native
  # benchmark.sh and enqueue.sh set native automatically on CHPC nodes.
  if(NOT DEFINED CMAKE_CUDA_ARCHITECTURES)
    set(CMAKE_CUDA_ARCHITECTURES 60 61 70 75 80 86)
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

if(ENABLE_CUDA)
  # Wrap every host-only dep in $<HOST_LINK:...> so nvlink does not receive
  # their transitive glibc 2.34+ stub .a files (libpthread.a, libdl.a,
  # librt.a) during the device link step. This covers HDF5 (via HighFive),
  # MPI, OpenMP, and anything else that carries pthread/dl/rt dependencies.
  target_link_libraries(analyzer_lib
    PUBLIC
      $<HOST_LINK:field>
      $<HOST_LINK:field_io>
      $<HOST_LINK:HighFive>
    PRIVATE
      $<HOST_LINK:utils>
      $<HOST_LINK:tomlplusplus::tomlplusplus>
  )
else()
  target_link_libraries(analyzer_lib
    PUBLIC
      field
      field_io
      HighFive
    PRIVATE
      utils
      tomlplusplus::tomlplusplus
  )
endif()

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
    if(ENABLE_CUDA)
        target_link_libraries(analyzer_lib PUBLIC $<HOST_LINK:MPI::MPI_CXX>)
    else()
        target_link_libraries(analyzer_lib PUBLIC MPI::MPI_CXX)
    endif()
endif()

find_package(OpenMP)
if(OpenMP_FOUND)
    if(ENABLE_CUDA)
        target_link_libraries(analyzer_lib PUBLIC $<HOST_LINK:OpenMP::OpenMP_CXX>)
    else()
        target_link_libraries(analyzer_lib PUBLIC OpenMP::OpenMP_CXX)
    endif()
endif()

add_executable(analyzer src/main.cpp)
target_link_libraries(analyzer PRIVATE
                      analyzer_lib
                      utils
                      stdc++fs
                     )

add_subdirectory(tests)
