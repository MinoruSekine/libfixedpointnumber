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

#include <limits>

namespace fixedpointnumber {

/// std::numeric_limits compatible functions for fixed_t.
///
/// @tparam T Instantiated class of fixed_t template class to know limits
template <class T>
class numeric_limits {
 public:
  /// Representing T is signed or not.
  ///
  /// This is compatible to std::numeric_limits<T>::is_signed.
  static constexpr const bool is_signed =
      std::numeric_limits<typename T::type>::is_signed;
  /// Representing T is integer or not.
  ///
  /// This is compatible to std::numeric_limits<T>::is_integer.
  static constexpr const bool is_integer = false;
  /// Representing T is exact representation or not.
  ///
  /// This is compatible to std::numeric_limits<T>::is_exact.
  static constexpr const bool is_exact = true;
  /// Representing T has infinity or not.
  ///
  /// This is compatible to std::numeric_limits<T>::has_infinity.
  static constexpr const bool has_infinity = false;
  /// Representing T has quiet NaN or not.
  ///
  /// This is compatible to std::numeric_limits<T>::has_quiet_NaN.
  static constexpr const bool has_quiet_NaN = false;
  /// Representing T has signaling NaN or not.
  ///
  /// This is compatible to std::numeric_limits<T>::has_signaling_NaN.
  static constexpr const bool has_signaling_NaN = false;
  /// Repersenting denormalize style of T.
  ///
  /// This is compatible to std::numeric_limits<T>::has_denorm.
  static constexpr const std::float_denorm_style has_denorm =
      std::denorm_absent;
  /// Repersenting loss at denormalization is available or not.
  ///
  /// This is compatible to std::numeric_limits<T>::has_denorm_loss.
  static constexpr const bool has_denorm_loss = false;
  /// Repersenting float round style of T.
  ///
  /// This is compatible to std::numeric_limits<T>::round_style.
  static constexpr const std::float_round_style round_style =
      std::round_toward_zero;
  /// Representing T is IEC559 compatible or not.
  ///
  /// This is compatible to std::numeric_limits<T>::is_iec559.
  static constexpr const bool is_iec559 = false;
  /// Representing T is bounded or not.
  ///
  /// This is compatible to std::numeric_limits<T>::is_bounded.
  static constexpr const bool is_bounded = true;
  /// Representing overflow at calculating T is processed with modulo or not.
  ///
  /// This is compatible to std::numeric_limits<T>::is_modulo.
  static constexpr const bool is_modulo = false;
  /// Representing capable bits by radix(mostly 2) units.
  ///
  /// This is compatible to std::numeric_limits<T>::digits.
  static constexpr const int digits =
      std::numeric_limits<typename T::type>::digits;
  /// Representing capable number of digits by 10 radix.
  ///
  /// This is compatible to std::numeric_limits<T>::digits10.
  static constexpr const int digits10 =
      std::numeric_limits<typename T::type>::digits10;
  /// Representing necessary number of digits to serialize to 10 radix string.
  ///
  /// This is compatible to std::numeric_limits<T>::digits10.
  static constexpr const int max_digits10 = 0;
  /// Representing radix of internal representation of T.
  ///
  /// This is compatible to std::numeric_limits<T>::radix.
  static constexpr const int radix = 2;
  /// Compatible to std::numeric_limits<T>::min_exponent.
  static constexpr const int min_exponent = 0;
  /// Compatible to std::numeric_limits<T>::min_exponent10.
  static constexpr const int min_exponent10 = 0;
  /// Compatible to std::numeric_limits<T>::max_exponent.
  static constexpr const int max_exponent = 0;
  /// Compatible to std::numeric_limits<T>::max_exponent10.
  static constexpr const int max_exponent10 = 0;
  /// Representing there is afraid of traps (exceptions).
  ///
  /// This is compatible to std::numeric_limits<T>::traps.
  static constexpr const bool traps = true;
  /// Representing test underflow or not before round at calculating T.
  ///
  /// This is compatible to std::numeric_limits<T>::tinyness_before.
  static constexpr const bool tinyness_before = false;

  /// Get minimum normalized positive value.
  ///
  /// This is compatible to std::numeric_limits<T>::min()..
  static constexpr T min() noexcept {
    return T(typename T::type(1), true);
  }
  /// Get lowest value.
  ///
  /// This is compatible to std::numeric_limits<T>::lowest().
  static constexpr T lowest() noexcept {
    return T(std::numeric_limits<typename T::type>::lowest(), true);
  }
  /// Get maximum value.
  ///
  /// This is compatible to std::numeric_limits<T>::max().
  static constexpr T max() noexcept {
    return T(std::numeric_limits<typename T::type>::max(), true);
  }
  /// Get machine epsilon value.
  ///
  /// This is compatible to std::numeric_limits<T>::epsilon().
  static constexpr T epsilon() noexcept {
    return T(typename T::type(1), true);
  }
  /// Get maximum round error.
  ///
  /// This is compatible to std::numeric_limits<T>::round_error().
  static constexpr T round_error() noexcept {
    return T((typename T::type(1 << (T::kBitsWidthOfDecimalPart - 1))), true);
  }
  /// Get the value which represents infinity if T has it.
  ///
  /// This is compatible to std::numeric_limits<T>::infinity().
  static constexpr T infinity() noexcept {
    return T(0);
  }
  /// Get quiet NaN if T has it.
  ///
  /// This is compatible to std::numeric_limits<T>::quiet_NaN().
  static constexpr T quiet_NaN() noexcept {
    return T(0);
  }
  /// Get signaling NaN if T has it.
  ///
  /// This is compatible to std::numeric_limits<T>::signaling_NaN().
  static constexpr T signaling_NaN() noexcept {
    return T(0);
  }
  /// Get positive minimum denormalized value if T has it.
  ///
  /// This is compatible to std::numeric_limits<T>::denorm_min().
  static constexpr T denorm_min() noexcept {
    return T(0);
  }
};

template <class T> constexpr const bool numeric_limits<T>::is_signed;
template <class T> constexpr const bool numeric_limits<T>::is_integer;
template <class T> constexpr const bool numeric_limits<T>::is_exact;
template <class T> constexpr const bool numeric_limits<T>::has_infinity;
template <class T> constexpr const bool numeric_limits<T>::has_quiet_NaN;
template <class T> constexpr const bool numeric_limits<T>::has_signaling_NaN;
template <class T>
constexpr const std::float_denorm_style numeric_limits<T>::has_denorm;
template <class T> constexpr const bool numeric_limits<T>::has_denorm_loss;
template <class T>
constexpr const std::float_round_style numeric_limits<T>::round_style;
template <class T> constexpr const bool numeric_limits<T>::is_iec559;
template <class T> constexpr const bool numeric_limits<T>::is_bounded;
template <class T> constexpr const bool numeric_limits<T>::is_modulo;
template <class T> constexpr const int numeric_limits<T>::digits;
template <class T> constexpr const int numeric_limits<T>::digits10;
template <class T> constexpr const int numeric_limits<T>::max_digits10;
template <class T> constexpr const int numeric_limits<T>::radix;
template <class T> constexpr const int numeric_limits<T>::min_exponent;
template <class T> constexpr const int numeric_limits<T>::min_exponent10;
template <class T> constexpr const int numeric_limits<T>::max_exponent;
template <class T> constexpr const int numeric_limits<T>::max_exponent10;
template <class T> constexpr const bool numeric_limits<T>::traps;
template <class T> constexpr const bool numeric_limits<T>::tinyness_before;

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_LIMITS_H_
