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

struct ModTestParam {
  float dividend;
  float divisor;
};

template <typename T>
bool is_same_sign(T a, T b) {
  return (((a > T(0)) && (b > T(0)))
          || ((a < T(0)) && (b < T(0)))
          || ((a == T(0)) && (b == T(0))));
}

}  // namespace

class ModTest
  : public ::testing::TestWithParam<ModTestParam> {
};

TEST_P(ModTest, Validation) {
  const fixed_t fixed_dividend = fixed_t(GetParam().dividend);
  const fixed_t fixed_divisor  = fixed_t(GetParam().divisor);
  const fixed_t mod_result     = fixedpointnumber::fixed_mod(fixed_dividend,
                                                             fixed_divisor);
  std::cout << fixed_dividend / fixed_divisor << ',' << mod_result << std::endl;

  EXPECT_TRUE((mod_result == fixed_t(0))
              || is_same_sign(fixed_dividend, mod_result));
  EXPECT_LT(fixedpointnumber::fixed_abs(mod_result),
            fixedpointnumber::fixed_abs(fixed_divisor));
}

constexpr ModTestParam kModTestParams[] = {{3.0f, 1.5f},
                                           {3.0f, 0.125f},
                                           {3.0f, 2.0f},
                                           {3.0f, 4.0f},
                                           {3.0f, -1.0f},
                                           {-2.0f, 2.0f},
                                           {-2.0f, 1.5f},
                                           {-2.0f, -1.0f},
                                           {-2.0f, -1.5f},
                                           {-2.0f, -3.0f}};
INSTANTIATE_TEST_SUITE_P(Instance0,
                         ModTest,
                         ::testing::ValuesIn(kModTestParams));
