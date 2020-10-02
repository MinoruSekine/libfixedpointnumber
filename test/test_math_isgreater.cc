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

#include <cmath>
#include <cstdint>
#include <tuple>

#include "gtest_compat.h"

#include "fixedpointnumber.h"
#include "fixedpointnumber_math.h"

namespace {

using fixed_t = fixedpointnumber::fixed_t<int16_t, 7>;

}  // namespace

class IsGreaterLess2ndParamTest
    : public ::testing::TestWithParam<std::tuple<fixed_t, fixed_t>> {
};

TEST_P(IsGreaterLess2ndParamTest, Validate) {
  const auto x = std::get<0>(GetParam());
  const auto y = std::get<1>(GetParam());
  EXPECT_TRUE(fixedpointnumber::fixed_isgreater(x, y));
}

INSTANTIATE_TEST_SUITE_P(Instance20,
                         IsGreaterLess2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t("2.0")),
                                            ::testing::Range(fixed_t("-1.0"),
                                                             fixed_t("2.0"),
                                                             fixed_t("0.25"))));

INSTANTIATE_TEST_SUITE_P(Instance10,
                         IsGreaterLess2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t("1.0")),
                                            ::testing::Range(fixed_t("-1.0"),
                                                             fixed_t("1.0"),
                                                             fixed_t("0.25"))));

INSTANTIATE_TEST_SUITE_P(Instance05,
                         IsGreaterLess2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t("0.5")),
                                            ::testing::Range(fixed_t("-1.0"),
                                                             fixed_t("0.5"),
                                                             fixed_t("0.25"))));

INSTANTIATE_TEST_SUITE_P(Instance0,
                         IsGreaterLess2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t(0)),
                                            ::testing::Range(fixed_t("-1.0"),
                                                             fixed_t(0),
                                                             fixed_t("0.25"))));

INSTANTIATE_TEST_SUITE_P(InstanceMinus05,
                         IsGreaterLess2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t("-0.5")),
                                            ::testing::Range(fixed_t("-1.0"),
                                                             fixed_t("-0.5"),
                                                             fixed_t("0.25"))));

class IsGreaterGreaterEqual2ndParamTest
    : public ::testing::TestWithParam<std::tuple<fixed_t, fixed_t>> {
};

TEST_P(IsGreaterGreaterEqual2ndParamTest, Validate) {
  const auto x = std::get<0>(GetParam());
  const auto y = std::get<1>(GetParam());
  EXPECT_FALSE(fixedpointnumber::fixed_isgreater(x, y));
}

INSTANTIATE_TEST_SUITE_P(Instance20,
                         IsGreaterGreaterEqual2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t("2.0")),
                                            ::testing::Range(fixed_t("2.0"),
                                                             fixed_t("3.1"),
                                                             fixed_t("0.25"))));

INSTANTIATE_TEST_SUITE_P(Instance10,
                         IsGreaterGreaterEqual2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t("1.0")),
                                            ::testing::Range(fixed_t("1.0"),
                                                             fixed_t("2.1"),
                                                             fixed_t("0.25"))));

INSTANTIATE_TEST_SUITE_P(Instance05,
                         IsGreaterGreaterEqual2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t("0.5")),
                                            ::testing::Range(fixed_t("0.5"),
                                                             fixed_t("1.1"),
                                                             fixed_t("0.25"))));

INSTANTIATE_TEST_SUITE_P(Instance0,
                         IsGreaterGreaterEqual2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t(0)),
                                            ::testing::Range(fixed_t(0),
                                                             fixed_t("1.1"),
                                                             fixed_t("0.25"))));

INSTANTIATE_TEST_SUITE_P(InstanceMinus05,
                         IsGreaterGreaterEqual2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t("-0.5")),
                                            ::testing::Range(fixed_t("-0.5"),
                                                             fixed_t("1.1"),
                                                             fixed_t("0.25"))));
