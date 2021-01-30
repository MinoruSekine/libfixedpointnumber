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

#include "pi_by_leibniz.h"

#include <cstdint>
#include <ostream>
#include <string>

#include "fixedpointnumber.h"

namespace {

using fixed_t = fixedpointnumber::fixed_t<int32_t, 16>;

constexpr fixed_t kOne(1);
constexpr fixed_t kTwo(2);
constexpr fixed_t kFour(4);

constexpr int kDefaultLoopCount = 1000;

fixed_t CalcPiByLeibniz(int32_t converge_loop_count) {
  fixed_t pi(0);
  const fixed_t end(converge_loop_count);
  fixed_t denom = kOne;
  for (fixed_t i(0); i < end; ++i) {
    pi += kFour / denom;
    denom += kTwo;
    pi -= kFour / denom;
    denom += kTwo;
  }

  return pi;
}

auto CalcPiByLeibnizHighPrecision(int32_t converge_loop_count)
    -> decltype(fixedpointnumber::fixed_div(kFour, kOne)) {
  decltype(fixedpointnumber::fixed_div(kFour, kOne)) pi(0);
  const fixed_t end(converge_loop_count);
  fixed_t denom = kOne;
  for (fixed_t i(0); i < end; ++i) {
    pi += fixedpointnumber::fixed_div(kFour, denom);
    denom += kTwo;
    pi -= fixedpointnumber::fixed_div(kFour, denom);
    denom += kTwo;
  }

  return pi;
}

}  // namespace

namespace fixedpointnumber {

namespace sample {

void PrintPiByLeibniz() {
  const auto pi = CalcPiByLeibniz(kDefaultLoopCount);
  std::cout << "PI by Leibniz fomula = " << pi << std::endl;

  const auto pi_high_precision =
      CalcPiByLeibnizHighPrecision(kDefaultLoopCount);
  std::cout << "PI by Leibniz fomula (High precision) = "
            << pi_high_precision
            << std::endl;

  return;
}

}  // namespace sample

}  // namespace fixedpointnumber
