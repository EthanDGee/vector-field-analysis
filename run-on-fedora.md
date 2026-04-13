(base) rylei@fedora:~/Spring26/CS6030/Final/vector-field-analysis$ git restore CMakeLists.txt
rm -rf build build-sanitize build-coverage
rm -rf bin include lib share
rm -f cmake/hdf5-config*.cmake
rm -f cmake/hdf5-targets*.cmake
rm -f cmake/hdf5_static-targets*.cmake
rm -rf cmake/Modules
(base) rylei@fedora:~/Spring26/CS6030/Final/vector-field-analysis$ sudo dnf install -y gcc-c++ cmake ninja-build hdf5-devel cppcheck python3 python3-pip git
[sudo] password for rylei: 
Updating and loading repositories:
 Fedora 41 - x86_64 - Updates                     100% |  27.0 KiB/s |   4.1 KiB |  00m00s
Repositories loaded.
Package "gcc-c++-14.3.1-4.fc41.x86_64" is already installed.
Package "cmake-3.30.8-1.fc41.x86_64" is already installed.
Package "ninja-build-1.12.1-3.fc41.x86_64" is already installed.
Package "hdf5-devel-1.12.1-21.fc41.x86_64" is already installed.
Package "cppcheck-2.18.3-1.fc41.x86_64" is already installed.
Package "python3-3.13.9-1.fc41.x86_64" is already installed.
Package "python3-pip-24.2-3.fc41.noarch" is already installed.

Package                     Arch     Version                      Repository          Size
Installing:
 git                        x86_64   2.52.0-1.fc41                updates         56.4 KiB
Installing dependencies:
 git-core-doc               noarch   2.52.0-1.fc41                updates         18.4 MiB
 perl-Error                 noarch   1:0.17029-16.fc41            fedora          77.3 KiB
 perl-Git                   noarch   2.52.0-1.fc41                updates         64.4 KiB
 perl-TermReadKey           x86_64   2.38-23.fc41                 fedora          64.1 KiB
 perl-lib                   x86_64   0.65-517.fc41                updates          8.5 KiB

Transaction Summary:
 Installing:         6 packages

Total size of inbound packages is 3 MiB. Need to download 3 MiB.
After this operation, 19 MiB extra will be used (install 19 MiB, remove 0 B).
[1/6] perl-TermReadKey-0:2.38-23.fc41.x86_64      100% | 145.1 KiB/s |  35.6 KiB |  00m00s
[2/6] git-0:2.52.0-1.fc41.x86_64                  100% | 122.7 KiB/s |  40.5 KiB |  00m00s
[3/6] perl-Git-0:2.52.0-1.fc41.noarch             100% | 240.9 KiB/s |  37.6 KiB |  00m00s
[4/6] perl-Error-1:0.17029-16.fc41.noarch         100% | 268.9 KiB/s |  40.6 KiB |  00m00s
[5/6] perl-lib-0:0.65-517.fc41.x86_64             100% | 175.5 KiB/s |  14.6 KiB |  00m00s
[6/6] git-core-doc-0:2.52.0-1.fc41.noarch         100% |   3.5 MiB/s |   3.1 MiB |  00m01s
------------------------------------------------------------------------------------------
[6/6] Total                                       100% |   3.2 MiB/s |   3.2 MiB |  00m01s
Running transaction
[1/8] Verify package files                        100% | 187.0   B/s |   6.0   B |  00m00s
[2/8] Prepare transaction                         100% |   4.0   B/s |   6.0   B |  00m01s
[3/8] Installing perl-lib-0:0.65-517.fc41.x86_64  100% | 278.2 KiB/s |   8.9 KiB |  00m00s
[4/8] Installing perl-Error-1:0.17029-16.fc41.noa 100% |   2.2 MiB/s |  80.5 KiB |  00m00s
[5/8] Installing git-core-doc-0:2.52.0-1.fc41.noa 100% |  11.9 MiB/s |  18.6 MiB |  00m02s
[6/8] Installing perl-TermReadKey-0:2.38-23.fc41. 100% |   4.0 MiB/s |  66.3 KiB |  00m00s
[7/8] Installing perl-Git-0:2.52.0-1.fc41.noarch  100% |   4.9 MiB/s |  65.4 KiB |  00m00s
[8/8] Installing git-0:2.52.0-1.fc41.x86_64       100% |  17.1 KiB/s |  57.7 KiB |  00m03s
Complete!
(base) rylei@fedora:~/Spring26/CS6030/Final/vector-field-analysis$ which h5cc
which h5c++
/usr/bin/h5cc
/usr/bin/h5c++
(base) rylei@fedora:~/Spring26/CS6030/Final/vector-field-analysis$ cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build -j
ctest --test-dir build --output-on-failure
-- The CXX compiler identification is GNU 14.3.1
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found HDF5: /usr/lib64/libhdf5.so;/usr/lib64/libhdf5_cpp.so;/usr/lib64/libhdf5.so (found version "1.12.1") found components: C CXX
CMake Deprecation Warning at build/_deps/eigen-src/CMakeLists.txt:2 (cmake_minimum_required):
  Compatibility with CMake < 3.10 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.


