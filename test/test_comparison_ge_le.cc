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

namespace {

using fixed_t = fixedpointnumber::fixed_t<int16_t, 7>;

}  // namespace

class ComparisonGeLeTest
  : public ::testing::TestWithParam<float> {
};

TEST_P(ComparisonGeLeTest, GeLe) {
  const fixed_t param(GetParam());
  const fixed_t three_point_zero(3.0f);
  EXPECT_GE(three_point_zero, param);
  EXPECT_LE(param, three_point_zero);
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         ComparisonGeLeTest,
                         ::testing::Range(3.0f, -2.0f, -0.0625f));
