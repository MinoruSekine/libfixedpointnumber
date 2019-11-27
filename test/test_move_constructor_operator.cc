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

#include <gtest/gtest.h>

#include "fixedpointnumber.h"

using fixed_t = fixedpointnumber::fixed_t<int16_t, 10>;

class MoveConstructorOperatorIntTest
  : public ::testing::TestWithParam<int8_t> {
 protected:
  fixed_t GetTestFixedValue() const {
    return fixed_t(GetParam());
  }
};

TEST_P(MoveConstructorOperatorIntTest, MoveConstructionWithBrace) {
  const int8_t test_value = GetParam();
  const fixed_t f0(GetTestFixedValue());

  EXPECT_EQ(test_value, static_cast<int8_t>(f0));
}

TEST_P(MoveConstructorOperatorIntTest, MoveConstructionWithEqual) {
  const int8_t test_value = GetParam();
  const fixed_t f0 = GetTestFixedValue();

  EXPECT_EQ(test_value, static_cast<int8_t>(f0));
}

TEST_P(MoveConstructorOperatorIntTest, MoveOperator) {
  const int8_t test_value = GetParam();
  fixed_t f0;

  f0 = GetTestFixedValue();
  EXPECT_EQ(test_value, static_cast<int8_t>(f0));
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         MoveConstructorOperatorIntTest,
                         ::testing::Values(int8_t(0), int8_t(1), int8_t(2)));