-- The C compiler identification is GNU 14.3.1
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Performing Test EIGEN_COMPILER_SUPPORT_CPP11
-- Performing Test EIGEN_COMPILER_SUPPORT_CPP11 - Success
-- Performing Test COMPILER_SUPPORT_std=cpp03
-- Performing Test COMPILER_SUPPORT_std=cpp03 - Success
-- Performing Test standard_math_library_linked_to_automatically
-- Performing Test standard_math_library_linked_to_automatically - Success
-- Standard libraries to link to explicitly: none
-- Performing Test COMPILER_SUPPORT_WERROR
-- Performing Test COMPILER_SUPPORT_WERROR - Success
-- Performing Test COMPILER_SUPPORT_pedantic
-- Performing Test COMPILER_SUPPORT_pedantic - Success
-- Performing Test COMPILER_SUPPORT_Wall
-- Performing Test COMPILER_SUPPORT_Wall - Success
-- Performing Test COMPILER_SUPPORT_Wextra
-- Performing Test COMPILER_SUPPORT_Wextra - Success
-- Performing Test COMPILER_SUPPORT_Wundef
-- Performing Test COMPILER_SUPPORT_Wundef - Success
-- Performing Test COMPILER_SUPPORT_Wcastalign
-- Performing Test COMPILER_SUPPORT_Wcastalign - Success
-- Performing Test COMPILER_SUPPORT_Wcharsubscripts
-- Performing Test COMPILER_SUPPORT_Wcharsubscripts - Success
-- Performing Test COMPILER_SUPPORT_Wnonvirtualdtor
-- Performing Test COMPILER_SUPPORT_Wnonvirtualdtor - Success
-- Performing Test COMPILER_SUPPORT_Wunusedlocaltypedefs
-- Performing Test COMPILER_SUPPORT_Wunusedlocaltypedefs - Success
-- Performing Test COMPILER_SUPPORT_Wpointerarith
-- Performing Test COMPILER_SUPPORT_Wpointerarith - Success
-- Performing Test COMPILER_SUPPORT_Wwritestrings
-- Performing Test COMPILER_SUPPORT_Wwritestrings - Success
-- Performing Test COMPILER_SUPPORT_Wformatsecurity
-- Performing Test COMPILER_SUPPORT_Wformatsecurity - Success
-- Performing Test COMPILER_SUPPORT_Wshorten64to32
-- Performing Test COMPILER_SUPPORT_Wshorten64to32 - Failed
-- Performing Test COMPILER_SUPPORT_Wlogicalop
-- Performing Test COMPILER_SUPPORT_Wlogicalop - Success
-- Performing Test COMPILER_SUPPORT_Wenumconversion
-- Performing Test COMPILER_SUPPORT_Wenumconversion - Success
-- Performing Test COMPILER_SUPPORT_Wcpp11extensions
-- Performing Test COMPILER_SUPPORT_Wcpp11extensions - Success
-- Performing Test COMPILER_SUPPORT_Wdoublepromotion
-- Performing Test COMPILER_SUPPORT_Wdoublepromotion - Success
-- Performing Test COMPILER_SUPPORT_Wshadow
-- Performing Test COMPILER_SUPPORT_Wshadow - Success
-- Performing Test COMPILER_SUPPORT_Wnopsabi
-- Performing Test COMPILER_SUPPORT_Wnopsabi - Success
-- Performing Test COMPILER_SUPPORT_Wnovariadicmacros
-- Performing Test COMPILER_SUPPORT_Wnovariadicmacros - Success
-- Performing Test COMPILER_SUPPORT_Wnolonglong
-- Performing Test COMPILER_SUPPORT_Wnolonglong - Success
-- Performing Test COMPILER_SUPPORT_fnochecknew
-- Performing Test COMPILER_SUPPORT_fnochecknew - Success
-- Performing Test COMPILER_SUPPORT_fnocommon
-- Performing Test COMPILER_SUPPORT_fnocommon - Success
-- Performing Test COMPILER_SUPPORT_fstrictaliasing
-- Performing Test COMPILER_SUPPORT_fstrictaliasing - Success
-- Performing Test COMPILER_SUPPORT_wd981
-- Performing Test COMPILER_SUPPORT_wd981 - Failed
-- Performing Test COMPILER_SUPPORT_wd2304
-- Performing Test COMPILER_SUPPORT_wd2304 - Failed
-- Performing Test COMPILER_SUPPORT_STRICTANSI
-- Performing Test COMPILER_SUPPORT_STRICTANSI - Failed
-- Performing Test COMPILER_SUPPORT_Qunusedarguments
-- Performing Test COMPILER_SUPPORT_Qunusedarguments - Failed
-- Performing Test COMPILER_SUPPORT_ansi
-- Performing Test COMPILER_SUPPORT_ansi - Success
-- Performing Test COMPILER_SUPPORT_OPENMP
-- Performing Test COMPILER_SUPPORT_OPENMP - Success
-- Looking for a Fortran compiler
-- Looking for a Fortran compiler - /usr/bin/gfortran
-- The Fortran compiler identification is GNU 14.3.1
-- Detecting Fortran compiler ABI info
-- Detecting Fortran compiler ABI info - done
-- Check for working Fortran compiler: /usr/bin/gfortran - skipped
-- Found unsuitable Qt version "" from NOTFOUND
-- Qt4 not found, so disabling the mandelbrot and opengl demos
-- Could NOT find CHOLMOD (missing: CHOLMOD_INCLUDES CHOLMOD_LIBRARIES) 
-- Could NOT find UMFPACK (missing: UMFPACK_INCLUDES UMFPACK_LIBRARIES) 
-- Could NOT find KLU (missing: KLU_INCLUDES KLU_LIBRARIES) 
-- Could NOT find SuperLU (missing: SUPERLU_INCLUDES SUPERLU_LIBRARIES SUPERLU_VERSION_OK) (Required is at least version "4.0")
-- Checking for one of the modules 'hwloc'
-- A version of Pastix has been found but pastix_nompi.h does not exist in the include directory. Because Eigen tests require a version without MPI, we disable the Pastix backend.
-- 
-- Configured Eigen 3.4.0
-- 
-- Available targets (use: cmake --build . --target TARGET):
-- ---------+--------------------------------------------------------------
-- Target   |   Description
-- ---------+--------------------------------------------------------------
-- install  | Install Eigen. Headers will be installed to:
--          |     <CMAKE_INSTALL_PREFIX>/<INCLUDE_INSTALL_DIR>
--          |   Using the following values:
--          |     CMAKE_INSTALL_PREFIX: /usr/local
--          |     INCLUDE_INSTALL_DIR:  include/eigen3
--          |   Change the install location of Eigen headers using:
--          |     cmake . -DCMAKE_INSTALL_PREFIX=yourprefix
--          |   Or:
--          |     cmake . -DINCLUDE_INSTALL_DIR=yourdir
-- doc      | Generate the API documentation, requires Doxygen & LaTeX
-- blas     | Build BLAS library (not the same thing as Eigen)
-- uninstall| Remove files installed by the install target
-- ---------+--------------------------------------------------------------
-- 
CMake Error at build/_deps/highfive-src/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 has been removed from CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.

  Or, add -DCMAKE_POLICY_VERSION_MINIMUM=3.5 to try configuring anyway.


-- Configuring incomplete, errors occurred!
ninja: error: loading 'build.ninja': No such file or directory
Test project /home/rylei/Spring26/CS6030/Final/vector-field-analysis/build
No tests were found!!!
(base) rylei@fedora:~/Spring26/CS6030/Final/vector-field-analysis$ 


(base) rylei@fedora:~/Spring26/CS6030/Final/vector-field-analysis$ rm -rf build
cmake -S . -B build -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_POLICY_VERSION_MINIMUM=3.5
cmake --build build -j
ctest --test-dir build --output-on-failure
-- The CXX compiler identification is GNU 14.3.1
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found HDF5: /usr/lib64/libhdf5.so;/usr/lib64/libhdf5_cpp.so;/usr/lib64/libhdf5.so (found version "1.12.1") found components: C CXX
CMake Deprecation Warning at build/_deps/eigen-src/CMakeLists.txt:2 (cmake_minimum_required):
  Compatibility with CMake < 3.10 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.


