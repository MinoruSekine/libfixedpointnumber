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
#include <tuple>

#include "gtest_compat.h"

#include "fixedpointnumber.h"
#include "fixedpointnumber_math.h"

namespace {

using fixed_t = fixedpointnumber::fixed_t<int16_t, 7>;

}  // namespace

class LerpTest
    : public ::testing::TestWithParam<std::tuple<fixed_t, fixed_t, fixed_t>> {
};

TEST_P(LerpTest, Validate) {
  const auto a = std::get<0>(GetParam());
  const auto b = a + std::get<1>(GetParam());
  const auto t = std::get<2>(GetParam());

  const auto lerp = fixedpointnumber::fixed_lerp(a, b, t);

  EXPECT_GE(lerp, a);
  EXPECT_EQ(t, (lerp - a) / (b - a));
}

INSTANTIATE_TEST_SUITE_P(
    Instance0,
    LerpTest,
    ::testing::Combine(::testing::Range(fixed_t("-1.5"),
                                        fixed_t("1.1"),
                                        fixed_t("0.5")),
                       ::testing::Range(fixed_t("1.0"),
                                        fixed_t("1.6"),
                                        fixed_t("0.5")),
                       ::testing::Range(fixed_t("0.0"),
                                        fixed_t("1.625"),
                                        fixed_t("0.25"))));

class LerpZeroOneTest
    : public ::testing::TestWithParam<std::tuple<fixed_t, fixed_t>> {
};

TEST_P(LerpZeroOneTest, Zero) {
  const auto a = std::get<0>(GetParam());
  const auto b = a + std::get<1>(GetParam());

  EXPECT_EQ(a, fixedpointnumber::fixed_lerp(a, b, fixed_t(0)));
}

TEST_P(LerpZeroOneTest, One) {
  const auto a = std::get<0>(GetParam());
  const auto b = a + std::get<1>(GetParam());

  EXPECT_EQ(b, fixedpointnumber::fixed_lerp(a, b, fixed_t(1)));
}

INSTANTIATE_TEST_SUITE_P(
    Instance0,
    LerpZeroOneTest,
    ::testing::Combine(::testing::Range(fixed_t("-2.0"),
                                        fixed_t("1.1"),
                                        fixed_t("0.5")),
                       ::testing::Range(fixed_t("1.0"),
                                        fixed_t("2.1"),
                                        fixed_t("0.5"))));
