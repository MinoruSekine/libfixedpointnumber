//
// Copyright 2019,2020 Minoru Sekine
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
#include <sstream>
#include <string>

#include "gtest_compat.h"

#include "fixedpointnumber.h"

namespace {

using fixed_t = fixedpointnumber::fixed_t<int16_t, 4>;

struct FloatAndString {
  float num;
  const char* str;
};


constexpr FloatAndString kStringTestValues[] = {
                                                { -40.125f ,  "-40.125"},
                                                {   0.0f   ,    "0"},
                                                {  90.0f   ,   "90.0"},
                                                { 800.0625f,  "800.0625"},
                                                {1000.5f   , "1000.5"},
};

}  // namespace

class StringConversionStreamOperatorTest
  : public ::testing::TestWithParam<FloatAndString> {
};

TEST_P(StringConversionStreamOperatorTest, StringConversion) {
  const auto param = GetParam();
  const fixed_t fixed_num(param.num);

  EXPECT_STREQ(param.str, fixed_num.ToString().c_str());
}

TEST_P(StringConversionStreamOperatorTest, StreamOutputOperator) {
  const auto param = GetParam();
  const fixed_t fixed_num(param.num);
  std::stringstream ss;

  ss << fixed_num;
  EXPECT_STREQ(param.str, ss.str().c_str());
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         StringConversionStreamOperatorTest,
                         ::testing::ValuesIn(kStringTestValues));

TEST(StringConversionTest, DecimalPartIsWide) {
  constexpr float kNum = 1.5f;
  constexpr char kStr[] = "1.5";
  const fixedpointnumber::fixed_t<int32_t, 19> fixed(kNum);

  EXPECT_STREQ(kStr, fixed.ToString().c_str());
}

template <typename T>
class WideFixedToStringConversionTest : public ::testing::Test {
};

using TestTargetTypes =
        ::testing::Types<fixedpointnumber::fixed_t<int32_t, 20>,
                         fixedpointnumber::fixed_t<int32_t, 21>>;
// See following pages to accepet pragma.
// - TYPED_TEST_SUITE: warning about variadic macro
//   - https://github.com/google/googletest/issues/2069
// - INSTANTIATE_TEST_CASE_P generates warnings with clang++ -Wpedantic
//   - https://github.com/google/googletest/issues/1419
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#endif  // __clang__
TYPED_TEST_SUITE(WideFixedToStringConversionTest, TestTargetTypes);
#ifdef __clang_
#pragma clang diagnostic pop
#endif  // __clang__

TYPED_TEST(WideFixedToStringConversionTest, ConversionTest) {
  for (const auto& i : kStringTestValues) {
    const TypeParam fixed(i.num);
    EXPECT_STREQ(i.str, fixed.ToString().c_str());
  }
}