-- The C compiler identification is GNU 14.3.1
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Performing Test EIGEN_COMPILER_SUPPORT_CPP11
-- Performing Test EIGEN_COMPILER_SUPPORT_CPP11 - Success
-- Performing Test COMPILER_SUPPORT_std=cpp03
-- Performing Test COMPILER_SUPPORT_std=cpp03 - Success
-- Performing Test standard_math_library_linked_to_automatically
-- Performing Test standard_math_library_linked_to_automatically - Success
-- Standard libraries to link to explicitly: none
-- Performing Test COMPILER_SUPPORT_WERROR
-- Performing Test COMPILER_SUPPORT_WERROR - Success
-- Performing Test COMPILER_SUPPORT_pedantic
-- Performing Test COMPILER_SUPPORT_pedantic - Success
-- Performing Test COMPILER_SUPPORT_Wall
-- Performing Test COMPILER_SUPPORT_Wall - Success
-- Performing Test COMPILER_SUPPORT_Wextra
-- Performing Test COMPILER_SUPPORT_Wextra - Success
-- Performing Test COMPILER_SUPPORT_Wundef
-- Performing Test COMPILER_SUPPORT_Wundef - Success
-- Performing Test COMPILER_SUPPORT_Wcastalign
-- Performing Test COMPILER_SUPPORT_Wcastalign - Success
-- Performing Test COMPILER_SUPPORT_Wcharsubscripts
-- Performing Test COMPILER_SUPPORT_Wcharsubscripts - Success
-- Performing Test COMPILER_SUPPORT_Wnonvirtualdtor
-- Performing Test COMPILER_SUPPORT_Wnonvirtualdtor - Success
-- Performing Test COMPILER_SUPPORT_Wunusedlocaltypedefs
-- Performing Test COMPILER_SUPPORT_Wunusedlocaltypedefs - Success
-- Performing Test COMPILER_SUPPORT_Wpointerarith
-- Performing Test COMPILER_SUPPORT_Wpointerarith - Success
-- Performing Test COMPILER_SUPPORT_Wwritestrings
-- Performing Test COMPILER_SUPPORT_Wwritestrings - Success
-- Performing Test COMPILER_SUPPORT_Wformatsecurity
-- Performing Test COMPILER_SUPPORT_Wformatsecurity - Success
-- Performing Test COMPILER_SUPPORT_Wshorten64to32
-- Performing Test COMPILER_SUPPORT_Wshorten64to32 - Failed
-- Performing Test COMPILER_SUPPORT_Wlogicalop
-- Performing Test COMPILER_SUPPORT_Wlogicalop - Success
-- Performing Test COMPILER_SUPPORT_Wenumconversion
-- Performing Test COMPILER_SUPPORT_Wenumconversion - Success
-- Performing Test COMPILER_SUPPORT_Wcpp11extensions
-- Performing Test COMPILER_SUPPORT_Wcpp11extensions - Success
-- Performing Test COMPILER_SUPPORT_Wdoublepromotion
-- Performing Test COMPILER_SUPPORT_Wdoublepromotion - Success
-- Performing Test COMPILER_SUPPORT_Wshadow
-- Performing Test COMPILER_SUPPORT_Wshadow - Success
-- Performing Test COMPILER_SUPPORT_Wnopsabi
-- Performing Test COMPILER_SUPPORT_Wnopsabi - Success
-- Performing Test COMPILER_SUPPORT_Wnovariadicmacros
-- Performing Test COMPILER_SUPPORT_Wnovariadicmacros - Success
-- Performing Test COMPILER_SUPPORT_Wnolonglong
-- Performing Test COMPILER_SUPPORT_Wnolonglong - Success
-- Performing Test COMPILER_SUPPORT_fnochecknew
-- Performing Test COMPILER_SUPPORT_fnochecknew - Success
-- Performing Test COMPILER_SUPPORT_fnocommon
-- Performing Test COMPILER_SUPPORT_fnocommon - Success
-- Performing Test COMPILER_SUPPORT_fstrictaliasing
-- Performing Test COMPILER_SUPPORT_fstrictaliasing - Success
-- Performing Test COMPILER_SUPPORT_wd981
-- Performing Test COMPILER_SUPPORT_wd981 - Failed
-- Performing Test COMPILER_SUPPORT_wd2304
-- Performing Test COMPILER_SUPPORT_wd2304 - Failed
-- Performing Test COMPILER_SUPPORT_STRICTANSI
-- Performing Test COMPILER_SUPPORT_STRICTANSI - Failed
-- Performing Test COMPILER_SUPPORT_Qunusedarguments
-- Performing Test COMPILER_SUPPORT_Qunusedarguments - Failed
-- Performing Test COMPILER_SUPPORT_ansi
-- Performing Test COMPILER_SUPPORT_ansi - Success
-- Performing Test COMPILER_SUPPORT_OPENMP
-- Performing Test COMPILER_SUPPORT_OPENMP - Success
-- Looking for a Fortran compiler
-- Looking for a Fortran compiler - /usr/bin/gfortran
-- The Fortran compiler identification is GNU 14.3.1
-- Detecting Fortran compiler ABI info
-- Detecting Fortran compiler ABI info - done
-- Check for working Fortran compiler: /usr/bin/gfortran - skipped
-- Found unsuitable Qt version "" from NOTFOUND
-- Qt4 not found, so disabling the mandelbrot and opengl demos
-- Could NOT find CHOLMOD (missing: CHOLMOD_INCLUDES CHOLMOD_LIBRARIES) 
-- Could NOT find UMFPACK (missing: UMFPACK_INCLUDES UMFPACK_LIBRARIES) 
-- Could NOT find KLU (missing: KLU_INCLUDES KLU_LIBRARIES) 
-- Could NOT find SuperLU (missing: SUPERLU_INCLUDES SUPERLU_LIBRARIES SUPERLU_VERSION_OK) (Required is at least version "4.0")
-- Checking for one of the modules 'hwloc'
-- A version of Pastix has been found but pastix_nompi.h does not exist in the include directory. Because Eigen tests require a version without MPI, we disable the Pastix backend.
-- 
-- Configured Eigen 3.4.0
-- 
-- Available targets (use: cmake --build . --target TARGET):
-- ---------+--------------------------------------------------------------
-- Target   |   Description
-- ---------+--------------------------------------------------------------
-- install  | Install Eigen. Headers will be installed to:
--          |     <CMAKE_INSTALL_PREFIX>/<INCLUDE_INSTALL_DIR>
--          |   Using the following values:
--          |     CMAKE_INSTALL_PREFIX: /usr/local
--          |     INCLUDE_INSTALL_DIR:  include/eigen3
--          |   Change the install location of Eigen headers using:
--          |     cmake . -DCMAKE_INSTALL_PREFIX=yourprefix
--          |   Or:
--          |     cmake . -DINCLUDE_INSTALL_DIR=yourdir
-- doc      | Generate the API documentation, requires Doxygen & LaTeX
-- blas     | Build BLAS library (not the same thing as Eigen)
-- uninstall| Remove files installed by the install target
-- ---------+--------------------------------------------------------------
-- 
-- Performing Test HAVE_FLAG__ffile_prefix_map__home_rylei_Spring26_CS6030_Final_vector_field_analysis_build__deps_catch2_src__
-- Performing Test HAVE_FLAG__ffile_prefix_map__home_rylei_Spring26_CS6030_Final_vector_field_analysis_build__deps_catch2_src__ - Success
-- Configuring done (28.9s)
-- Generating done (0.1s)
-- Build files have been written to: /home/rylei/Spring26/CS6030/Final/vector-field-analysis/build
[131/131] Linking CXX executable bins/simulator/tests/simulator_tests
Test project /home/rylei/Spring26/CS6030/Final/vector-field-analysis/build
      Start  1: Vector magnitude
 1/64 Test  #1: Vector magnitude ...................................................................   Passed    0.00 sec
      Start  2: Vector unitVector has magnitude 1
 2/64 Test  #2: Vector unitVector has magnitude 1 ..................................................   Passed    0.00 sec
      Start  3: Vector unitVector preserves direction
 3/64 Test  #3: Vector unitVector preserves direction ..............................................   Passed    0.00 sec
      Start  4: dotProduct
 4/64 Test  #4: dotProduct .........................................................................   Passed    0.00 sec
      Start  5: almostParallel
 5/64 Test  #5: almostParallel .....................................................................   Passed    0.00 sec
      Start  6: Vec2 unitVector for zero vector returns zero vector
 6/64 Test  #6: Vec2 unitVector for zero vector returns zero vector ................................   Passed    0.00 sec
      Start  7: almostParallel threshold boundary
 7/64 Test  #7: almostParallel threshold boundary ..................................................   Passed    0.00 sec
      Start  8: dotProduct with zero vector
 8/64 Test  #8: dotProduct with zero vector ........................................................   Passed    0.00 sec
      Start  9: StreamLine initialises with start point
 9/64 Test  #9: StreamLine initialises with start point ............................................   Passed    0.00 sec
      Start 10: Streamline path grows when points are appended
