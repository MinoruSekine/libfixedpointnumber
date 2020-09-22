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

#ifndef INCLUDE_CONSTEXPR_MATH_H_
#define INCLUDE_CONSTEXPR_MATH_H_

#include <type_traits>

namespace constexprmath {

/// @addtogroup constexprmath constexprmath
///
/// constexprmath provides some math functions as constexpr functions.
///
/// @{

/// Calculate x^n.
///
/// This function is only supporting both integral x and n.
///
/// @tparam T Type of arguments and results.
///           It must be primitive integral types.
///
/// @param[in] x Calculate n-th power of x (x^n)
/// @param[in] n Calculate n-th power of x (x^n)
///
/// @return x^n
template <typename T>
constexpr auto cpowi(T x, T n)
    -> typename std::enable_if<(std::is_integral<T>::value
                                && std::is_signed<T>::value),
                               T>::type {
  return ((n > 0)
          ? (((n % 2) == 0)
             ? (cpowi(x, n / 2) * cpowi(x, n / 2))
             : (cpowi(x, n / 2) * cpowi(x, n / 2) * x))
          : ((n < 0)
             ? (1 / cpowi(x, -n))
             : 1));
}

template <typename T>
constexpr auto cpowi(T x, T n)
    -> typename std::enable_if<(std::is_integral<T>::value
                                && std::is_unsigned<T>::value),
                               T>::type {
  return ((n > 0)
          ? (((n % 2) == 0)
             ? (cpowi(x, n / 2) * cpowi(x, n / 2))
             : (cpowi(x, n / 2) * cpowi(x, n / 2) * x))
          : 1);
}

/// @}

}  // namespace constexprmath

#endif  // INCLUDE_CONSTEXPR_MATH_H_
