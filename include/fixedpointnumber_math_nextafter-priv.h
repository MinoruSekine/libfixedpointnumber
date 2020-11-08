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

#ifndef INCLUDE_FIXEDPOINTNUMBER_MATH_NEXTAFTER_PRIV_H_
#define INCLUDE_FIXEDPOINTNUMBER_MATH_NEXTAFTER_PRIV_H_

#include "fixedpointnumber.h"
#include "fixedpointnumber_limits.h"
#include "fixedpointnumber_math_signbit-priv.h"

#ifndef FIXEDPOINTNUMBER_MATH_INTERNAL
#error Do not include this file directly, ixedpointnumber_math.h instead.
#endif

namespace fixedpointnumber {

/// Compute next after value.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param x Value computed next after
/// @param y Specifiies direction
///
/// @return Value next after x in direction of y
///         which has smallest differenct between x and y
///
/// @relates fixed_t
template <typename IntType, std::size_t Q>
constexpr fixed_t<IntType, Q> fixed_nextafter(fixed_t<IntType, Q> x,
                                              fixed_t<IntType, Q> y) {
  using fixed_t = fixed_t<IntType, Q>;
  return (fixed_signbit(y)
          ? (x + numeric_limits<fixed_t>::min())
          : (x - numeric_limits<fixed_t>::min()));
}

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_MATH_NEXTAFTER_PRIV_H_
