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

#include <cstddef>

#include "gtest_compat.h"

#include "constexpr_math.h"

TEST(ConstexprMathTest, cpowi) {
  EXPECT_EQ(1,    constexprmath::cpowi(10, 0));
  EXPECT_EQ(1000, constexprmath::cpowi(10, 3));
}

TEST(ConstexprMathTest, cpowi_constexpr) {
  constexpr auto cpowi_result = constexprmath::cpowi(2, 10);
  EXPECT_EQ(1024, cpowi_result);
}

TEST(ConstexprMathTest, cpowi_negative_nth_power_limitation) {
  constexpr auto cpowi_result = constexprmath::cpowi(5, -8);
  EXPECT_EQ(1, cpowi_result);
}
