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

#include <sstream>
#include <string>

#ifndef INCLUDE_FIXEDPOINTNUMBER_STRING_PRIV_H_
#define INCLUDE_FIXEDPOINTNUMBER_STRING_PRIV_H_

#ifndef FIXEDPOINTNUMBER_INTERNAL
#error Do not include this file directly, include fixedpointnumber.h instead.
#endif

namespace fixedpointnumber {

template <typename IntType, std::size_t Q>
std::string fixed_t<IntType, Q>::ToString() const {
  std::string str;

  if (fixed_point_ == 0) {
    str = "0";
  } else {
    const bool is_negative = (fixed_point_ < 0);
    const auto abs_fixed_point = is_negative ? -fixed_point_ : fixed_point_;
    int decimal_part = 0;
    int decimal_part_length = 0;
    int value = 5;
    for (auto i = 1 << (kBitsWidthOfDecimalPart - 1); i > 0; i = i >> 1) {
      decimal_part *= 10;
      if (abs_fixed_point & i) {
        decimal_part += value;
      }
      ++decimal_part_length;
      value *= 5;
    }
    while ((decimal_part_length > 1) && ((decimal_part % 10) == 0)) {
      decimal_part /= 10;
      --decimal_part_length;
    }

    std::stringstream ss;
    if (is_negative) {
      ss << '-';
    }
    ss << (abs_fixed_point >> kBitsWidthOfDecimalPart)
       << '.'
       << std::setfill('0')
       << std::right
       << std::setw(decimal_part_length)
       << decimal_part;

    str = ss.str();
  }

  return str;
}

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_STRING_PRIV_H_
