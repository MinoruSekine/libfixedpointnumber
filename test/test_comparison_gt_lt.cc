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

using fixed_t = fixedpointnumber::fixed_t<int16_t, 5>;

class ComparisonGtLtTest
  : public ::testing::TestWithParam<double> {
};

TEST_P(ComparisonGtLtTest, GtGeLtLeNe) {
  const fixed_t param(GetParam());
  fixed_t incremented_param(param);
  ++incremented_param;
  EXPECT_GT(incremented_param, param);
  EXPECT_GE(incremented_param, param);
  EXPECT_LT(param, incremented_param);
  EXPECT_LE(param, incremented_param);
  EXPECT_NE(incremented_param, param);
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         ComparisonGtLtTest,
                         ::testing::Range(-2.125, 3.0, 0.5));
