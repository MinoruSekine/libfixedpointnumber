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
#include <iostream>
#include <tuple>

#include "gtest_compat.h"

#include "fixedpointnumber.h"
#include "fixedpointnumber_math.h"

namespace {

using fixed_t = fixedpointnumber::fixed_t<int16_t, 7>;

constexpr const fixed_t kTestStartValue(-2.0);
constexpr const fixed_t kTestEndValue(2.5);
constexpr const fixed_t kTestStepValue(0.5);

}  // namespace

class FmaTest
    : public ::testing::TestWithParam<std::tuple<fixed_t, fixed_t, fixed_t>> {
};

TEST_P(FmaTest, Validate) {
  const auto x_as_fixed = std::get<0>(GetParam());
  const auto y_as_fixed = std::get<1>(GetParam());
  const auto z_as_fixed = std::get<2>(GetParam());
  const double x_as_double = static_cast<double>(x_as_fixed);
  const double y_as_double = static_cast<double>(y_as_fixed);
  const double z_as_double = static_cast<double>(z_as_fixed);

  EXPECT_DOUBLE_EQ(std::fma(x_as_double, y_as_double, z_as_double),
                   static_cast<double>(
                       fixedpointnumber::fixed_fma(x_as_fixed,
                                                   y_as_fixed,
                                                   z_as_fixed)));
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         FmaTest,
                         ::testing::Combine(::testing::Range(kTestStartValue,
                                                             kTestEndValue,
                                                             kTestStepValue),
                                            ::testing::Range(kTestStartValue,
                                                             kTestEndValue,
                                                             kTestStepValue),
                                            ::testing::Range(kTestStartValue,
                                                             kTestEndValue,
                                                             kTestStepValue)));
