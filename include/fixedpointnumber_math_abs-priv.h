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

#ifndef INCLUDE_FIXEDPOINTNUMBER_MATH_ABS_PRIV_H_
#define INCLUDE_FIXEDPOINTNUMBER_MATH_ABS_PRIV_H_

#include "fixedpointnumber.h"

#ifndef FIXEDPOINTNUMBER_MATH_INTERNAL
#error Do not include this file directly, ixedpointnumber_math.h instead.
#endif

namespace fixedpointnumber {

/// Compute absolute value.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param src value to compute absolute value
///
/// @return The absolute value of src
///
/// @note This specialization is for signed IntType
template <typename IntType, std::size_t Q>
constexpr auto fixed_abs(fixed_t<IntType, Q> src)
    -> typename std::enable_if<std::is_signed<IntType>::value,
                               fixed_t<IntType, Q>>::type {
  return ((src < fixed_t<IntType, Q>(0)) ? -src : src);
}

/// Compute absolute value.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param src value to compute absolute value
///
/// @return The absolute value of src
///
/// @note This specialization is for unsigned IntType,
///       it is necessary to avoid to use unary operator `-` to unsigned type
template <typename IntType, std::size_t Q>
constexpr auto fixed_abs(fixed_t<IntType, Q> src)
    -> typename std::enable_if<std::is_unsigned<IntType>::value,
                               fixed_t<IntType, Q>>::type {
  return src;
}

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_MATH_ABS_PRIV_H_
