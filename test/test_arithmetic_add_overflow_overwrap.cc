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
#include "fixedpointnumber_limits.h"

template <typename T>
class AddOverflowIsOverwrappingTest
    : public ::testing::Test {
 protected:
  using fixed_t = T;
  using fixed_limits = fixedpointnumber::numeric_limits<fixed_t>;
};

using MyTypes = ::testing::Types<fixedpointnumber::fixed_t<uint8_t, 4>,
                                 fixedpointnumber::fixed_t<uint16_t, 5>,
                                 fixedpointnumber::fixed_t<uint32_t, 20>,
                                 fixedpointnumber::fixed_t<int8_t, 6>,
                                 fixedpointnumber::fixed_t<int16_t, 10>,
                                 fixedpointnumber::fixed_t<int32_t, 2>>;

// This strange 3rd argument omission is quick hack
// for warning with Google Test Framework.
// See https://github.com/google/googletest/issues/2271#issuecomment-665742471 .
// cppcheck-suppress syntaxError
TYPED_TEST_SUITE(AddOverflowIsOverwrappingTest, MyTypes, );  // NOLINT

TYPED_TEST(AddOverflowIsOverwrappingTest, Validate) {
  const auto max_num = TestFixture::fixed_limits::max();
  const auto min_num = TestFixture::fixed_limits::min();
  EXPECT_LT(max_num + min_num, max_num);
}
