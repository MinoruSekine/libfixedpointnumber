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

#include "gtest_compat.h"

#include "fixedpointnumber.h"
#include "fixedpointnumber_math.h"

namespace {

using fixed_t = fixedpointnumber::fixed_t<int16_t, 7>;

}  // namespace

class AbsPositiveTest
  : public ::testing::TestWithParam<fixed_t> {
};

TEST_P(AbsPositiveTest, Validation) {
  EXPECT_EQ(GetParam(), fixedpointnumber::fixed_abs(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         AbsPositiveTest,
                         ::testing::Range(fixed_t(0),
                                          fixed_t(2),
                                          fixed_t(0.25f)));

class AbsNegativeTest
  : public ::testing::TestWithParam<fixed_t> {
};

TEST_P(AbsNegativeTest, Validation) {
  EXPECT_EQ(GetParam(), -fixedpointnumber::fixed_abs(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         AbsNegativeTest,
                         ::testing::Range(fixed_t(-3),
                                          fixed_t(0),
                                          fixed_t(0.25f)));
