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
#include <ostream>
#include <string>

#include "fixedpointnumber.h"

namespace {

using fixed_t = fixedpointnumber::fixed_t<int32_t, 16>;

constexpr fixed_t kMinusOne(-1);
constexpr fixed_t kOne(1);
constexpr fixed_t kTwo(2);
constexpr fixed_t kFour(4);

constexpr int kDefaultLoopCount = 1000;

fixed_t CalcPi(int32_t converge_loop_count) {
  fixed_t pi(0);
  const fixed_t end(converge_loop_count);
  fixed_t sign = kOne;
  for (fixed_t i(0); i < end; ++i) {
    const fixed_t denom = i * kTwo + kOne;
    pi += kOne / denom * sign;
    sign *= kMinusOne;
  }

  return pi * kFour;
}

}  // namespace

int main(int argc, char** argv) {
  const int loop_count = (argc >= 2) ? std::stoi(argv[1]) : kDefaultLoopCount;
  const auto pi = CalcPi(loop_count);
  std::cout << "PI = " << pi << std::endl;

  return 0;
}