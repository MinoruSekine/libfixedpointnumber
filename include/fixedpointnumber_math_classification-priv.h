//
// Copyright 2021 Minoru Sekine
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

#ifndef INCLUDE_FIXEDPOINTNUMBER_MATH_CLASSIFICATION_PRIV_H_
#define INCLUDE_FIXEDPOINTNUMBER_MATH_CLASSIFICATION_PRIV_H_

#include "fixedpointnumber.h"

#include "fixedpointnumber_unused-priv.h"

#ifndef FIXEDPOINTNUMBER_MATH_INTERNAL
#error Do not include this file directly, ixedpointnumber_math.h instead.
#endif

namespace fixedpointnumber {

/// Return given parameter value is finite or not.
///
/// This functions is compatible to std::isfinite().
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param src value to check finite or not
///
/// @retval true  src is finite
/// @retval false src is not finite
///
/// @note Always returns false
///
/// @relates fixed_t
template <typename IntType, std::size_t Q>
constexpr bool fixed_isfinite(fixed_t<IntType, Q> src) {
  return FIXEDPOINTNUMBER_UNUSED(src), false;
}

/// Return given parameter value is infinity or not.
///
/// This functions is compatible to std::isinf().
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param src value to check infinity or not
///
/// @retval true  src is infinity
/// @retval false src is not infinity
///
/// @note Always returns false
///
/// @relates fixed_t
template <typename IntType, std::size_t Q>
constexpr bool fixed_isinf(fixed_t<IntType, Q> src) {
  return FIXEDPOINTNUMBER_UNUSED(src), false;
}

/// Return given parameter value is NaN or not.
///
/// This functions is compatible to std::isnan().
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param src value to check NaN or not
///
/// @retval true  src is NaN
/// @retval false src is not NaN
///
/// @note Always returns false
///
/// @relates fixed_t
template <typename IntType, std::size_t Q>
constexpr bool fixed_isnan(fixed_t<IntType, Q> src) {
  return FIXEDPOINTNUMBER_UNUSED(src), false;
}

/// Return given parameter value is normalized or not.
///
/// This functions is compatible to std::isnormal().
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param src value to check normalized or not
///
/// @retval true  src is normalized
/// @retval false src is not normalized
///
/// @note Always returns true
///
/// @relates fixed_t
template <typename IntType, std::size_t Q>
constexpr bool fixed_isnormal(fixed_t<IntType, Q> src) {
  return (src != fixed_t<IntType, Q>(0));
}

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_MATH_CLASSIFICATION_PRIV_H_
