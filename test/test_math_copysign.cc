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

using fixed_t  = fixedpointnumber::fixed_t<int16_t, 7>;

}  // namespace

class CopysignTest
    : public ::testing::TestWithParam<std::tuple<fixed_t, fixed_t>> {
};

TEST_P(CopysignTest, Validate) {
  const auto param0 = std::get<0>(GetParam());
  const auto param1 = std::get<1>(GetParam());
  const auto result = fixedpointnumber::fixed_copysign(param0, param1);

  EXPECT_EQ(fixedpointnumber::fixed_abs(param0),
            fixedpointnumber::fixed_abs(result));
  EXPECT_TRUE((fixedpointnumber::fixed_signbit(param1)
               == fixedpointnumber::fixed_signbit(result))
              || (param0 == fixed_t(0)));
}

INSTANTIATE_TEST_SUITE_P(
    Instance0,
    CopysignTest,
    ::testing::Combine(::testing::Range(fixed_t("-2.0"),
                                        fixed_t("2.125"),
                                        fixed_t("0.25")),
                       ::testing::Range(fixed_t("-2.0"),
                                        fixed_t("2.125"),
                                        fixed_t("0.25"))));
