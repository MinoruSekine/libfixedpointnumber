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

#include "gtest_compat.h"

#include "fixedpointnumber.h"

namespace {

using fixed_t = fixedpointnumber::fixed_t<int16_t, 10>;

}  // namespace

template <typename T>
class UnaryOperatorMinusTest : public ::testing::Test {
};

using TestTargetTypes =
    ::testing::Types<fixedpointnumber::fixed_t<int16_t, 10>,
                     fixedpointnumber::fixed_t<int32_t, 16>>;
// See following pages to accepet pragma.
// - TYPED_TEST_SUITE: warning about variadic macro
//   - https://github.com/google/googletest/issues/2069
// - INSTANTIATE_TEST_CASE_P generates warnings with clang++ -Wpedantic
//   - https://github.com/google/googletest/issues/1419
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#endif  // __clang__
TYPED_TEST_SUITE(UnaryOperatorMinusTest, TestTargetTypes);
#ifdef __clang_
#pragma clang diagnostic pop
#endif  // __clang__

TYPED_TEST(UnaryOperatorMinusTest, DoesWork) {
  EXPECT_EQ(TypeParam(-1), -TypeParam(1));
  EXPECT_EQ(TypeParam(2), -TypeParam(-2));
}
