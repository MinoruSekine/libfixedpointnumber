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
#include <iostream>

#include "fixedpointnumber.h"

using fixed_Q7_t = fixedpointnumber::fixed_t<int16_t, 7>;
using fixed_Q8_t = fixedpointnumber::fixed_t<int16_t, 8>;

int main(int, char**) {
  std::cout << "Input number to divide (less than 128): ";

  fixed_Q7_t num(0);
  std::cin >> num;

  std::cout << "Half of "
            << num
            << " is "
            << fixed_Q8_t(num) / fixed_Q8_t(2)
            << std::endl;

  return 0;
}