10/64 Test #10: Streamline path grows when points are appended .....................................   Passed    0.00 sec
      Start 11: neighborInVectorDirection advances in vector direction
11/64 Test #11: neighborInVectorDirection advances in vector direction .............................   Passed    0.01 sec
      Start 12: traceStreamlineStep assigns a streamline
12/64 Test #12: traceStreamlineStep assigns a streamline ...........................................   Passed    0.01 sec
      Start 13: neighborInVectorDirection pointing left decreases column
13/64 Test #13: neighborInVectorDirection pointing left decreases column ...........................   Passed    0.01 sec
      Start 14: neighborInVectorDirection pointing up increases row
14/64 Test #14: neighborInVectorDirection pointing up increases row ................................   Passed    0.01 sec
      Start 15: neighborInVectorDirection pointing down decreases row
15/64 Test #15: neighborInVectorDirection pointing down decreases row ..............................   Passed    0.01 sec
      Start 16: neighborInVectorDirection clamped at left edge
16/64 Test #16: neighborInVectorDirection clamped at left edge .....................................   Passed    0.01 sec
      Start 17: neighborInVectorDirection clamped at right edge
17/64 Test #17: neighborInVectorDirection clamped at right edge ....................................   Passed    0.01 sec
      Start 18: neighborInVectorDirection clamped at top edge
18/64 Test #18: neighborInVectorDirection clamped at top edge ......................................   Passed    0.01 sec
      Start 19: neighborInVectorDirection clamped at bottom edge
19/64 Test #19: neighborInVectorDirection clamped at bottom edge ...................................   Passed    0.01 sec
      Start 20: joinStreamlines merges end path into start
20/64 Test #20: joinStreamlines merges end path into start .........................................   Passed    0.01 sec
      Start 21: joinStreamlines with null start is a no-op
21/64 Test #21: joinStreamlines with null start is a no-op .........................................   Passed    0.01 sec
      Start 22: joinStreamlines on equal pointers is a no-op
22/64 Test #22: joinStreamlines on equal pointers is a no-op .......................................   Passed    0.01 sec
      Start 23: tracing multiple steps builds a path without crash
23/64 Test #23: tracing multiple steps builds a path without crash .................................   Passed    0.01 sec
      Start 24: tracing into an occupied cell triggers merge without crash
24/64 Test #24: tracing into an occupied cell triggers merge without crash .........................   Passed    0.01 sec
      Start 25: FieldReader::read() throws for nonexistent file
25/64 Test #25: FieldReader::read() throws for nonexistent file ....................................   Passed    0.01 sec
      Start 26: FieldReader::read() returns correct step/row/col dimensions
26/64 Test #26: FieldReader::read() returns correct step/row/col dimensions ........................   Passed    0.01 sec
      Start 27: FieldReader::read() populates xMin/xMax/yMin/yMax
27/64 Test #27: FieldReader::read() populates xMin/xMax/yMin/yMax ..................................   Passed    0.01 sec
      Start 28: FieldReader::read() Vec2 values match written floats
28/64 Test #28: FieldReader::read() Vec2 values match written floats ...............................   Passed    0.01 sec
      Start 29: FieldReader::read() throws when vx dataset is missing
29/64 Test #29: FieldReader::read() throws when vx dataset is missing ..............................   Passed    0.01 sec
      Start 30: Vortex field produces unit vectors
30/64 Test #30: Vortex field produces unit vectors .................................................   Passed    0.01 sec
      Start 31: Vortex field is perpendicular to radius
31/64 Test #31: Vortex field is perpendicular to radius ............................................   Passed    0.01 sec
      Start 32: Vortex field is zero at origin
32/64 Test #32: Vortex field is zero at origin .....................................................   Passed    0.01 sec
      Start 33: generateTimeSeries() returns correct 3D dimensions
33/64 Test #33: generateTimeSeries() returns correct 3D dimensions .................................   Passed    0.01 sec
      Start 34: Vortex generateTimeSeries() produces unit magnitude away from origin
34/64 Test #34: Vortex generateTimeSeries() produces unit magnitude away from origin ...............   Passed    0.01 sec
      Start 35: Uniform field at angle=0 points right
35/64 Test #35: Uniform field at angle=0 points right ..............................................   Passed    0.01 sec
      Start 36: Uniform field at angle=90 points up
36/64 Test #36: Uniform field at angle=90 points up ................................................   Passed    0.01 sec
      Start 37: Source field points away from center
37/64 Test #37: Source field points away from center ...............................................   Passed    0.01 sec
      Start 38: Sink field points toward center
38/64 Test #38: Sink field points toward center ....................................................   Passed    0.01 sec
      Start 39: Saddle field has opposite signs in x and y relative to center
39/64 Test #39: Saddle field has opposite signs in x and y relative to center ......................   Passed    0.01 sec
      Start 40: Spiral field is between vortex and sink
40/64 Test #40: Spiral field is between vortex and sink ............................................   Passed    0.01 sec
      Start 41: Viscous decay reduces magnitude over steps
41/64 Test #41: Viscous decay reduces magnitude over steps .........................................   Passed    0.01 sec
      Start 42: Custom x_expression = "x" evaluates to world x-coordinate
42/64 Test #42: Custom x_expression = "x" evaluates to world x-coordinate ..........................   Passed    0.01 sec
      Start 43: Superposition sums field contributions
