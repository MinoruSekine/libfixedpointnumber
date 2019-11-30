//
// Copyright 2019 Minoru Sekine
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

using fixed_t = fixedpointnumber::fixed_t<int16_t, 6>;

struct AddSubResult {
  template <typename T>
  constexpr AddSubResult(T a, T b, T c)
      : n1(a), n2(b), add_result(c) {
  }

  fixed_t n1;
  fixed_t n2;
  fixed_t add_result;
};

class ArithmeticAddSubTest
  : public ::testing::TestWithParam<AddSubResult> {
};

TEST_P(ArithmeticAddSubTest, Add) {
  const auto param = GetParam();
  EXPECT_EQ(param.add_result, param.n1 + param.n2);
}

TEST_P(ArithmeticAddSubTest, Sub) {
  const auto param = GetParam();
  EXPECT_EQ(param.n1, param.add_result - param.n2);
  EXPECT_EQ(param.n2, param.add_result - param.n1);
}

TEST_P(ArithmeticAddSubTest, AddCommulativeLaw) {
  const auto param = GetParam();
  EXPECT_EQ(param.add_result, param.n2 + param.n1);
}

TEST_P(ArithmeticAddSubTest, CompoundAdd) {
  const auto param = GetParam();
  fixed_t compound_added_result = param.n1;
  compound_added_result += param.n2;
  EXPECT_EQ(param.add_result, compound_added_result);
}

TEST_P(ArithmeticAddSubTest, CompoundSub) {
  const auto param = GetParam();
  {
    fixed_t compound_sub_result1 = param.add_result;
    compound_sub_result1 -= param.n1;
    EXPECT_EQ(param.n2, compound_sub_result1);
  }

  {
    fixed_t compound_sub_result2 = param.add_result;
    compound_sub_result2 -= param.n2;
    EXPECT_EQ(param.n1, compound_sub_result2);
  }
}

const AddSubResult kAddSubResults[] = {
  // Negative value, Positive value, Positive Value
  {   -1,    2,    1},
  {-5.5f, 6.0f, 0.5f},
  // Negative value, Positice value, Zero
  {    -1,     1,    0},
  {-9.25f, 9.25f, 0.0f},
  // Zero, Positive value, Positive value (no changes)
  {   0,    1,    1},
  {0.0f, 2.5f, 2.5f},
  // Positive value, Positive value, Positive value
  {      2,       3,    5},
  {6.0625f, 0.9375f, 7.0f},
};

INSTANTIATE_TEST_SUITE_P(Instance0,
                         ArithmeticAddSubTest,
                         ::testing::ValuesIn(kAddSubResults));
