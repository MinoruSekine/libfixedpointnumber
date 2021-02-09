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

template <typename T>
T str_to_num(const char* str) {
  assert(str);

  std::stringstream ss;
  ss << str;
  T num(0);
  ss >> num;

  return num;
}

template <typename T>
void dump_range(const char* start_as_str, const char* end_as_str) {
  const T start(str_to_num<T>(start_as_str));
  const T end(str_to_num<T>(end_as_str));
  constexpr const T step = fixedpointnumber::numeric_limits<T>::min();

  std::cout << "Dump from " << start << " to " << end << std::endl;
  for (T i = start; i < end; i += step) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;

  return;
}

template <typename IntType, std::size_t start_Q>
class RangeDumper {
 public:
  static void dump_range(std::size_t param_q,
                         const char* start_as_str,
                         const char* end_as_str) {
    if (start_Q == param_q) {
      ::dump_range<fixedpointnumber::fixed_t<IntType, start_Q>>(start_as_str,
                                                                end_as_str);
    } else {
      RangeDumper<IntType, start_Q - 1>::dump_range(param_q,
                                                    start_as_str,
                                                    end_as_str);
    }
    return;
  }
};

template <typename IntType>
class RangeDumper<IntType, 0> {
 public:
  static void dump_range(std::size_t param_q,
                         const char* start_as_str,
                         const char* end_as_str) {
    (void)param_q;
    (void)start_as_str;
    (void)end_as_str;
    return;
  }
};

void usage() {
  std::cout << "Usage: dump_range Q_bits_width start_num end_num." << std::endl;

  return;
}

}  // namespace

int main(int argc, char* argv[]) {
  if (argc >= 4) {
    RangeDumper<uint8_t, 7>::dump_range(str_to_num<std::size_t>(argv[1]),
                                        argv[2],
                                        argv[3]);
  } else {
    usage();
  }

  return 0;
}
