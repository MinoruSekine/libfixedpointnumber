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

#include <cstdint>
#include <limits>

#include <gtest/gtest.h>

#include "fixedpointnumber.h"

namespace {

using fixed_t = fixedpointnumber::fixed_t<int32_t, 20>;

}  // namespace

class NumericLimitsTest
  : public ::testing::Test {
};

TEST_F(NumericLimitsTest, MemberConstants) {
  EXPECT_TRUE(std::numeric_limits<fixed_t>::is_specialized);
  EXPECT_TRUE(std::numeric_limits<fixed_t>::is_signed);
  EXPECT_FALSE(std::numeric_limits<fixed_t>::is_integer);
  EXPECT_TRUE(std::numeric_limits<fixed_t>::is_exact);
  EXPECT_FALSE(std::numeric_limits<fixed_t>::has_infinity);
  EXPECT_FALSE(std::numeric_limits<fixed_t>::has_quiet_NaN);
  EXPECT_FALSE(std::numeric_limits<fixed_t>::has_signaling_NaN);
  EXPECT_EQ(std::denorm_absent, std::numeric_limits<fixed_t>::has_denorm);
  EXPECT_FALSE(std::numeric_limits<fixed_t>::has_denorm_loss);
  EXPECT_EQ(std::round_toward_zero, std::numeric_limits<fixed_t>::round_style);
  EXPECT_FALSE(std::numeric_limits<fixed_t>::is_iec559);
  EXPECT_TRUE(std::numeric_limits<fixed_t>::is_bounded);
  EXPECT_FALSE(std::numeric_limits<fixed_t>::is_modulo);
  EXPECT_EQ(11, std::numeric_limits<fixed_t>::digits);
  EXPECT_EQ(4, std::numeric_limits<fixed_t>::digits10);
  EXPECT_EQ(0, std::numeric_limits<fixed_t>::max_digits10);
  EXPECT_EQ(2, std::numeric_limits<fixed_t>::radix);
  EXPECT_EQ(0, std::numeric_limits<fixed_t>::min_exponent);
  EXPECT_EQ(0, std::numeric_limits<fixed_t>::min_exponent10);
  EXPECT_EQ(0, std::numeric_limits<fixed_t>::max_exponent);
  EXPECT_EQ(0, std::numeric_limits<fixed_t>::max_exponent10);
  EXPECT_TRUE(std::numeric_limits<fixed_t>::traps);
  EXPECT_FALSE(std::numeric_limits<fixed_t>::tinyness_before);
}

