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

#include <cstddef>

#include "gtest_compat.h"

#include "constexpr_string.h"

namespace {

constexpr const char kTestFloatString[] = "10.0625";
constexpr const char kTestIntString[]   = "100625";
constexpr const char kTestNullString[]  = "";

}  // namespace

TEST(ConstexprStringTest, cstrlen) {
  constexpr std::size_t test_string_len =
      constexprstr::cstrlen(kTestFloatString);
  EXPECT_EQ(7U, test_string_len);
}

TEST(ConstexprStringTest, cstrlen_zero_len_string) {
  constexpr std::size_t test_string_len =
      constexprstr::cstrlen(kTestNullString);
  EXPECT_EQ(0U, test_string_len);
}

TEST(ConstexprStringTest, cstrchr) {
  constexpr const char* kDotPos = constexprstr::cstrchr(kTestFloatString, '.');
  EXPECT_STREQ(".0625", kDotPos);
}

TEST(ConstexprStringTest, cstrchr_cant_find) {
  constexpr const char* kDotPos = constexprstr::cstrchr(kTestIntString, '.');
  EXPECT_EQ(nullptr, kDotPos);
}
