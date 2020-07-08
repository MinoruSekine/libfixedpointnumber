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

#include "gtest_compat.h"

#include "fixedpointnumber.h"

namespace {

using fixed_t = fixedpointnumber::fixed_t<int16_t, 6>;

struct IncDecResult {
  template <typename T>
  constexpr IncDecResult(T a, T b)
      : n(a), inc_result(b) {
  }

  fixed_t n;
  fixed_t inc_result;
};

const IncDecResult kIncDecResults[] = {
  {-11, -10},
  { -1,   0},
  {  0,   1},
  {  4,   5},
  {-16.125f, -15.125f},
  {-14.000f, -13.000f},
  { -1.000f,   0.000f},
  { -0.250f,   0.750f},
  {  0.000f,   1.000f},
  {  9.750f,  10.750f},
};

}  // namespace

class ArithmeticIncDecTest
  : public ::testing::TestWithParam<IncDecResult> {
};

TEST_P(ArithmeticIncDecTest, Increment) {
  const auto param = GetParam();
  fixed_t n = param.n;
  EXPECT_EQ(param.inc_result, ++n);
}

TEST_P(ArithmeticIncDecTest, Decrement) {
  const auto param = GetParam();
  fixed_t n = param.inc_result;
  EXPECT_EQ(param.n, --n);
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         ArithmeticIncDecTest,
                         ::testing::ValuesIn(kIncDecResults));
