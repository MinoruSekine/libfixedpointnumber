# libfixedpointnumber

libfixedpointnumber is a Library for fixed point number by C++11.

![](https://github.com/MinoruSekine/libfixedpointnumber/workflows/Check%20build/badge.svg?branch=master)

## Build

Is this section, you can know how to integrate this into your project
and some check methods on your environment.

### Integrate into your project

Put include/fixedpointnumber.h into a directory
enabled to include from your project,
and include it.

### List of build targets

| `make` target | How it works |
----|----
| `build-test` | Build unit tests (only build, not run) |
| `build-sample` | Build sample programs (only build, not run) |
| `check` | Process `cppcheck` and `cpplint` |
| `clean` | Remove generated files |
| `clean-doc` | Remove generated Doxygen document files |
| `coverage` | Generate unit tests coverage report (Must use with `BUILD_TYPE=coverage`) |
| `cppcheck` | Static analytics by `cppcheck` |
| `cpplint` | Lint by `cpplint` |
| `doc` | Generate doxygen documents into out/doc |
| `run-sample` | Build (if necessary) and run sample programs |
| `run-test` | Build (if necessary) and run unit tests |

### Build and run unit tests

1. Install Google Test (https://github.com/google/googletest)
1. `make run-test` in this directory

#### Build coverage report

1. Install `gcovr`
1. `make BUILD_TYPE=coverage coverage`, so html report is put into `out/coverage_html/`

### Build and run sample programs

1. `make run-sample` in this directory

### Checks

Some check targets are available in build by Makefile

#### cpplint

- Install `cpplint.py`
- Set that directory in your environment variable `PATH`
- `make cpplint`

or

- `make CPPLINT=your/installed/directory/cpplint.py cpplint`

#### cppcheck

- Install `cppechck` into your environment
- `make cppcheck`

### Generate Doxygen document files

- Install `doxygen` into your environment
- `make doc`

### For Windows (Visual Studio)

- The solution file to build samples and tests with Visual Studio is available
as build/win_vs/libfixedpointnumber/libfixedpointnumber.sln
- Google Test Framework will be recovered automatically at opening solution file
