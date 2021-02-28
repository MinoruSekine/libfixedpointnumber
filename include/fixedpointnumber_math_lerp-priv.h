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

#ifndef INCLUDE_FIXEDPOINTNUMBER_MATH_LERP_PRIV_H_
#define INCLUDE_FIXEDPOINTNUMBER_MATH_LERP_PRIV_H_

#include "fixedpointnumber.h"
#include "fixedpointnumber_math.h"

#ifndef FIXEDPOINTNUMBER_MATH_INTERNAL
#error Do not include this file directly, fixedpointnumber_math.h instead.
#endif

namespace fixedpointnumber {

/// Compute the lerp.
///
/// Compute linear interpolation of 2 parameters for 3rd parameter.
/// If 3rd parameter is greater than 1,
/// it will be computed extrapolation.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param a A side of range to interpolate
/// @param b Another side of range to interpolate
/// @param t Interpolate coef, 0 represents a, and 1 represents 1
///
/// @return Lerp of [a, b] with coef t
///
/// @relates fixed_t
template <typename IntType, std::size_t Q>
constexpr fixed_t<IntType, Q> fixed_lerp(fixed_t<IntType, Q> a,
                                         fixed_t<IntType, Q> b,
                                         fixed_t<IntType, Q> t) {
  using wider_fixed_t = decltype(fixed_mul(t, (b - a)));
  return static_cast<fixed_t<IntType, Q>>(static_cast<wider_fixed_t>(a)
                                          + fixed_mul(t, (b - a)));
}

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_MATH_LERP_PRIV_H_
