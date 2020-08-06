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

#include <cmath>
#include <cstdint>

#include "gtest_compat.h"

#include "fixedpointnumber.h"
#include "fixedpointnumber_math.h"

namespace {

using fixed_t = fixedpointnumber::fixed_t<int16_t, 7>;

}  // namespace

class FloorTest
  : public ::testing::TestWithParam<float> {
};

TEST_P(FloorTest, Validation) {
  const fixed_t fixed_param(GetParam());
  const fixed_t floored_num = fixedpointnumber::fixed_floor(fixed_param);

  EXPECT_LE(floored_num, fixed_param);
  EXPECT_LT(fixed_param, floored_num + fixed_t(1));
  EXPECT_FLOAT_EQ(std::floor(GetParam()), static_cast<float>(floored_num));
}

INSTANTIATE_TEST_SUITE_P(InstancePositiveNearZero,
                         FloorTest,
                         ::testing::Range(0.0f, 2.0f, 0.25f));

INSTANTIATE_TEST_SUITE_P(InstanceNegativeNearZero,
                         FloorTest,
                         ::testing::Range(-2.0f, 0.0f, 0.25f));

class CeilTest
  : public ::testing::TestWithParam<float> {
};

TEST_P(CeilTest, Validation) {
  const fixed_t fixed_param(GetParam());
  const fixed_t ceiled_num = fixedpointnumber::fixed_ceil(fixed_param);

  EXPECT_GE(ceiled_num, fixed_param);
  EXPECT_GT(fixed_param + fixed_t(1), ceiled_num);
  EXPECT_FLOAT_EQ(std::ceil(GetParam()), static_cast<float>(ceiled_num));
}

INSTANTIATE_TEST_SUITE_P(InstancePositiveNearZero,
                         CeilTest,
                         ::testing::Range(0.0f, 2.0f, 0.25f));

INSTANTIATE_TEST_SUITE_P(InstanceNegativeNearZero,
                         CeilTest,
                         ::testing::Range(-2.0f, 0.0f, 0.25f));
