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
  EXPECT_EQ(0, cpowi_result);
}

class CpowiOneToThePowerOfNegativeTest
    : public ::testing::TestWithParam<int32_t> {
};

TEST_P(CpowiOneToThePowerOfNegativeTest, MustBeOne) {
  EXPECT_EQ(1, constexprmath::cpowi(1, GetParam()));
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         CpowiOneToThePowerOfNegativeTest,
                         ::testing::Range(-3, -1));

class CpowiMoreThanOneToThePowerOfNegativeTest
    : public ::testing::TestWithParam<std::tuple<int32_t, int32_t>> {
};

TEST_P(CpowiMoreThanOneToThePowerOfNegativeTest, MustBeZero) {
  EXPECT_EQ(0, constexprmath::cpowi(std::get<0>(GetParam()),
                                    std::get<1>(GetParam())));
}

INSTANTIATE_TEST_SUITE_P(Positive,
                         CpowiMoreThanOneToThePowerOfNegativeTest,
                         ::testing::Combine(::testing::Range(2, 3),
                                            ::testing::Range(-3, -1)));

INSTANTIATE_TEST_SUITE_P(Negative,
                         CpowiMoreThanOneToThePowerOfNegativeTest,
                         ::testing::Combine(::testing::Range(-3, -1),
                                            ::testing::Range(-3, -1)));
