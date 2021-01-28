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

#ifndef TEST_COMPARISON_HELPER_H_
#define TEST_COMPARISON_HELPER_H_

#include "fixedpointnumber.h"
#include "fixedpointnumber_limits.h"

template <typename FloatType, typename IntType, IntType Q>
bool IsFloatFixedEq(FloatType float_value,
               fixedpointnumber::fixed_t<IntType, Q> fixed_value) {
  using fixed_t = fixedpointnumber::fixed_t<IntType, Q>;
  return (std::abs(float_value - static_cast<FloatType>(fixed_value))
          <= static_cast<FloatType>(
              fixedpointnumber::numeric_limits<fixed_t>::min()));
}

#endif  // TEST_COMPARISON_HELPER_H_
