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

