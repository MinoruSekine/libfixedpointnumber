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

#include <cmath>
#include <cstdint>

#include "gtest_compat.h"

#include "fixedpointnumber.h"
#include "fixedpointnumber_math.h"

namespace {

using fixed_t = fixedpointnumber::fixed_t<int16_t, 7>;

constexpr const fixed_t kFixedZero("0");

}  // namespace

class ClassificationNonZeroTest
    : public ::testing::TestWithParam<fixed_t> {
};

TEST_P(ClassificationNonZeroTest, fixed_isfinite) {
  EXPECT_FALSE(fixedpointnumber::fixed_isfinite(GetParam()));
}

TEST_P(ClassificationNonZeroTest, fixed_isinf) {
  EXPECT_FALSE(fixedpointnumber::fixed_isinf(GetParam()));
}

TEST_P(ClassificationNonZeroTest, fixed_isnan) {
  EXPECT_FALSE(fixedpointnumber::fixed_isnan(GetParam()));
}

TEST_P(ClassificationNonZeroTest, fixed_isnormal) {
  EXPECT_TRUE(fixedpointnumber::fixed_isnormal(GetParam()));
}

TEST_P(ClassificationNonZeroTest, fixed_classify) {
  EXPECT_EQ(fixedpointnumber::classification_t::kNormal,
            fixedpointnumber::fixed_classify(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(Instance0,
                         ClassificationNonZeroTest,
                         ::testing::Values(fixed_t("-1.5"),
                                           fixed_t("-1.25"),
                                           fixed_t("-1.0"),
                                           fixed_t("-0.75"),
                                           fixed_t("-0.5"),
                                           fixed_t("-0.25"),
                                           fixed_t("0.25"),
                                           fixed_t("0.5"),
                                           fixed_t("0.75"),
                                           fixed_t("1.0"),
                                           fixed_t("1.25"),
                                           fixed_t("1.5")));

TEST(ClassificationZeroTest, fixed_isfinite) {
  EXPECT_FALSE(fixedpointnumber::fixed_isfinite(kFixedZero));
}

TEST(ClassificationZeroTest, fixed_isinf) {
  EXPECT_FALSE(fixedpointnumber::fixed_isinf(kFixedZero));
}

TEST(ClassificationZeroTest, fixed_isnan) {
  EXPECT_FALSE(fixedpointnumber::fixed_isnan(kFixedZero));
}

TEST(ClassificationZeroTest, fixed_isnormal) {
  EXPECT_FALSE(fixedpointnumber::fixed_isnormal(kFixedZero));
}

TEST(ClassificationZeroTest, fixed_classify) {
  EXPECT_EQ(fixedpointnumber::classification_t::kZero,
            fixedpointnumber::fixed_classify(kFixedZero));
}
