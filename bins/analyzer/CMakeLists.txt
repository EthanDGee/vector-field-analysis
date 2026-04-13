option(ENABLE_CUDA "BUILD ANALYZER CUDA BACKEND" ON)

if(ENABLE_CUDA)
  enable_language(CUDA)
  find_package(CUDAToolkit REQUIRED)
endif()

add_library(analyzer_lib STATIC
            src/vectorField.cpp
            src/fieldReader.cpp
)

if(ENABLE_CUDA)
  target_sources(analyzer_lib PRIVATE
                 src/cuda.cu 
  )
endif()

target_include_directories(analyzer_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(analyzer_lib PUBLIC 
                      vector 
                      HighFive)

if(ENABLE_CUDA)
  target_link_libraries(analyzer_lib PUBLIC
                        CUDA::cudart)

  set_target_properties(analyzer_lib PROPERTIES
                        CUDA_SEPARABLE_COMPILATION ON 
                        CUDA_STANDARD 17
                        CUDA_STANDARD_REQUIRED ON)
endif()

add_executable(analyzer src/main.cpp)

target_link_libraries(analyzer PRIVATE 
                      analyzer_lib)

add_subdirectory(tests)
