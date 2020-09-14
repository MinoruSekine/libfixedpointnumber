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

#ifndef INCLUDE_FIXEDPOINTNUMBER_MATH_MODF_PRIV_H_
#define INCLUDE_FIXEDPOINTNUMBER_MATH_MODF_PRIV_H_

#include "fixedpointnumber.h"
#include "fixedpointnumber_math.h"

#ifndef FIXEDPOINTNUMBER_MATH_INTERNAL
#error Do not include this file directly, ixedpointnumber_math.h instead.
#endif

namespace fixedpointnumber {

namespace impl {

template <typename T>
constexpr T get_integral_part(T x) {
  return ((x >= T(0))
          ? T(x.fixed_point_ & T::kIntegralPartMask, true)
          : -(get_integral_part(-x)));
}

template <typename T>
constexpr T get_fractional_part(T x) {
  return ((x >= T(0))
          ? T(x.fixed_point_ & T::kDecimalPartMask, true)
          : -(get_fractional_part(-x)));
}

}  // namespace impl

/// Split given fixed_t value into integral and fractional parts.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param x             Value to split into integral and fractional parts
/// @param integral_part Pointer of fixed_t to receive integral part
///
/// @return Fractional part of x
template <typename IntType, std::size_t Q>
constexpr fixed_t<IntType, Q> fixed_modf(fixed_t<IntType, Q> x,
                                         fixed_t<IntType, Q>* integral_part) {
  return ((*integral_part = impl::get_integral_part(x)),
          impl::get_fractional_part(x));
}

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_MATH_MODF_PRIV_H_
