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

#include "gtest_compat.h"

#include "fixedpointnumber.h"
#include "fixedpointnumber_math.h"

namespace {

using fixed_t  = fixedpointnumber::fixed_t<int16_t, 7>;
using ufixed_t = fixedpointnumber::fixed_t<uint16_t, 7>;

}  // namespace

class SignbitPositiveTest
  : public ::testing::TestWithParam<fixed_t> {
};

TEST_P(SignbitPositiveTest, Validation) {
  EXPECT_FALSE(fixedpointnumber::fixed_signbit(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         SignbitPositiveTest,
                         ::testing::Range(fixed_t(0.0f),
                                          fixed_t(2.125f),
                                          fixed_t(0.125f)));

class SignbitNegativeTest
  : public ::testing::TestWithParam<fixed_t> {
};

TEST_P(SignbitNegativeTest, Validation) {
  EXPECT_TRUE(fixedpointnumber::fixed_signbit(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         SignbitNegativeTest,
                         ::testing::Range(fixed_t(-2.0f),
                                          fixed_t(0.0f),
                                          fixed_t(0.125f)));

class SignbitUnsignedFixedTest
  : public ::testing::TestWithParam<ufixed_t> {
};

TEST_P(SignbitUnsignedFixedTest, Validation) {
  EXPECT_FALSE(fixedpointnumber::fixed_signbit(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         SignbitUnsignedFixedTest,
                         ::testing::Range(ufixed_t(0.0f),
                                          ufixed_t(2.125f),
                                          ufixed_t(0.125f)));
