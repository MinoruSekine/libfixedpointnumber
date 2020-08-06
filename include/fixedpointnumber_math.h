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

#ifndef INCLUDE_FIXEDPOINTNUMBER_MATH_H_
#define INCLUDE_FIXEDPOINTNUMBER_MATH_H_

#include "fixedpointnumber.h"

namespace fixedpointnumber {

namespace impl {

template <typename IntType, std::size_t Q>
constexpr fixed_t<IntType, Q> fixed_floor_positive(fixed_t<IntType, Q> src) {
  return fixed_t<IntType, Q>(src.fixed_point_ & src.kIntegralPartMask, true);
}

template <typename IntType, std::size_t Q>
constexpr fixed_t<IntType, Q> fixed_ceil_positive(fixed_t<IntType, Q> src) {
  return (((src.fixed_point_ & src.kDecimalPartMask) != 0)
          ? (fixed_floor_positive(src) + fixed_t<IntType, Q>(1))
          : src);
}

template <typename IntType, std::size_t Q>
constexpr fixed_t<IntType, Q> fixed_round_positive(fixed_t<IntType, Q> src) {
  return fixed_floor_positive(src + fixed_t<IntType, Q>(0.5f));
}

template <typename IntType, std::size_t Q>
constexpr fixed_t<IntType, Q> fixed_floor_negative(fixed_t<IntType, Q> src) {
  return -fixed_ceil_positive(-src);
}

template <typename IntType, std::size_t Q>
constexpr fixed_t<IntType, Q> fixed_ceil_negative(fixed_t<IntType, Q> src) {
  return -fixed_floor_positive(-src);
}

template <typename IntType, std::size_t Q>
constexpr fixed_t<IntType, Q> fixed_round_negative(fixed_t<IntType, Q> src) {
  return fixed_ceil_negative(src - fixed_t<IntType, Q>(0.5f));
}

}  // namespace impl

/// Compute the smallest integral value which is larger than the parameter.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param src value to compute smallest integral value
///            which is larger than this value
///
/// @return The smallest integral value which is larger than the src
///
/// @note This specialization is for signed IntType
template <typename IntType, std::size_t Q>
constexpr auto fixed_floor(fixed_t<IntType, Q> src)
    -> typename std::enable_if<std::is_signed<IntType>::value,
                               fixed_t<IntType, Q>>::type {
  return ((src >= fixed_t<IntType, Q>(0))
          ? impl::fixed_floor_positive(src)
          : impl::fixed_floor_negative(src));
}

/// Compute the smallest integral value which is larger than the parameter.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param src value to compute smallest integral value
///            which is larger than this value
///
/// @return The smallest integral value which is larger than the src
///
/// @note This specialization is for unsigned IntType,
///       it is necessary to avoid to use unary operator `-` to unsigned type
template <typename IntType, std::size_t Q>
constexpr auto fixed_floor(fixed_t<IntType, Q> src)
    -> typename std::enable_if<std::is_unsigned<IntType>::value,
                               fixed_t<IntType, Q>>::type {
  return impl::fixed_floor_positive(src);
}

/// Compute the largest integral value which is smaller than the parameter.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param src value to compute largest integral value
///            which is smaller than this value
///
/// @return The largest integral value which is smaller than the src
///
/// @note This specialization is for signed IntType
template <typename IntType, std::size_t Q>
constexpr auto fixed_ceil(fixed_t<IntType, Q> src)
    -> typename std::enable_if<std::is_signed<IntType>::value,
                               fixed_t<IntType, Q>>::type {
  return ((src >= fixed_t<IntType, Q>(0))
          ? impl::fixed_ceil_positive(src)
          : impl::fixed_ceil_negative(src));
}

/// Compute the largest integral value which is smaller than the parameter.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param src value to compute largest integral value
///            which is smaller than this value
///
/// @return The largest integral value which is smaller than the src
///
/// @note This specialization is for unsigned IntType,
///       it is necessary to avoid to use unary operator `-` to unsigned type
template <typename IntType, std::size_t Q>
constexpr auto fixed_ceil(fixed_t<IntType, Q> src)
    -> typename std::enable_if<std::is_unsigned<IntType>::value,
                               fixed_t<IntType, Q>>::type {
  return impl::fixed_ceil_positive(src);
}

/// Compute the round-ed integral value.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param src value to compute round-ed integral value
///
/// @return The round-ed integral value
///
/// @note This specialization is for signed IntType,
///       it is necessary to avoid to use unary operator `-` to unsigned type
template <typename IntType, std::size_t Q>
constexpr auto fixed_round(fixed_t<IntType, Q> src)
    -> typename std::enable_if<std::is_signed<IntType>::value,
                               fixed_t<IntType, Q>>::type {
  return ((src >= fixed_t<IntType, Q>(0))
          ? impl::fixed_round_positive(src)
          : impl::fixed_round_negative(src));
}

/// Compute the round-ed integral value.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param src value to compute round-ed integral value
///
/// @return The round-ed integral value
///
/// @note This specialization is for unsigned IntType,
///       it is necessary to avoid to use unary operator `-` to unsigned type
template <typename IntType, std::size_t Q>
constexpr auto fixed_round(fixed_t<IntType, Q> src)
    -> typename std::enable_if<std::is_unsigned<IntType>::value,
                               fixed_t<IntType, Q>>::type {
  return impl::fixed_round_positive(src);
}

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_MATH_H_
