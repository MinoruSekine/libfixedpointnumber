//
// Copyright 2019,2020 Minoru Sekine
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

#ifndef INCLUDE_FIXEDPOINTNUMBER_STRING_PRIV_H_
#define INCLUDE_FIXEDPOINTNUMBER_STRING_PRIV_H_

#include <cassert>
#include <iomanip>
#include <sstream>
#include <string>

#include "fixedpointnumber_wider_int-priv.h"

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
    assert(abs_fixed_point >= 0);

    std::stringstream ss;
    if (is_negative) {
      ss << '-';
    }
    const auto integral_part = abs_fixed_point >> kBitsWidthOfDecimalPart;
    assert(integral_part >= 0);
    ss << integral_part
       << '.';

    using wider_int_t = impl::wider_int_t<IntType>;
    wider_int_t decimal_part = wider_int_t(abs_fixed_point) & kDecimalPartMask;
    if (decimal_part != 0) {
      while (decimal_part > 0) {
        decimal_part *= 10;
        const auto this_digit = (decimal_part >> kBitsWidthOfDecimalPart);
        assert(this_digit >= 0);
        assert(this_digit <= 9);
        ss << this_digit;
        decimal_part &= kDecimalPartMask;
      }
    } else {
      ss << '0';
    }

    str = ss.str();
  }

  return str;
}

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_STRING_PRIV_H_
