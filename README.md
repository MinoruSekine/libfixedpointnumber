# libfixedpointnumber
libfixedpointnumber is a Library for fixed point number by C++11.

## Build

### Integrate into your project

Put include/fixedpointnumber.h into a directory
enabled to include from your project,
and include it.

### Build unit tests

1. Install Google Test (https://github.com/google/googletest)
1. `make test` in this directory

### Checks

Some check targets are available in build by Makefile

| `make` target | How it works |
----|----
| cpplint | Lint by `cpplint` |
| cppcheck | Static analytics by `cppcheck` |
| check | Process all checks above |

#### cpplint

- Install `cpplint.py`
- Set that directory in your environment variable `PATH`
- `make cpplint`

or

- `make CPPLINT=your/installed/directory/cpplint.py`

#### cppcheck

- Install `cppechck` into your environment
- `make cppcheck`
