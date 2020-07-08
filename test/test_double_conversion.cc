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

using fixed_t = fixedpointnumber::fixed_t<int16_t, 4>;

constexpr double k11BitsMax = 2047;

}  // namespace

class DoubleFixedConversionTest
  : public ::testing::TestWithParam<double> {
};

TEST_P(DoubleFixedConversionTest, SimpleConversion) {
  const double test_value = GetParam();
  const fixed_t f(test_value);

  EXPECT_DOUBLE_EQ(test_value, static_cast<double>(f));
}

TEST_P(DoubleFixedConversionTest, DoubleFixedIntConversion) {
  const double test_value = GetParam();
  const fixed_t f(test_value);
  const int32_t i(static_cast<int32_t>(test_value));

  EXPECT_EQ(i, static_cast<int32_t>(f));
}

INSTANTIATE_TEST_SUITE_P(NearZeroRange,
                         DoubleFixedConversionTest,
                         ::testing::Values(0.0, 0.0625));

INSTANTIATE_TEST_SUITE_P(MiddleRange,
                         DoubleFixedConversionTest,
                         ::testing::Range(1023.0, 1025.0, 0.0625));

INSTANTIATE_TEST_SUITE_P(NearMaxRange,
                         DoubleFixedConversionTest,
                         ::testing::Values(k11BitsMax - 1.0, k11BitsMax));

INSTANTIATE_TEST_SUITE_P(NegativeRange,
                         DoubleFixedConversionTest,
                         ::testing::Values(-1.0, -2.0, -2047.0, -2048.0));