43/64 Test #43: Superposition sums field contributions .............................................   Passed    0.01 sec
      Start 44: parseFile() uses defaults when [simulation] section absent
44/64 Test #44: parseFile() uses defaults when [simulation] section absent .........................   Passed    0.01 sec
      Start 45: parseFile() reads [simulation] values correctly
45/64 Test #45: parseFile() reads [simulation] values correctly ....................................   Passed    0.01 sec
      Start 46: parseFile() defaults to one vortex layer when [[layers]] absent
46/64 Test #46: parseFile() defaults to one vortex layer when [[layers]] absent ....................   Passed    0.01 sec
      Start 47: parseFile() parses all 8 field types from [[layers]]
47/64 Test #47: parseFile() parses all 8 field types from [[layers]] ...............................   Passed    0.01 sec
      Start 48: parseFile() reads layer parameters
48/64 Test #48: parseFile() reads layer parameters .................................................   Passed    0.01 sec
      Start 49: parseFile() throws for nonexistent file
49/64 Test #49: parseFile() throws for nonexistent file ............................................   Passed    0.01 sec
      Start 50: parseFile() throws for unknown field type
50/64 Test #50: parseFile() throws for unknown field type ..........................................   Passed    0.01 sec
      Start 51: Noise field is non-constant spatially
51/64 Test #51: Noise field is non-constant spatially ..............................................   Passed    0.01 sec
      Start 52: Noise field is reproducible with the same seed
52/64 Test #52: Noise field is reproducible with the same seed .....................................   Passed    0.01 sec
      Start 53: Noise field differs between seeds
53/64 Test #53: Noise field differs between seeds ..................................................   Passed    0.01 sec
      Start 54: Spiral at sinkBlend=0 matches pure vortex
54/64 Test #54: Spiral at sinkBlend=0 matches pure vortex ..........................................   Passed    0.01 sec
      Start 55: Spiral at sinkBlend=1 matches pure sink
55/64 Test #55: Spiral at sinkBlend=1 matches pure sink ............................................   Passed    0.01 sec
      Start 56: Custom y_expression = "y" evaluates to world y-coordinate
56/64 Test #56: Custom y_expression = "y" evaluates to world y-coordinate ..........................   Passed    0.01 sec
      Start 57: Custom t expression evaluates to step*dt
57/64 Test #57: Custom t expression evaluates to step*dt ...........................................   Passed    0.01 sec
      Start 58: Invalid custom expression throws
58/64 Test #58: Invalid custom expression throws ...................................................   Passed    0.01 sec
      Start 59: Empty layers produces all-zero output
59/64 Test #59: Empty layers produces all-zero output ..............................................   Passed    0.01 sec
      Start 60: Layer strength multiplies contribution
60/64 Test #60: Layer strength multiplies contribution .............................................   Passed    0.01 sec
      Start 61: FieldWriter::write() creates the HDF5 file
61/64 Test #61: FieldWriter::write() creates the HDF5 file .........................................   Passed    0.01 sec
      Start 62: FieldWriter::write() stores vx/vy with correct dimensions [steps][height][width]
62/64 Test #62: FieldWriter::write() stores vx/vy with correct dimensions [steps][height][width] ...   Passed    0.01 sec
      Start 63: FieldWriter::write() stores correct metadata attributes
63/64 Test #63: FieldWriter::write() stores correct metadata attributes ............................   Passed    0.01 sec
      Start 64: FieldWriter::write() vx/vy values match generateTimeSeries() output
64/64 Test #64: FieldWriter::write() vx/vy values match generateTimeSeries() output ................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 64

Total Test time (real) =   0.40 sec
(base) rylei@fedora:~/Spring26/CS6030/Final/vector-field-analysis$ cmake --version
which cmake
type -a cmake
cmake version 4.3.1

CMake suite maintained and supported by Kitware (kitware.com/cmake).
~/.local/share/mise/installs/cmake/4.3.1/cmake-4.3.1-linux-x86_64/bin/cmake
cmake is /home/rylei/.local/share/mise/installs/cmake/4.3.1/cmake-4.3.1-linux-x86_64/bin/cmake
cmake is /usr/bin/cmake
cmake is /usr/bin/cmake
cmake is /bin/cmake
(base) rylei@fedora:~/Spring26/CS6030/Final/vector-field-analysis$ # keep using the newer cmake, but add the policy flag
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_POLICY_VERSION_MINIMUM=3.5

# or temporarily force Fedora’s system cmake if it is /usr/bin/cmake
/usr/bin/cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
CMake Deprecation Warning at build/_deps/eigen-src/CMakeLists.txt:2 (cmake_minimum_required):
  Compatibility with CMake < 3.10 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.


