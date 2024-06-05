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

struct FloatAndStr {
  // cppcheck-suppress unusedStructMember
  float f;
  // cppcheck-suppress unusedStructMember
  const char* str;
};

constexpr FloatAndStr kTestValues[] = {
  {4.5f, "4.5"},
  {4.5f, "4.500"},
  {-1.25f, "-1.25"},
  {0.0f, "0"},
  {0.0f, "0.00"},
};

}  // namespace

class FromStringTest
    : public ::testing::TestWithParam<FloatAndStr> {
};

TEST_P(FromStringTest, ConstructFromString) {
  const auto param = GetParam();
  EXPECT_EQ(fixed_t(param.f), fixed_t(param.str));
}

TEST_P(FromStringTest, FromString) {
  const auto param = GetParam();
  fixed_t from_string;
  EXPECT_EQ(fixed_t(param.f), from_string.FromString(param.str));
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         FromStringTest,
                         ::testing::ValuesIn(kTestValues));
