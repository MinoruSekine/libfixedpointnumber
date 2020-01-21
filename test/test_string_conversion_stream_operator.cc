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
#include <sstream>
#include <string>

#include <gtest/gtest.h>

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
                                                {2000.5f   , "2000.5"},
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

TEST_P(StringConversionStreamOperatorTest, StreamOperator) {
  const auto param = GetParam();
  const fixed_t fixed_num(param.num);
  std::stringstream ss;

  ss << fixed_num;
  EXPECT_STREQ(param.str, ss.str().c_str());
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         StringConversionStreamOperatorTest,
                         ::testing::ValuesIn(kStringTestValues));
