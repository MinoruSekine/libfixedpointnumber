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

#ifndef INCLUDE_FIXEDPOINTNUMBER_LIMITS_H_
#define INCLUDE_FIXEDPOINTNUMBER_LIMITS_H_

#include <cmath>
#include <limits>

#ifndef FIXEDPOINTNUMBER_INTERNAL
#error Do not include this file directly, include fixedpointnumber.h instead.
#endif

namespace fixedpointnumber {

namespace impl {

constexpr int digits_to_digits10(int digits) {
  // This is loose approximation of digits * log10(2).
  return (digits * 301) / 1000;
}

}  // namespace impl

}  // namespace fixedpointnumber

namespace std {

template <typename internal_int_t, std::size_t Q>
class numeric_limits<fixedpointnumber::fixed_t<internal_int_t, Q>> {
 public:
  using fixed_t = fixedpointnumber::fixed_t<internal_int_t, Q>;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed =
      std::numeric_limits<internal_int_t>::is_signed;
  static constexpr bool is_integer = false;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  static constexpr std::float_denorm_style has_denorm = std::denorm_absent;
  static constexpr bool has_denorm_loss = false;
  static constexpr std::float_round_style round_style =
      std::numeric_limits<internal_int_t>::round_style;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = std::numeric_limits<internal_int_t>::digits - Q;
  static constexpr int digits10 =
      fixedpointnumber::impl::digits_to_digits10(digits);
  static constexpr int max_digits10 = 0;
  static constexpr int radix = std::numeric_limits<internal_int_t>::radix;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = std::numeric_limits<internal_int_t>::traps;
  static constexpr bool tinyness_before =
      std::numeric_limits<internal_int_t>::tinyness_before;

  static constexpr fixed_t min() {
    return fixed_t(std::numeric_limits<internal_int_t>::min(), true);
  }

  static constexpr fixed_t lowest() {
    return fixed_t(std::numeric_limits<internal_int_t>::lowest(), true);
  }

  static constexpr fixed_t max() {
    return fixed_t(std::numeric_limits<internal_int_t>::max(), true);
  }

  static constexpr fixed_t epsilon() {
    return fixed_t(internal_int_t(0x01), true);
  }

  static constexpr fixed_t round_error() {
    return fixed_t(internal_int_t(0x01), true);
  }

  static constexpr fixed_t infinity() {
    return fixed_t(0);
  }

  static constexpr fixed_t quiet_NaN() {
    return fixed_t(0);
  }

  static constexpr fixed_t signaling_NaN() {
    return fixed_t(0);
  }

  static constexpr fixed_t denorm_min() {
    return fixed_t(0);
  }
};

}  // namespace std

#endif  // INCLUDE_FIXEDPOINTNUMBER_LIMITS_H_