-- Performing Test COMPILER_SUPPORT_std=cpp03
-- Performing Test COMPILER_SUPPORT_std=cpp03 - Success
-- Standard libraries to link to explicitly: none
-- Found unsuitable Qt version "" from NOTFOUND
-- Qt4 not found, so disabling the mandelbrot and opengl demos
-- Could NOT find CHOLMOD (missing: CHOLMOD_INCLUDES CHOLMOD_LIBRARIES) 
-- Could NOT find UMFPACK (missing: UMFPACK_INCLUDES UMFPACK_LIBRARIES) 
-- Could NOT find KLU (missing: KLU_INCLUDES KLU_LIBRARIES) 
-- Could NOT find SuperLU (missing: SUPERLU_INCLUDES SUPERLU_LIBRARIES SUPERLU_VERSION_OK) (Required is at least version "4.0")
-- Checking for one of the modules 'hwloc'
-- A version of Pastix has been found but pastix_nompi.h does not exist in the include directory. Because Eigen tests require a version without MPI, we disable the Pastix backend.
-- 
-- Configured Eigen 3.4.0
-- 
-- Available targets (use: cmake --build . --target TARGET):
-- ---------+--------------------------------------------------------------
-- Target   |   Description
-- ---------+--------------------------------------------------------------
-- install  | Install Eigen. Headers will be installed to:
--          |     <CMAKE_INSTALL_PREFIX>/<INCLUDE_INSTALL_DIR>
--          |   Using the following values:
--          |     CMAKE_INSTALL_PREFIX: /usr/local
--          |     INCLUDE_INSTALL_DIR:  include/eigen3
--          |   Change the install location of Eigen headers using:
--          |     cmake . -DCMAKE_INSTALL_PREFIX=yourprefix
--          |   Or:
--          |     cmake . -DINCLUDE_INSTALL_DIR=yourdir
-- doc      | Generate the API documentation, requires Doxygen & LaTeX
-- blas     | Build BLAS library (not the same thing as Eigen)
-- uninstall| Remove files installed by the install target
-- ---------+--------------------------------------------------------------
-- 
-- Configuring done (3.1s)
-- Generating done (0.1s)
-- Build files have been written to: /home/rylei/Spring26/CS6030/Final/vector-field-analysis/build
-- The CXX compiler identification is GNU 14.3.1
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found HDF5: /usr/lib64/libhdf5.so;/usr/lib64/libhdf5_cpp.so;/usr/lib64/libhdf5.so (found version "1.12.1") found components: C CXX
-- The C compiler identification is GNU 14.3.1
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Performing Test COMPILER_SUPPORT_std=cpp03
-- Performing Test COMPILER_SUPPORT_std=cpp03 - Success
-- Standard libraries to link to explicitly: none
-- The Fortran compiler identification is GNU 14.3.1
-- Detecting Fortran compiler ABI info
-- Detecting Fortran compiler ABI info - done
-- Check for working Fortran compiler: /usr/bin/gfortran - skipped
-- Found unsuitable Qt version "" from NOTFOUND
-- Qt4 not found, so disabling the mandelbrot and opengl demos
-- Could NOT find CHOLMOD (missing: CHOLMOD_INCLUDES CHOLMOD_LIBRARIES) 
-- Could NOT find UMFPACK (missing: UMFPACK_INCLUDES UMFPACK_LIBRARIES) 
-- Could NOT find KLU (missing: KLU_INCLUDES KLU_LIBRARIES) 
-- Could NOT find SuperLU (missing: SUPERLU_INCLUDES SUPERLU_LIBRARIES SUPERLU_VERSION_OK) (Required is at least version "4.0")
-- Checking for one of the modules 'hwloc'
-- A version of Pastix has been found but pastix_nompi.h does not exist in the include directory. Because Eigen tests require a version without MPI, we disable the Pastix backend.
-- 
-- Configured Eigen 3.4.0
-- 
-- Available targets (use: cmake --build . --target TARGET):
-- ---------+--------------------------------------------------------------
-- Target   |   Description
-- ---------+--------------------------------------------------------------
-- install  | Install Eigen. Headers will be installed to:
--          |     <CMAKE_INSTALL_PREFIX>/<INCLUDE_INSTALL_DIR>
--          |   Using the following values:
--          |     CMAKE_INSTALL_PREFIX: /usr/local
--          |     INCLUDE_INSTALL_DIR:  include/eigen3
--          |   Change the install location of Eigen headers using:
--          |     cmake . -DCMAKE_INSTALL_PREFIX=yourprefix
--          |   Or:
--          |     cmake . -DINCLUDE_INSTALL_DIR=yourdir
-- doc      | Generate the API documentation, requires Doxygen & LaTeX
-- blas     | Build BLAS library (not the same thing as Eigen)
-- uninstall| Remove files installed by the install target
-- ---------+--------------------------------------------------------------
-- 
-- Configuring done (25.2s)
-- Generating done (0.1s)
-- Build files have been written to: /home/rylei/Spring26/CS6030/Final/vector-field-analysis/build
(base) rylei@fedora:~/Spring26/CS6030/Final/vector-field-analysis$

(base) rylei@fedora:~/Spring26/CS6030/Final/vector-field-analysis$ mise run deps
mise run build
mise run test
[deps] $ if command -v apt-get &>/dev/null; then
[sudo] password for rylei: 
Package                           Arch   Version                    Repository        Size
Upgrading:
 brave-browser                    x86_64 1.89.132-1                 brave-browse 421.8 MiB
   replacing brave-browser        x86_64 1.88.138-1                 brave-browse 422.8 MiB
 google-chrome-stable             x86_64 147.0.7727.55-1            google-chrom 394.7 MiB
   replacing google-chrome-stable x86_64 146.0.7680.177-1           google-chrom 395.2 MiB

Transaction Summary:
 Upgrading:          2 packages
 Replacing:          2 packages

Is this ok [y/N]: y
[1/6] Verify package files                        100% |   1.0   B/s |   2.0   B |  00m02s
[2/6] Prepare transaction                         100% |   7.0   B/s |   4.0   B |  00m01s
[3/6] Upgrading google-chrome-stable-0:147.0.7727 100% |  27.3 MiB/s | 394.8 MiB |  00m14s
[4/6] Upgrading brave-browser-0:1.89.132-1.x86_64 100% |  27.1 MiB/s | 421.8 MiB |  00m16s
[5/6] Removing google-chrome-stable-0:146.0.7680. 100% |   5.0 KiB/s | 274.0   B |  00m00s
[6/6] Removing brave-browser-0:1.88.138-1.x86_64  100% | 255.0   B/s | 252.0   B |  00m01s
Package "hdf5-1.12.1-21.fc41.x86_64" is already installed.
Package "cppcheck-2.18.3-1.fc41.x86_64" is already installed.

Nothing to do.
[configure] $ cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_C…
-- Found HDF5: /usr/lib64/libhdf5.so;/usr/lib64/libhdf5_cpp.so;/usr/lib64/libhdf5.so (found version "1.12.1") found components: C CXX
CMake Deprecation Warning at build/_deps/eigen-src/CMakeLists.txt:2 (cmake_minimum_required):
  Compatibility with CMake < 3.10 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.


-- Performing Test COMPILER_SUPPORT_std=cpp03
-- Performing Test COMPILER_SUPPORT_std=cpp03 - Success
-- Standard libraries to link to explicitly: none
-- Found unsuitable Qt version "" from NOTFOUND
-- Qt4 not found, so disabling the mandelbrot and opengl demos
-- Could NOT find CHOLMOD (missing: CHOLMOD_INCLUDES CHOLMOD_LIBRARIES) 
-- Could NOT find UMFPACK (missing: UMFPACK_INCLUDES UMFPACK_LIBRARIES) 
-- Could NOT find KLU (missing: KLU_INCLUDES KLU_LIBRARIES) 
-- Could NOT find SuperLU (missing: SUPERLU_INCLUDES SUPERLU_LIBRARIES SUPERLU_VERSION_OK) (Required is at least version "4.0")
-- Checking for one of the modules 'hwloc'
-- A version of Pastix has been found but pastix_nompi.h does not exist in the include directory. Because Eigen tests require a version without MPI, we disable the Pastix backend.
-- 
-- Configured Eigen 3.4.0
-- 
-- Available targets (use: cmake --build . --target TARGET):
-- ---------+--------------------------------------------------------------
-- Target   |   Description
-- ---------+--------------------------------------------------------------
-- install  | Install Eigen. Headers will be installed to:
--          |     <CMAKE_INSTALL_PREFIX>/<INCLUDE_INSTALL_DIR>
--          |   Using the following values:
--          |     CMAKE_INSTALL_PREFIX: /usr/local
--          |     INCLUDE_INSTALL_DIR:  include/eigen3
--          |   Change the install location of Eigen headers using:
--          |     cmake . -DCMAKE_INSTALL_PREFIX=yourprefix
--          |   Or:
--          |     cmake . -DINCLUDE_INSTALL_DIR=yourdir
-- doc      | Generate the API documentation, requires Doxygen & LaTeX
-- blas     | Build BLAS library (not the same thing as Eigen)
-- uninstall| Remove files installed by the install target
-- ---------+--------------------------------------------------------------
-- 
-- Configuring done (23.2s)
-- Generating done (0.1s)
-- Build files have been written to: /home/rylei/Spring26/CS6030/Final/vector-field-analysis/build
[build] $ cmake --build build
[125/125] Linking CXX executable bins/simulator/tests/simulator_tests
Finished in 189.37s
[configure] $ cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_C…
CMake Deprecation Warning at build/_deps/eigen-src/CMakeLists.txt:2 (cmake_minimum_required):
  Compatibility with CMake < 3.10 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.


