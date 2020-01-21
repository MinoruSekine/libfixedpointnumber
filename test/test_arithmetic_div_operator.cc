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

#include <cstdint>

#include <gtest/gtest.h>

#include "fixedpointnumber.h"

namespace {

using fixed_t = fixedpointnumber::fixed_t<int16_t, 5>;

struct DivResult {
  template <typename T>
  constexpr DivResult(T a, T b, T c)
      : lhs(a), rhs(b), div_result(c) {
  }

  fixed_t lhs;
  fixed_t rhs;
  fixed_t div_result;
};

const DivResult kDivResults[] = {
  // Combination of negative/positive values.
  { 0.5f,  2.00f,  0.25f},
  {-0.5f,  2.00f, -0.25f},
  { 0.5f, -0.25f, -2.00f},
  {-0.5f, -0.25f,  2.00f},

  // Results are just one.
  { 0.500f, 0.500f, 1.0f},
  { 2.125f, 2.125f, 1.0f},
};

}  // namespace

class ArithmeticDivOperatorTest
  : public ::testing::TestWithParam<DivResult> {
};

TEST_P(ArithmeticDivOperatorTest, NormalOperator) {
  const auto param = GetParam();
  EXPECT_EQ(param.div_result, param.lhs / param.rhs);
}

TEST_P(ArithmeticDivOperatorTest, CompoundOperator) {
  const auto param = GetParam();
  auto lhs = param.lhs;
  lhs /= param.rhs;
  EXPECT_EQ(param.div_result, lhs);
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         ArithmeticDivOperatorTest,
                         ::testing::ValuesIn(kDivResults));
