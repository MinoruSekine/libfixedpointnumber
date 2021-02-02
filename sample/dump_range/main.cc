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

#include <cassert>
#include <cstdint>
#include <iostream>

#include "fixedpointnumber.h"
#include "fixedpointnumber_limits.h"

using fixed_t = fixedpointnumber::fixed_t<uint8_t, 4>;

namespace {

fixed_t str_to_fixed_t(const char* str) {
  assert(str);

  std::stringstream ss;
  ss << str;
  fixed_t fixed(0);
  ss >> fixed;

  return fixed;
}

void usage() {
  std::cout << "Usage: dump_range start end." << std::endl;

  return;
}

}  // namespace

int main(int argc, char* argv[]) {
  if (argc >= 3) {
    const fixed_t start(str_to_fixed_t(argv[1]));
    const fixed_t end(str_to_fixed_t(argv[2]));

    std::cout << "Dump from " << start << " to " << end << std::endl;

    constexpr const fixed_t step =
        fixedpointnumber::numeric_limits<fixed_t>::min();
    for (fixed_t i = start; i < end; i += step) {
      std::cout << i << ' ';
    }
    std::cout << std::endl;
  } else {
    usage();
  }

  return 0;
}
