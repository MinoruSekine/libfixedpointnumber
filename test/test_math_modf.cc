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

class ModfTest
    : public ::testing::TestWithParam<double> {
};

TEST_P(ModfTest, Validate) {
  const double target_value_as_double = GetParam();
  double integral_part_as_double = 0.0;
  const double fractional_part_as_double =
      std::modf(target_value_as_double, &integral_part_as_double);

  const fixed_t target_value_as_fixed(target_value_as_double);
  fixed_t integral_part_as_fixed(0);
  const fixed_t fractional_part_as_fixed =
      fixedpointnumber::fixed_modf(target_value_as_fixed,
                                   &integral_part_as_fixed);

  EXPECT_DOUBLE_EQ(integral_part_as_double,
                   static_cast<double>(integral_part_as_fixed));
  EXPECT_DOUBLE_EQ(fractional_part_as_double,
                   static_cast<double>(fractional_part_as_fixed));
}

TEST_P(ModfTest, FractionalPartOfIntegralPartByModfIsZero) {
  const fixed_t target_value_as_fixed(GetParam());
  fixed_t integral_part_as_fixed(0);
  fixedpointnumber::fixed_modf(target_value_as_fixed, &integral_part_as_fixed);
  EXPECT_EQ(fixed_t(0),
            fixedpointnumber::fixed_modf(integral_part_as_fixed,
                                         &integral_part_as_fixed));
}

INSTANTIATE_TEST_SUITE_P(NegativeParam,
                         ModfTest,
                         ::testing::Range(-2.0, 0.0, 0.25));

INSTANTIATE_TEST_SUITE_P(PositiveParam,
                         ModfTest,
                         ::testing::Range(0.0, 3.0, 0.25));
