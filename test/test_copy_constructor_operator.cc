//
// Copyright 2019 Minoru Sekine
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

namespace {

using fixed_t = fixedpointnumber::fixed_t<int16_t, 10>;

}  // namespace

class CopyConstructorOperatorIntTest
  : public ::testing::TestWithParam<int8_t> {
};

TEST_P(CopyConstructorOperatorIntTest, CopyConstructionWithBrace) {
  const int8_t test_value = GetParam();
  const fixed_t f0(test_value);
  const fixed_t f1(f0);

  EXPECT_EQ(f0, f1);
}

TEST_P(CopyConstructorOperatorIntTest, CopyConstructionWithEqual) {
  const int8_t test_value = GetParam();
  const fixed_t f0(test_value);
  const fixed_t f1 = f0;

  EXPECT_EQ(f0, f1);
}

TEST_P(CopyConstructorOperatorIntTest, CopyOperator) {
  const int8_t test_value = GetParam();
  const fixed_t f0(test_value);
  fixed_t f1(0);

  f1 = f0;
  EXPECT_EQ(f0, f1);
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         CopyConstructorOperatorIntTest,
                         ::testing::Values(int8_t(0), int8_t(1), int8_t(2)));
