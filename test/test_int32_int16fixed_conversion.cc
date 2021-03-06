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

using fixed_t = fixedpointnumber::fixed_t<int16_t, 5>;

constexpr int32_t kMiddleRangeValue = 0x001f;
constexpr int32_t k10BitsMax = 0x03ff;

}  // namespace

class Int32Int16FixedConversionTest
    : public ::testing::TestWithParam<int32_t> {
};

TEST_P(Int32Int16FixedConversionTest, SimpleConversion) {
  const auto test_value = GetParam();
  const fixed_t f(test_value);

  EXPECT_EQ(test_value, static_cast<int32_t>(f));
}

INSTANTIATE_TEST_SUITE_P(NearZeroRange,
                         Int32Int16FixedConversionTest,
                         ::testing::Values(0, 1, 2));

INSTANTIATE_TEST_SUITE_P(MiddleRange,
                         Int32Int16FixedConversionTest,
                         ::testing::Values(kMiddleRangeValue,
                                           kMiddleRangeValue + 1));

INSTANTIATE_TEST_SUITE_P(NearMaxRange,
                         Int32Int16FixedConversionTest,
                         ::testing::Values(k10BitsMax - 1, k10BitsMax));

INSTANTIATE_TEST_SUITE_P(NegativeRange,
                         Int32Int16FixedConversionTest,
                         ::testing::Values(-1, -2, -1023, -1024));
