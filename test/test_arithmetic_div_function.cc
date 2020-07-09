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

#include "gtest_compat.h"

#include "fixedpointnumber.h"

namespace {

struct DivResult {
  float lhs;
  float rhs;
  float div_result;
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

class ArithmeticDivFunctionTest
  : public ::testing::TestWithParam<DivResult> {
};

TEST_P(ArithmeticDivFunctionTest, Div) {
  const auto param = GetParam();
  using lhs_fixed_t = fixedpointnumber::fixed_t<int16_t, 5>;
  const auto lhs = static_cast<lhs_fixed_t>(param.lhs);
  using rhs_fixed_t = fixedpointnumber::fixed_t<int16_t, 3>;
  const auto rhs = static_cast<rhs_fixed_t>(param.rhs);
  const auto result = fixed_div(lhs, rhs);
  const auto expected_result = static_cast<decltype(result)>(param.div_result);
  EXPECT_EQ(expected_result, result);
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         ArithmeticDivFunctionTest,
                         ::testing::ValuesIn(kDivResults));
