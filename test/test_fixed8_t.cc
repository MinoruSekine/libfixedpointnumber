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

#include "comparison_helper.h"

namespace {

using fixed8_t = fixedpointnumber::fixed_t<int8_t, 5>;

}  // namespace

class Fixed8tTest
    : public ::testing::TestWithParam<std::tuple<float, float>> {
 public:
  Fixed8tTest()
      : lhs_(0.0f), rhs_(0.0f) {
  }

  void SetUp() override {
    lhs_ = std::get<0>(GetParam());
    rhs_ = std::get<1>(GetParam());

    return;
  }

 protected:
  float lhs_;
  float rhs_;
};

TEST_P(Fixed8tTest, Add) {
  EXPECT_PRED2((IsFloatFixedEq<float, int8_t, 5>),
               lhs_ + rhs_,
               fixed8_t(lhs_) + fixed8_t(rhs_));
}

TEST_P(Fixed8tTest, Sub) {
  EXPECT_PRED2((IsFloatFixedEq<float, int8_t, 5>),
               lhs_ - rhs_,
               fixed8_t(lhs_) - fixed8_t(rhs_));
}

TEST_P(Fixed8tTest, Mul) {
  EXPECT_PRED2((IsFloatFixedEq<float, int8_t, 5>),
               lhs_ * rhs_,
               fixed8_t(lhs_) * fixed8_t(rhs_));
}

TEST_P(Fixed8tTest, Div) {
  EXPECT_PRED2((IsFloatFixedEq<float, int8_t, 5>),
               lhs_ / rhs_,
               fixed8_t(lhs_) / fixed8_t(rhs_));
}

INSTANTIATE_TEST_SUITE_P(
    PositiveLhsPositiveRhs,
    Fixed8tTest,
    ::testing::Combine(::testing::Range(0.0f, 2.0f, 0.5f),
                       ::testing::Range(0.5f, 2.0f, 0.5f)));

INSTANTIATE_TEST_SUITE_P(
    NegativeLhsPositiveRhs,
    Fixed8tTest,
    ::testing::Combine(::testing::Range(-1.5f, 0.0f, 0.5f),
                       ::testing::Range(0.5f, 2.0f, 0.5f)));

INSTANTIATE_TEST_SUITE_P(
    PositiveLhsNegativeRhs,
    Fixed8tTest,
    ::testing::Combine(::testing::Range(0.0f, 2.0f, 0.5f),
                       ::testing::Range(-1.5f, 0.0f, 0.5f)));

INSTANTIATE_TEST_SUITE_P(
    NegativeLhsNegativeRhs,
    Fixed8tTest,
    ::testing::Combine(::testing::Range(-1.5f, 0.0f, 0.5f),
                       ::testing::Range(-1.5f, 0.0f, 0.5f)));
