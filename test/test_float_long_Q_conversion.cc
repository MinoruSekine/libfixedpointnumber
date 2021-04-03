//
// Copyright 2021 Minoru Sekine
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

using fixed_t = fixedpointnumber::fixed_t<uint16_t, 16>;

}  // namespace

class FloatLongQFixedConversionTest
    : public ::testing::TestWithParam<float> {
};

TEST_P(FloatLongQFixedConversionTest, SimpleConversion) {
  const float test_value = GetParam();
  const fixed_t f(test_value);

  EXPECT_FLOAT_EQ(test_value, static_cast<float>(f));
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         FloatLongQFixedConversionTest,
                         ::testing::Range(0.0f, 1.0f, 0.5f));
