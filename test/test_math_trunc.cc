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

class TruncTest
  : public ::testing::TestWithParam<fixed_t> {
};

TEST_P(TruncTest, Validate) {
  const auto trunc_result = fixedpointnumber::fixed_trunc(GetParam());
  EXPECT_TRUE((fixedpointnumber::fixed_signbit(GetParam())
               == fixedpointnumber::fixed_signbit(trunc_result))
              || (trunc_result == fixed_t(0)));
  EXPECT_LE(fixedpointnumber::fixed_abs(trunc_result),
            fixedpointnumber::fixed_abs(GetParam()));
  EXPECT_LT(fixedpointnumber::fixed_abs(GetParam() - trunc_result),
            fixed_t(1));
  EXPECT_EQ(trunc_result, fixedpointnumber::fixed_trunc(trunc_result));
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         TruncTest,
                         ::testing::Range(fixed_t("-2.0"),
                                          fixed_t("2.125"),
                                          fixed_t("0.25")));
