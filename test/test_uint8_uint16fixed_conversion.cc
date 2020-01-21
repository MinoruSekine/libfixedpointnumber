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

using ufixed_t = fixedpointnumber::fixed_t<uint16_t, 10>;

constexpr uint8_t kMiddleRangeValue      = 0x07;
constexpr uint8_t kMiddleRangeValuePlus1 = 0x08;
constexpr uint8_t k6BitsMax       = 0x3f;
constexpr uint8_t k6BitsMaxMinus1 = 0x3e;

}  // namespace

class UInt8UInt16FixedConversionTest
  : public ::testing::TestWithParam<uint8_t> {
};

TEST_P(UInt8UInt16FixedConversionTest, SimpleConversion) {
  const auto test_value = GetParam();
  const ufixed_t f(test_value);

  EXPECT_EQ(test_value, static_cast<uint8_t>(f));
}

INSTANTIATE_TEST_SUITE_P(NearZeroRange,
                         UInt8UInt16FixedConversionTest,
                         ::testing::Values(uint8_t(0), uint8_t(1), uint8_t(2)));

INSTANTIATE_TEST_SUITE_P(MiddleRange,
                         UInt8UInt16FixedConversionTest,
                         ::testing::Values(kMiddleRangeValue,
                                           kMiddleRangeValuePlus1));

INSTANTIATE_TEST_SUITE_P(NearMaxRange,
                         UInt8UInt16FixedConversionTest,
                         ::testing::Values(k6BitsMaxMinus1, k6BitsMax));
