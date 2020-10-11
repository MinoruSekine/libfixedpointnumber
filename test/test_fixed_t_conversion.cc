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

using fixed_14_1_t = fixedpointnumber::fixed_t<int16_t, 1>;
using fixed_12_3_t = fixedpointnumber::fixed_t<int16_t, 3>;

}  // namespace

class FixedTConversionTest
    : public ::testing::TestWithParam<float> {
};

TEST_P(FixedTConversionTest, ExpandDecimalPartConversion) {
  const float test_value = GetParam();
  const fixed_14_1_t f_14_1(test_value);
  const fixed_12_3_t f_12_3(f_14_1);

  EXPECT_FLOAT_EQ(test_value, static_cast<float>(f_12_3));
}

TEST_P(FixedTConversionTest, ShrinkDecimalPartConversion) {
  const float test_value = GetParam();
  const fixed_12_3_t f_12_3(test_value);
  const fixed_14_1_t f_14_1(f_12_3);

  EXPECT_FLOAT_EQ(test_value, static_cast<float>(f_14_1));
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         FixedTConversionTest,
                         ::testing::Range(-2.0f, 2.5f, 0.5f));
