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

using lhs_fixed_t    = fixedpointnumber::fixed_t<int16_t, 2>;
using rhs_fixed_t    = fixedpointnumber::fixed_t<int16_t, 3>;
using result_fixed_t = fixedpointnumber::fixed_t<int32_t, 5>;

struct MulResult {
  template <typename lhs_t, typename rhs_t, typename result_t>
  constexpr MulResult(lhs_t a, rhs_t b, result_t c)
      : lhs(a), rhs(b), mul_result(c) {
  }

  lhs_fixed_t lhs;
  rhs_fixed_t rhs;
  result_fixed_t mul_result;
};

const MulResult kMulResults[] = {
  // Combination of negative/positive values.
  { 0.5f,  0.5f,  0.25f},
  {-0.5f,  0.5f, -0.25f},
  { 0.5f, -0.5f, -0.25f},
  {-0.5f, -0.5f,  0.25f},

  // Results are just one.
  { 0.5f,    2, 1},
  {    2, 0.5f, 1},

  // Results are just zero.
  {      0,  0.25f, 0},
  {  0.25f,      0, 0},
  {      0, -0.25f, 0},
  { -0.25f,      0, 0},

  // Both integers multiply.
  {  10,  100,  1000},
  { -10,  100, -1000},
  { -10, -100,  1000},
};

}  // namespace

class ArithmeticMulFunctionTest
  : public ::testing::TestWithParam<MulResult> {
};

TEST_P(ArithmeticMulFunctionTest, MulWithKeepingPrecision) {
  const auto param = GetParam();
  EXPECT_EQ(param.mul_result, fixed_mul(param.lhs, param.rhs));
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         ArithmeticMulFunctionTest,
                         ::testing::ValuesIn(kMulResults));
