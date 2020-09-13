# libfixedpointnumber

libfixedpointnumber is a Library for fixed point number by C++11.

![](https://github.com/MinoruSekine/libfixedpointnumber/workflows/Check%20build/badge.svg?branch=master)

## API Reference

- See https://minorusekine.github.io/libfixedpointnumber/Doxygen/html/

## Integrate into your project

1. Include header files in libfixedpointnumber/include/
1. Add libfixedpointnumber/include/ into your include path.
1. Compile your codes

It is not necessary to build and link static link library of libfixedpointnumber
because all implementations are available in header files.

## Usage

Following simple sample code provides to calculate half of input number
with converting precision
(Latest code of this is in interactive_sample/).

```C++
#include <cstdint>
#include <iostream>

#include "fixedpointnumber.h"

using fixed_Q7_t = fixedpointnumber::fixed_t<int16_t, 7>;
using fixed_Q8_t = fixedpointnumber::fixed_t<int16_t, 8>;

int main(int, char**) {
  std::cout << "Input number to divide (less than 128): ";

  fixed_Q7_t num(0);
  std::cin >> num;

  std::cout << "Half of "
            << num
            << " is "
            << fixed_Q8_t(num) / fixed_Q8_t(2)
            << std::endl;

  return 0;
}
```

You can see following items in this sample

- Input/Output stream operators are supported
- Overloaded basic arithmetic operators are available
- `fixed_t` can be construct from constant integer

## Build samples and unit tests

Makefile of libfixedpointnumber will provide followings on your environments

- Build and run unit tests
- Build and run sample programs
- Some checks
  - Coding rule check by cpplint
  - Static analysis by cppcheck
- Build documents with Doxygen

### List of build targets

| `make` target | How it works |
----|----
| `build-interactive-sample` | Build interactive sample programs (only build, not run) |
| `build-sample` | Build sample programs (only build, not run) |
| `build-test` | Build unit tests (only build, not run) |
| `check` | Process `cppcheck` and `cpplint` |
| `clean` | Remove generated files |
| `coverage` | Generate unit tests coverage report (Must use with `BUILD_TYPE=coverage`) |
| `cppcheck` | Static analytics by `cppcheck` |
| `cpplint` | Lint by `cpplint` |
| `doc` | Generate doxygen documents into out/doc |
| `run-all` | `run-sample` and `run-test` (interactive-sample is not included)|
| `run-sample` | Build (if necessary) and run sample programs |
| `run-test` | Build (if necessary) and run unit tests |

### Build options

#### `BUILD_TYPE`

| `BUILD_TYPE` | How it works |
----|----
| `debug` | All optimizations are disabled in build |
| `release` | Optimizations are enabled in build |
| `coverage` | Options for build `coverage` as `make` target, optimizatiosn are disabled and some additional information to get coverage report will be generated |

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
