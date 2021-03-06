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
#include <tuple>

#include "gtest_compat.h"

#include "fixedpointnumber.h"
#include "fixedpointnumber_math.h"

namespace {

using fixed_t = fixedpointnumber::fixed_t<int16_t, 7>;

}  // namespace

class RemainderTest
    : public ::testing::TestWithParam<std::tuple<fixed_t, fixed_t>> {
 public:
  RemainderTest()
      : num_(0), denom_(0), quotient_(0), remainder_(0) {
  }

 protected:
  void SetUp() override {
    num_ = std::get<0>(GetParam());
    denom_ = std::get<1>(GetParam());
    remainder_ = fixedpointnumber::fixed_remainder(num_, denom_);
    quotient_ = (num_ - remainder_) / denom_;
  }

  fixed_t num_;
  fixed_t denom_;
  fixed_t quotient_;
  fixed_t remainder_;
};

TEST_P(RemainderTest, RemainderLessThanDenominator) {
  EXPECT_LT(fixedpointnumber::fixed_abs(remainder_),
            fixedpointnumber::fixed_abs(denom_));
}

TEST_P(RemainderTest, ValidateQuotientAndRemainder) {
  EXPECT_FLOAT_EQ(static_cast<float>(num_),
                  static_cast<float>(denom_ * quotient_ + remainder_));
}

// 2 instances to split range of denominator, for solution of zero division.
INSTANTIATE_TEST_SUITE_P(PositiveDenom,
                         RemainderTest,
                         ::testing::Combine(::testing::Range(fixed_t("-1.5"),
                                                             fixed_t("1.75"),
                                                             fixed_t("0.5")),
                                            ::testing::Range(fixed_t("0.5"),
                                                             fixed_t("1.75"),
                                                             fixed_t("0.5"))));

INSTANTIATE_TEST_SUITE_P(NegativeDenom,
                         RemainderTest,
                         ::testing::Combine(::testing::Range(fixed_t("-1.5"),
                                                             fixed_t("1.75"),
                                                             fixed_t("0.5")),
                                            ::testing::Range(fixed_t("-1.5"),
                                                             fixed_t(0),
                                                             fixed_t("0.5"))));
