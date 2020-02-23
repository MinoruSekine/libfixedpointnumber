
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

#include <gtest/gtest.h>

#include "fixedpointnumber.h"
#include "fixedpointnumber_limits.h"

namespace {

using fixed_t = fixedpointnumber::fixed_t<int16_t, 7>;
using limits = fixedpointnumber::numeric_limits<fixed_t>;

}  // namespace

TEST(NumericLimitsTest, ConstantBoolsOrEnums) {
  EXPECT_TRUE(limits::is_signed);
  EXPECT_FALSE(limits::is_integer);
  EXPECT_TRUE(limits::is_exact);
  EXPECT_FALSE(limits::has_infinity);
  EXPECT_FALSE(limits::has_quiet_NaN);
  EXPECT_FALSE(limits::has_signaling_NaN);
  EXPECT_EQ(std::denorm_absent, limits::has_denorm);
  EXPECT_FALSE(limits::has_denorm_loss);
  EXPECT_EQ(std::round_toward_zero, limits::round_style);
  EXPECT_FALSE(limits::is_iec559);
  EXPECT_TRUE(limits::is_bounded);
  EXPECT_FALSE(limits::is_modulo);
  EXPECT_TRUE(limits::traps);
  EXPECT_FALSE(limits::tinyness_before);
}

TEST(NumericLimitsTest, ConstantIntegers) {
  EXPECT_EQ(15, limits::digits);
  EXPECT_EQ(4, limits::digits10);
  EXPECT_EQ(0, limits::max_digits10);
  EXPECT_EQ(2, limits::radix);
  EXPECT_EQ(0, limits::min_exponent);
  EXPECT_EQ(0, limits::min_exponent10);
  EXPECT_EQ(0, limits::max_exponent);
  EXPECT_EQ(0, limits::max_exponent10);
}
