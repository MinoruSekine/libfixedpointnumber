//
// Copyright 2020 Minoru Sekine
//
// This file is part of libfixedpointnumber.
//
// libfixedpointnumber is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libfixedpointnumber is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with libfixedpointnumber.  If not, see <http://www.gnu.org/licenses/>.

#include <cstdint>

#ifndef INCLUDE_FIXEDPOINTNUMBER_WIDER_INT_H_
#define INCLUDE_FIXEDPOINTNUMBER_WIDER_INT_H_

#ifndef FIXEDPOINTNUMBER_INTERNAL
#error Do not include this file directly, include fixedpointnumber.h instead.
#endif

namespace fixedpointnumber {

namespace impl {

/// Helper class to get wider type than specified int type.
///
/// @tparam int_t Type to get wider type
template <typename int_t>
class WiderIntType {
};

/// Specialized template helper class to get wider type than int8_t.
template<>
class WiderIntType<int8_t> {
 public:
  /// Wider type than int8_t.
  using type = int16_t;
};

/// Specialized template helper class to get wider type than int16_t.
template<>
class WiderIntType<int16_t> {
 public:
  /// Wider type than int16_t.
  using type = int32_t;
};

/// Specialized template helper class to get wider type than int32_t.
template<>
class WiderIntType<int32_t> {
 public:
  /// Wider type than int32_t.
  using type = int64_t;
};

/// Specialized template helper class to get wider type than uint8_t.
template<>
class WiderIntType<uint8_t> {
 public:
  /// Wider type than uint8_t.
  using type = uint16_t;
};

/// Specialized template helper class to get wider type than uint16_t.
template<>
class WiderIntType<uint16_t> {
 public:
  /// Wider type than uint16_t.
  using type = uint32_t;
};

/// Specialized template helper class to get wider type than uint32_t.
template<>
class WiderIntType<uint32_t> {
 public:
  /// Wider type than uint32_t.
  using type = uint64_t;
};

/// Alias tempalte to wider type than template argument int type.
template <typename int_t>
using wider_int_t = typename WiderIntType<int_t>::type;

}  // namespace impl

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_WIDER_INT_H_
