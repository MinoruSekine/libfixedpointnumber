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

class IsLessGreater2ndParamTest
    : public ::testing::TestWithParam<std::tuple<fixed_t, fixed_t>> {
};

TEST_P(IsLessGreater2ndParamTest, Validate) {
  const auto x = std::get<0>(GetParam());
  const auto y = std::get<1>(GetParam());
  EXPECT_TRUE(fixedpointnumber::fixed_isless(x, y));
}

INSTANTIATE_TEST_SUITE_P(Instance20,
                         IsLessGreater2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t("2.0")),
                                            ::testing::Range(fixed_t("2.25"),
                                                             fixed_t("3.0"),
                                                             fixed_t("0.25"))));

INSTANTIATE_TEST_SUITE_P(Instance10,
                         IsLessGreater2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t("1.0")),
                                            ::testing::Range(fixed_t("1.25"),
                                                             fixed_t("2.0"),
                                                             fixed_t("0.25"))));

INSTANTIATE_TEST_SUITE_P(Instance05,
                         IsLessGreater2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t("0.5")),
                                            ::testing::Range(fixed_t("0.75"),
                                                             fixed_t("1.5"),
                                                             fixed_t("0.25"))));

INSTANTIATE_TEST_SUITE_P(Instance0,
                         IsLessGreater2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t(0)),
                                            ::testing::Range(fixed_t("0.25"),
                                                             fixed_t("1.0"),
                                                             fixed_t("0.25"))));

INSTANTIATE_TEST_SUITE_P(InstanceMinus05,
                         IsLessGreater2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t("-0.5")),
                                            ::testing::Range(fixed_t("-0.25"),
                                                             fixed_t("0.5"),
                                                             fixed_t("0.25"))));

class IsLessLessEqual2ndParamTest
    : public ::testing::TestWithParam<std::tuple<fixed_t, fixed_t>> {
};

TEST_P(IsLessLessEqual2ndParamTest, Validate) {
  const auto x = std::get<0>(GetParam());
  const auto y = std::get<1>(GetParam());
  EXPECT_FALSE(fixedpointnumber::fixed_isless(x, y));
}

INSTANTIATE_TEST_SUITE_P(Instance20,
                         IsLessLessEqual2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t("2.0")),
                                            ::testing::Range(fixed_t("-1.0"),
                                                             fixed_t("2.1"),
                                                             fixed_t("0.25"))));

INSTANTIATE_TEST_SUITE_P(Instance10,
                         IsLessLessEqual2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t("1.0")),
                                            ::testing::Range(fixed_t("-1.0"),
                                                             fixed_t("1.1"),
                                                             fixed_t("0.25"))));

INSTANTIATE_TEST_SUITE_P(Instance05,
                         IsLessLessEqual2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t("0.5")),
                                            ::testing::Range(fixed_t("-1.0"),
                                                             fixed_t("0.6"),
                                                             fixed_t("0.25"))));

INSTANTIATE_TEST_SUITE_P(Instance0,
                         IsLessLessEqual2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t(0)),
                                            ::testing::Range(fixed_t("-1.0"),
                                                             fixed_t("0.1"),
                                                             fixed_t("0.25"))));

INSTANTIATE_TEST_SUITE_P(InstanceMinus05,
                         IsLessLessEqual2ndParamTest,
                         ::testing::Combine(::testing::Values(fixed_t("-0.5")),
                                            ::testing::Range(fixed_t("-1.5"),
                                                             fixed_t("-0.4"),
                                                             fixed_t("0.25"))));