-- Performing Test COMPILER_SUPPORT_std=cpp03
-- Performing Test COMPILER_SUPPORT_std=cpp03 - Success
-- Standard libraries to link to explicitly: none
-- Found unsuitable Qt version "" from NOTFOUND
-- Qt4 not found, so disabling the mandelbrot and opengl demos
-- Could NOT find CHOLMOD (missing: CHOLMOD_INCLUDES CHOLMOD_LIBRARIES) 
-- Could NOT find UMFPACK (missing: UMFPACK_INCLUDES UMFPACK_LIBRARIES) 
-- Could NOT find KLU (missing: KLU_INCLUDES KLU_LIBRARIES) 
-- Could NOT find SuperLU (missing: SUPERLU_INCLUDES SUPERLU_LIBRARIES SUPERLU_VERSION_OK) (Required is at least version "4.0")
-- Checking for one of the modules 'hwloc'
-- A version of Pastix has been found but pastix_nompi.h does not exist in the include directory. Because Eigen tests require a version without MPI, we disable the Pastix backend.
-- 
-- Configured Eigen 3.4.0
-- 
-- Available targets (use: cmake --build . --target TARGET):
-- ---------+--------------------------------------------------------------
-- Target   |   Description
-- ---------+--------------------------------------------------------------
-- install  | Install Eigen. Headers will be installed to:
--          |     <CMAKE_INSTALL_PREFIX>/<INCLUDE_INSTALL_DIR>
--          |   Using the following values:
--          |     CMAKE_INSTALL_PREFIX: /usr/local
--          |     INCLUDE_INSTALL_DIR:  include/eigen3
--          |   Change the install location of Eigen headers using:
--          |     cmake . -DCMAKE_INSTALL_PREFIX=yourprefix
--          |   Or:
--          |     cmake . -DINCLUDE_INSTALL_DIR=yourdir
-- doc      | Generate the API documentation, requires Doxygen & LaTeX
-- blas     | Build BLAS library (not the same thing as Eigen)
-- uninstall| Remove files installed by the install target
-- ---------+--------------------------------------------------------------
-- 
-- Configuring done (3.0s)
-- Generating done (0.1s)
-- Build files have been written to: /home/rylei/Spring26/CS6030/Final/vector-field-analysis/build
[build] $ cmake --build build
ninja: no work to do.
[test] $ ctest --test-dir build --output-on-failure
Test project /home/rylei/Spring26/CS6030/Final/vector-field-analysis/build
      Start  1: Vector magnitude
 1/64 Test  #1: Vector magnitude ...................................................................   Passed    0.00 sec
      Start  2: Vector unitVector has magnitude 1
 2/64 Test  #2: Vector unitVector has magnitude 1 ..................................................   Passed    0.00 sec
      Start  3: Vector unitVector preserves direction
 3/64 Test  #3: Vector unitVector preserves direction ..............................................   Passed    0.00 sec
      Start  4: dotProduct
 4/64 Test  #4: dotProduct .........................................................................   Passed    0.00 sec
      Start  5: almostParallel
 5/64 Test  #5: almostParallel .....................................................................   Passed    0.00 sec
      Start  6: Vec2 unitVector for zero vector returns zero vector
 6/64 Test  #6: Vec2 unitVector for zero vector returns zero vector ................................   Passed    0.00 sec
      Start  7: almostParallel threshold boundary
 7/64 Test  #7: almostParallel threshold boundary ..................................................   Passed    0.00 sec
      Start  8: dotProduct with zero vector
 8/64 Test  #8: dotProduct with zero vector ........................................................   Passed    0.00 sec
      Start  9: StreamLine initialises with start point
 9/64 Test  #9: StreamLine initialises with start point ............................................   Passed    0.00 sec
      Start 10: Streamline path grows when points are appended
10/64 Test #10: Streamline path grows when points are appended .....................................   Passed    0.00 sec
      Start 11: neighborInVectorDirection advances in vector direction
11/64 Test #11: neighborInVectorDirection advances in vector direction .............................   Passed    0.01 sec
      Start 12: traceStreamlineStep assigns a streamline
12/64 Test #12: traceStreamlineStep assigns a streamline ...........................................   Passed    0.01 sec
      Start 13: neighborInVectorDirection pointing left decreases column
13/64 Test #13: neighborInVectorDirection pointing left decreases column ...........................   Passed    0.01 sec
      Start 14: neighborInVectorDirection pointing up increases row
14/64 Test #14: neighborInVectorDirection pointing up increases row ................................   Passed    0.01 sec
      Start 15: neighborInVectorDirection pointing down decreases row
15/64 Test #15: neighborInVectorDirection pointing down decreases row ..............................   Passed    0.01 sec
      Start 16: neighborInVectorDirection clamped at left edge
16/64 Test #16: neighborInVectorDirection clamped at left edge .....................................   Passed    0.01 sec
      Start 17: neighborInVectorDirection clamped at right edge
17/64 Test #17: neighborInVectorDirection clamped at right edge ....................................   Passed    0.01 sec
      Start 18: neighborInVectorDirection clamped at top edge
18/64 Test #18: neighborInVectorDirection clamped at top edge ......................................   Passed    0.01 sec
      Start 19: neighborInVectorDirection clamped at bottom edge
19/64 Test #19: neighborInVectorDirection clamped at bottom edge ...................................   Passed    0.01 sec
      Start 20: joinStreamlines merges end path into start
20/64 Test #20: joinStreamlines merges end path into start .........................................   Passed    0.01 sec
      Start 21: joinStreamlines with null start is a no-op
21/64 Test #21: joinStreamlines with null start is a no-op .........................................   Passed    0.01 sec
      Start 22: joinStreamlines on equal pointers is a no-op
22/64 Test #22: joinStreamlines on equal pointers is a no-op .......................................   Passed    0.01 sec
      Start 23: tracing multiple steps builds a path without crash
23/64 Test #23: tracing multiple steps builds a path without crash .................................   Passed    0.01 sec
      Start 24: tracing into an occupied cell triggers merge without crash
24/64 Test #24: tracing into an occupied cell triggers merge without crash .........................   Passed    0.01 sec
      Start 25: FieldReader::read() throws for nonexistent file
25/64 Test #25: FieldReader::read() throws for nonexistent file ....................................   Passed    0.01 sec
      Start 26: FieldReader::read() returns correct step/row/col dimensions
