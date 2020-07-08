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

using fixed_t = fixedpointnumber::fixed_t<int16_t, 4>;

namespace {

struct MulResult {
  template <typename T>
  constexpr MulResult(T a, T b, T c)
      : lhs(a), rhs(b), mul_result(c) {
  }

  fixed_t lhs;
  fixed_t rhs;
  fixed_t mul_result;
};

const MulResult kMulResults[] = {
  // Combination of negative/positive values.
  { 0.5f,  0.5f,  0.25f},
  {-0.5f,  0.5f, -0.25f},
  { 0.5f, -0.5f, -0.25f},
  {-0.5f, -0.5f,  0.25f},

  // Results are just one.
  { 0.5f, 2.0f, 1.0f},
  { 2.0f, 0.5f, 1.0f},

  // Results are just zero.
  {  0.00f,  0.25f, 0.00f},
  {  0.25f,  0.00f, 0.00f},
  {  0.00f, -0.25f, 0.00f},
  { -0.25f,  0.00f, 0.00f},

  // Both integers multiply.
  {  10,  100,  1000},
  { -10,  100, -1000},
  { -10, -100,  1000},
};

}  // namespace

class ArithmeticMulOperatorTest
  : public ::testing::TestWithParam<MulResult> {
};

TEST_P(ArithmeticMulOperatorTest, NormalOperator) {
  const auto param = GetParam();
  EXPECT_EQ(param.mul_result, param.lhs * param.rhs);
}

TEST_P(ArithmeticMulOperatorTest, CommutativeLaw) {
  const auto param = GetParam();
  EXPECT_EQ(param.mul_result, param.rhs * param.lhs);
}

TEST_P(ArithmeticMulOperatorTest, CompoundOperator) {
  const auto param = GetParam();
  auto lhs = param.lhs;
  lhs *= param.rhs;
  EXPECT_EQ(param.mul_result, lhs);
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         ArithmeticMulOperatorTest,
                         ::testing::ValuesIn(kMulResults));
