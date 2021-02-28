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

#ifndef INCLUDE_FIXEDPOINTNUMBER_MATH_REMQUO_PRIV_H_
#define INCLUDE_FIXEDPOINTNUMBER_MATH_REMQUO_PRIV_H_

#include "fixedpointnumber.h"
#include "fixedpointnumber_math.h"

#ifndef FIXEDPOINTNUMBER_MATH_INTERNAL
#error Do not include this file directly, fixedpointnumber_math.h instead.
#endif

namespace fixedpointnumber {

/// Compute remainder and quotient.
///
/// @tparam IntType Internal int type for type fixed_t template param
/// @tparam Q       Q for type fixed_t template param
///
/// @param[in]  num   Numerator
/// @param[in]  denom Denominator
/// @param[out] quo   Quotient
///
/// @return The quotient remainder of num / denom
///
/// @relates fixed_t
template <typename IntType, std::size_t Q>
constexpr fixed_t<IntType, Q> fixed_remquo(fixed_t<IntType, Q> num,
                                           fixed_t<IntType, Q> denom,
                                           fixed_t<IntType, Q>* quo) {
  return *quo = fixed_round(num / denom), fixed_remainder(num, denom);
}

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_MATH_REMQUO_PRIV_H_
