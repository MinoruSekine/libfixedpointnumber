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

using fixed_t = fixedpointnumber::fixed_t<int16_t, 4>;

class FloatFixedConversionTest
  : public ::testing::TestWithParam<float> {
};

TEST_P(FloatFixedConversionTest, SimpleConversion) {
  const float test_value = GetParam();
  const fixed_t f(test_value);

  EXPECT_FLOAT_EQ(test_value, static_cast<float>(f));
}

TEST_P(FloatFixedConversionTest, FloatFixedIntConversion) {
  const float test_value = GetParam();
  const fixed_t f(test_value);
  const int32_t i(static_cast<int32_t>(test_value));

  EXPECT_EQ(i, static_cast<int32_t>(f));
}

INSTANTIATE_TEST_SUITE_P(NearZeroRange,
                         FloatFixedConversionTest,
                         ::testing::Values(0.0f, 0.0625f));

INSTANTIATE_TEST_SUITE_P(MiddleRange,
                         FloatFixedConversionTest,
                         ::testing::Range(1023.0f, 1025.0f, 0.0625f));

constexpr float k11BitsMax = 2047;
INSTANTIATE_TEST_SUITE_P(NearMaxRange,
                         FloatFixedConversionTest,
                         ::testing::Values(k11BitsMax - 1.0f, k11BitsMax));

INSTANTIATE_TEST_SUITE_P(NegativeRange,
                         FloatFixedConversionTest,
                         ::testing::Values(-1.0f, -2.0f, -2047.0f, -2048.0f));