26/64 Test #26: FieldReader::read() returns correct step/row/col dimensions ........................   Passed    0.01 sec
      Start 27: FieldReader::read() populates xMin/xMax/yMin/yMax
27/64 Test #27: FieldReader::read() populates xMin/xMax/yMin/yMax ..................................   Passed    0.01 sec
      Start 28: FieldReader::read() Vec2 values match written floats
28/64 Test #28: FieldReader::read() Vec2 values match written floats ...............................   Passed    0.01 sec
      Start 29: FieldReader::read() throws when vx dataset is missing
29/64 Test #29: FieldReader::read() throws when vx dataset is missing ..............................   Passed    0.01 sec
      Start 30: Vortex field produces unit vectors
30/64 Test #30: Vortex field produces unit vectors .................................................   Passed    0.01 sec
      Start 31: Vortex field is perpendicular to radius
31/64 Test #31: Vortex field is perpendicular to radius ............................................   Passed    0.01 sec
      Start 32: Vortex field is zero at origin
32/64 Test #32: Vortex field is zero at origin .....................................................   Passed    0.01 sec
      Start 33: generateTimeSeries() returns correct 3D dimensions
33/64 Test #33: generateTimeSeries() returns correct 3D dimensions .................................   Passed    0.01 sec
      Start 34: Vortex generateTimeSeries() produces unit magnitude away from origin
34/64 Test #34: Vortex generateTimeSeries() produces unit magnitude away from origin ...............   Passed    0.01 sec
      Start 35: Uniform field at angle=0 points right
35/64 Test #35: Uniform field at angle=0 points right ..............................................   Passed    0.01 sec
      Start 36: Uniform field at angle=90 points up
36/64 Test #36: Uniform field at angle=90 points up ................................................   Passed    0.01 sec
      Start 37: Source field points away from center
37/64 Test #37: Source field points away from center ...............................................   Passed    0.01 sec
      Start 38: Sink field points toward center
38/64 Test #38: Sink field points toward center ....................................................   Passed    0.01 sec
      Start 39: Saddle field has opposite signs in x and y relative to center
39/64 Test #39: Saddle field has opposite signs in x and y relative to center ......................   Passed    0.01 sec
      Start 40: Spiral field is between vortex and sink
40/64 Test #40: Spiral field is between vortex and sink ............................................   Passed    0.01 sec
      Start 41: Viscous decay reduces magnitude over steps
41/64 Test #41: Viscous decay reduces magnitude over steps .........................................   Passed    0.01 sec
      Start 42: Custom x_expression = "x" evaluates to world x-coordinate
42/64 Test #42: Custom x_expression = "x" evaluates to world x-coordinate ..........................   Passed    0.01 sec
      Start 43: Superposition sums field contributions
43/64 Test #43: Superposition sums field contributions .............................................   Passed    0.01 sec
      Start 44: parseFile() uses defaults when [simulation] section absent
44/64 Test #44: parseFile() uses defaults when [simulation] section absent .........................   Passed    0.01 sec
      Start 45: parseFile() reads [simulation] values correctly
45/64 Test #45: parseFile() reads [simulation] values correctly ....................................   Passed    0.01 sec
      Start 46: parseFile() defaults to one vortex layer when [[layers]] absent
46/64 Test #46: parseFile() defaults to one vortex layer when [[layers]] absent ....................   Passed    0.01 sec
      Start 47: parseFile() parses all 8 field types from [[layers]]
47/64 Test #47: parseFile() parses all 8 field types from [[layers]] ...............................   Passed    0.01 sec
      Start 48: parseFile() reads layer parameters
48/64 Test #48: parseFile() reads layer parameters .................................................   Passed    0.01 sec
      Start 49: parseFile() throws for nonexistent file
49/64 Test #49: parseFile() throws for nonexistent file ............................................   Passed    0.01 sec
      Start 50: parseFile() throws for unknown field type
50/64 Test #50: parseFile() throws for unknown field type ..........................................   Passed    0.01 sec
      Start 51: Noise field is non-constant spatially
51/64 Test #51: Noise field is non-constant spatially ..............................................   Passed    0.01 sec
      Start 52: Noise field is reproducible with the same seed
52/64 Test #52: Noise field is reproducible with the same seed .....................................   Passed    0.01 sec
      Start 53: Noise field differs between seeds
53/64 Test #53: Noise field differs between seeds ..................................................   Passed    0.01 sec
      Start 54: Spiral at sinkBlend=0 matches pure vortex
54/64 Test #54: Spiral at sinkBlend=0 matches pure vortex ..........................................   Passed    0.01 sec
      Start 55: Spiral at sinkBlend=1 matches pure sink
55/64 Test #55: Spiral at sinkBlend=1 matches pure sink ............................................   Passed    0.01 sec
      Start 56: Custom y_expression = "y" evaluates to world y-coordinate
56/64 Test #56: Custom y_expression = "y" evaluates to world y-coordinate ..........................   Passed    0.01 sec
      Start 57: Custom t expression evaluates to step*dt
57/64 Test #57: Custom t expression evaluates to step*dt ...........................................   Passed    0.01 sec
      Start 58: Invalid custom expression throws
58/64 Test #58: Invalid custom expression throws ...................................................   Passed    0.01 sec
      Start 59: Empty layers produces all-zero output
59/64 Test #59: Empty layers produces all-zero output ..............................................   Passed    0.01 sec
      Start 60: Layer strength multiplies contribution
60/64 Test #60: Layer strength multiplies contribution .............................................   Passed    0.01 sec
      Start 61: FieldWriter::write() creates the HDF5 file
61/64 Test #61: FieldWriter::write() creates the HDF5 file .........................................   Passed    0.01 sec
      Start 62: FieldWriter::write() stores vx/vy with correct dimensions [steps][height][width]
62/64 Test #62: FieldWriter::write() stores vx/vy with correct dimensions [steps][height][width] ...   Passed    0.01 sec
      Start 63: FieldWriter::write() stores correct metadata attributes
63/64 Test #63: FieldWriter::write() stores correct metadata attributes ............................   Passed    0.01 sec
      Start 64: FieldWriter::write() vx/vy values match generateTimeSeries() output
64/64 Test #64: FieldWriter::write() vx/vy values match generateTimeSeries() output ................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 64

Total Test time (real) =   0.40 sec
Finished in 3.60s
(base) rylei@fedora:~/Spring26/CS6030/Final/vector-field-analysis$ 



# working build path:
```
rm -rf build
cmake -S . -B build -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_POLICY_VERSION_MINIMUM=3.5
cmake --build build -j
ctest --test-dir build --output-on-failure
```

# clean options:
```
# option 1: keep using mise cmake, but always include the policy flag
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_POLICY_VERSION_MINIMUM=3.5

# option 2: bypass mise cmake and use Fedora's system cmake
/usr/bin/cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```


```
```
```
```
```
```
