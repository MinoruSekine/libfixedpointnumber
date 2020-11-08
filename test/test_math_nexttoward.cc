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

class NextTowardPositiveTest
    : public ::testing::TestWithParam<std::tuple<fixed_t, long double>> {
};

TEST_P(NextTowardPositiveTest, Validate) {
  EXPECT_GT(std::get<0>(GetParam()),
            fixedpointnumber::fixed_nexttoward(std::get<0>(GetParam()),
                                               std::get<1>(GetParam())));
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         NextTowardPositiveTest,
                         ::testing::Combine(::testing::Range(fixed_t(-1),
                                                             fixed_t("1.5"),
                                                             fixed_t("0.5")),
                                            ::testing::Range(0.5L,
                                                             1.5L,
                                                             0.5L)));

class NextTowardNegativeTest
    : public ::testing::TestWithParam<std::tuple<fixed_t, long double>> {
};

TEST_P(NextTowardNegativeTest, Validate) {
  EXPECT_LT(std::get<0>(GetParam()),
            fixedpointnumber::fixed_nexttoward(std::get<0>(GetParam()),
                                               std::get<1>(GetParam())));
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         NextTowardNegativeTest,
                         ::testing::Combine(::testing::Range(fixed_t(-1),
                                                             fixed_t("1.5"),
                                                             fixed_t("0.5")),
                                            ::testing::Range(-2.0L,
                                                             0.0L,
                                                             0.5L)));
