# Contributing to libfixedpointnumber

This document tells you how to contribute to libfixedpointnumber
and rules to keep on contributing.

## Legal prerequisites

If you hope to contribute,
you have to accept libfixedpointnumber is adopting LGPLv3
( [GNU Lesser General Public License version 3](https://www.gnu.org/licenses/lgpl.html) ).

## Coding standards

All contributions must conform [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

### Our additonal rules to [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

#### Types

- You can use type suffix `_t` to represent compatibility to built-in types
  - Example:
```c++
using my_favorite_integral_t = int32_t;  // OK.

// NG. This class is incompatible to built-in types and is not trivial.
class Foo {
 public:
  Foo() {
    // Some Foo-specific initializations.
  }

  ~Foo() {
    // Some Foo-specific uninitializations.
  }
};

```

#### `return`

- 2 or more `return` in a function are allowed only when they increase readability, like as simply parameter check
  - If not, 2 or more `return` should be prohibited because it can be difficult to trace flow of a function
```C++
// OK. It increases readability, `return` if simply parameter check is faield.
bool process_something(const char* str) {
  if (!str) {
    return false;
  }

  // Some complex processes...
  return true;
}

// Also this is OK. I love this style more, but I can't force it, haha.
bool process_more_something(const char* str) {
  bool is_parameter_valid = false;
  if (str) {
    // Some complex processes...
	is_parameter_valid = true;
  } else {
    is_parameter_valid = false;
  }
  return is_parameter_valid;
}
```

## Submit patches

1. Folk repository
1. Commit and push your patch to remote branch
1. Make pull request to master branch of master repository
1. Wait approval
