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

#ifndef INCLUDE_FIXEDPOINTNUMBER_MATH_COMPARISON_PRIV_H_
#define INCLUDE_FIXEDPOINTNUMBER_MATH_COMPARISON_PRIV_H_

#include "fixedpointnumber.h"

#ifndef FIXEDPOINTNUMBER_MATH_INTERNAL
#error Do not include this file directly, fixedpointnumber_math.h instead.
#endif

namespace fixedpointnumber {

/// Test 1st parameter greater than 2nd or not.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param x Value to test which is greater than y
/// @param y Value to test which is less than or equal to x
///
/// @retval true  When x > y
/// @retval false When x <= y
///
/// @relates fixed_t
template <typename IntType, std::size_t Q>
constexpr bool fixed_isgreater(fixed_t<IntType, Q> x,
                               fixed_t<IntType, Q> y) {
  return (x > y);
}

/// Test 1st parameter greater than or equal to 2nd.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param x Value to test which is greater than or equal to y
/// @param y Value to test which is less than x
///
/// @retval true  When x >= y
/// @retval false When x < y
///
/// @relates fixed_t
template <typename IntType, std::size_t Q>
constexpr bool fixed_isgreaterequal(fixed_t<IntType, Q> x,
                                    fixed_t<IntType, Q> y) {
  return (x >= y);
}

/// Test 1st parameter less than 2nd or not.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param x Value to test which is less than y
/// @param y Value to test which is greater than or equal to x
///
/// @retval true  When x < y
/// @retval false When x >= y
///
/// @relates fixed_t
template <typename IntType, std::size_t Q>
constexpr bool fixed_isless(fixed_t<IntType, Q> x,
                            fixed_t<IntType, Q> y) {
  return (x < y);
}

/// Test 1st parameter less than or equal to 2nd.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param x Value to test which is less than or equal to y
/// @param y Value to test which is greater than x
///
/// @retval true  When x <= y
/// @retval false When x > y
///
/// @relates fixed_t
template <typename IntType, std::size_t Q>
constexpr bool fixed_islessequal(fixed_t<IntType, Q> x,
                                 fixed_t<IntType, Q> y) {
  return (x <= y);
}

/// Test 1st parameter less or greater than 2nd.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param x Value to test which is less or greater than y
/// @param y Value to test which is less or greater than x
///
/// @retval true  When x < y or x > y
/// @retval false When not x < y and not x > y
///
/// @relates fixed_t
template <typename IntType, std::size_t Q>
constexpr bool fixed_islessgreater(fixed_t<IntType, Q> x,
                                   fixed_t<IntType, Q> y) {
  return ((x < y) || (x > y));
}

/// Test 1st and 2nd parameter are unordered or not.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @retval true  1st and 2nd parameter are unordered
/// @retval false 1st and 2nd parameter are not unordered
///
/// @note Currently this function always returns false
///
/// @relates fixed_t
template <typename IntType, std::size_t Q>
constexpr bool fixed_isunordered(fixed_t<IntType, Q>,
                                 fixed_t<IntType, Q>) {
  return false;
}

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_MATH_COMPARISON_PRIV_H_
