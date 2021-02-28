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

#ifndef INCLUDE_FIXEDPOINTNUMBER_MATH_MOD_PRIV_H_
#define INCLUDE_FIXEDPOINTNUMBER_MATH_MOD_PRIV_H_

#include "fixedpointnumber.h"
#include "fixedpointnumber_math.h"

#ifndef FIXEDPOINTNUMBER_MATH_INTERNAL
#error Do not include this file directly, fixedpointnumber_math.h instead.
#endif

namespace fixedpointnumber {

namespace impl {

template <typename IntType, std::size_t Q>
constexpr auto fixed_abs_floor(fixed_t<IntType, Q> src)
    -> typename std::enable_if<std::is_signed<IntType>::value,
                               fixed_t<IntType, Q>>::type {
  return ((src >= fixed_t<IntType, Q>(0))
          ? fixed_floor(src)
          : fixed_ceil(src));
}

template <typename IntType, std::size_t Q>
constexpr fixed_t<IntType, Q> fixed_div_round(fixed_t<IntType, Q> dividend,
                               fixed_t<IntType, Q> divisor) {
  return fixed_abs_floor(dividend / divisor);
}

}  // namespace impl

/// Compute the modulo value for fixed_t
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param dividend Dividend value to get modulo
/// @param divisor  Divisor value to get modulo
///
/// @return The modulo value
///
/// @relates fixed_t
template <typename IntType, std::size_t Q>
constexpr fixed_t<IntType, Q> fixed_mod(fixed_t<IntType, Q> dividend,
                                        fixed_t<IntType, Q> divisor) {
  return (dividend - (divisor * impl::fixed_div_round(dividend, divisor)));
}

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_MATH_MOD_PRIV_H_
