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

#ifndef INCLUDE_FIXEDPOINTNUMBER_MATH_FMA_PRIV_H_
#define INCLUDE_FIXEDPOINTNUMBER_MATH_FMA_PRIV_H_

#include "fixedpointnumber.h"

#ifndef FIXEDPOINTNUMBER_MATH_INTERNAL
#error Do not include this file directly, fixedpointnumber_math.h instead.
#endif

namespace fixedpointnumber {

/// Compute x * y + z with less precision lost.
///
/// operator* for fixed_t may lost precision.
/// So if we use x * y + z,
/// there may be 2 presicion lost at multiply and add.
/// This function have only 1 precision lost afraid at finally addition.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param x Multiplicand
/// @param y Multiplier
/// @param z Value to add
///
/// @return x * y + z with less precision lost
///
/// @relates fixed_t
template <typename IntType, std::size_t Q>
constexpr fixed_t<IntType, Q> fixed_fma(fixed_t<IntType, Q> x,
                                        fixed_t<IntType, Q> y,
                                        fixed_t<IntType, Q> z) {
  using internal_fixed_t = decltype(fixedpointnumber::fixed_mul(x, y));
  return static_cast<fixed_t<IntType, Q>>(fixed_mul(x, y)
                                          + static_cast<internal_fixed_t>(z));
}

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_MATH_FMA_PRIV_H_
