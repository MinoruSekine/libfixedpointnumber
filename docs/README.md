# libfixedpointnumber

libfixedpointnumber is a Library for fixed point number by C++11.

![](https://github.com/MinoruSekine/libfixedpointnumber/workflows/Check%20build/badge.svg?branch=master)

## Summary

Usual progrmas computing fixed point number,

- Bit shift operations are necessary, and they lose readability
- Types which holding fixed point numbers are just standard integral types,
  it also lose readability
- Not type-safe because types for different-spec fixed point numbers are
  just standard integral types
  (they include no Q bit width information anywhere)

If libfixedpointnumber is used in programs computing fixed point number...

- Bit shift operations can be hidden
- Specs of fixed point number
  (holding standard integral types
  and how many bits assigned for fractional part)
  are explicit
- Can not substitute a fixed point number into another spec fixed point number
  without explicit casting

libfixedpointnumber provides...

- Template class `fixed_t` to represent fixed point number
- Arithmetic and comparison operators for `fixed_t`
- Casting as conversion between different spec `fixed_t`
  (different bit width or different Q bit width)
- Convert from string like as `"3.14"` into `fixed_t`
- Functions for `fixed_t` which are compatible to part of functions in `cmath`
- Most members and releated functions of `fixed_t`
  are provided as constexpr functions

## API Reference

- [By Doxygen](https://minorusekine.github.io/libfixedpointnumber/Doxygen/html/)

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
| `all` | Same as `build-all` |
| `build-all` | `build-sample` and `build-test` |
| `build-sample` | Build sample programs |
| `build-test` | Build unit tests |
| `check` | Process `cppcheck` and `cpplint` |
| `clean` | Remove generated files |
| `coverage` | Create coverage report into out/site/coverage (Must use with `BUILD_TYPE=coverage`) |
| `cppcheck` | Static analytics by `cppcheck` |
| `cpplint` | Lint by `cpplint` |
| `doc` | `coverage` and `doxygen` |
| `doxygen` | Generate doxygen HTML documents into out/site/Doxygen |
| `latex` | Generate doxygen LaTeX documents into out/site/Doxygen |
| `run-all` | `run-sample` and `run-test` |
| `run-sample` | Build (if necessary) and run sample programs |
| `run-test` | Build (if necessary) and run unit tests |
| `site` | Build tree for [project site](https://minorusekine.github.io/libfixedpointnumber/) |

### Build options

#### `BUILD_TYPE`

| `BUILD_TYPE` | How it works |
----|----
| `debug` | All optimizations are disabled in build |
| `release` | Optimizations are enabled in build |
| `coverage` | Options for build `coverage` as `make` target |

- In `coverage`, optimization are disabled
  and some additional information
  to get coverage report will be generated

### Build and run unit tests

1. Install [Google Test](https://github.com/google/googletest)
1. `make run-test` in this directory

#### Build coverage report

1. Install `gcovr`
1. `make BUILD_TYPE=coverage coverage`,
   so html report is put into `out/coverage_html/`

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

- The solution file to build samples and tests with Visual Studio
  is available as build/win_vs/libfixedpointnumber/libfixedpointnumber.sln
- Google Test Framework will be recovered automatically
  at opening solution file

## Environments

As of 2021/02/12,
all tests succeed and all samples are working well on following environments

| OS | Compiler |
----|----
| FreeBSD 12.2-STABLE | clang++ |
| macOS Catalina 10.15.7 | g++ (symlink to clang) |
| Ubuntu 16.04 | g++ |
| Ubuntu 18.04 | g++ |
| Windows Server 2016 Datacenter | Visual C++ |
