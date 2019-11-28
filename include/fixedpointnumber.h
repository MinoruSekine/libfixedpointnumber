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

#include <string>
#include <type_traits>

#ifndef INCLUDE_FIXEDPOINTNUMBER_H_
#define INCLUDE_FIXEDPOINTNUMBER_H_

#define FIXEDPOINTNUMBER_INTERNAL

namespace fixedpointnumber {

/// Type for fixed point number.
///
/// @tparam IntType Internal integral type to hold fixed point number
/// @tparam Q       Bits width for decimal part
template <typename IntType, std::size_t Q>
class fixed_t {
 public:
  /// Default constructor.
  constexpr fixed_t() = default;

  /// Copy constructor.
  ///
  /// @param[in] src Value to construct from
  constexpr fixed_t(const fixed_t& src) = default;

  /// Move constructor.
  ///
  /// @param[in] src Value to construct from
  constexpr fixed_t(fixed_t&& src) = default;

  /// Construction from integral/floating-point types.
  ///
  /// @tparam SrcType Type to construct from
  ///
  /// @param[in] src Value to construct from
  template <typename SrcType>
  constexpr explicit fixed_t(SrcType src)
      : fixed_point_(ToIntType<SrcType>(src)) {
  }

  /// Construction from fixed_t which has another template param.
  ///
  /// @tparam SrcIntType Internal int type to hold fixed point number of source
  /// @tparam SrcQ       Bits width for decimal part of source
  ///
  /// @param[in] src fixed_t to construct from
  template <typename SrcIntType, std::size_t SrcQ>
  constexpr explicit fixed_t(const fixed_t<SrcIntType, SrcQ>& src)
    : fixed_point_(ToIntType<SrcIntType, SrcQ>(src)) {
  }

  /// Cast operator to specified integral or floating-point types.
  ///
  /// @tparam DestType Type to cast to.
  ///
  /// @return Casted DestType value converted from holding fixed point number.
  template <typename DestType>
  constexpr operator DestType() const {
    return FromIntType<DestType>(fixed_point_);
  }

  /// Copy operator.
  ///
  /// @param[in] src Value to substitute into this instance.
  ///
  /// @return Reference to this instance.
  fixed_t& operator= (const fixed_t& src) = default;

  /// Move operator.
  ///
  /// @param[in] src Value to substitute into this instance.
  ///
  /// @return Reference to this instance.
  fixed_t& operator= (fixed_t&& src) = default;

  /// Compound assignment operator+=.
  ///
  /// @param[in] rhs Value to add into this instance
  ///
  /// @return Reference to this instance added rhs into.
  fixed_t& operator+=(const fixed_t& rhs) {
    // Simplifying following expression as
    //   fixed_point_ += rhs.fixed_point_;
    // is not valid on some environments.
    // Because implicit integer promotion makes
    // from int to short (if IntType is short) cast implicitly,
    // and it can be error by compiler option -Werror=conversion.
    fixed_point_ = static_cast<IntType>(fixed_point_ + rhs.fixed_point_);
    return *this;
  }

  /// Add operator.
  ///
  /// @param[in] lhs One of two operand at left hand side
  /// @param[in] rhs One of two operand at right hand side
  ///
  /// @return Add result.
  friend fixed_t operator+(fixed_t lhs, const fixed_t& rhs) {
    lhs += rhs;
    return lhs;
  }

  /// Increment operator.
  ///
  /// @return Reference to this instance incremented.
  fixed_t& operator++() {
    constexpr fixed_t kOne(1);
    *this += kOne;
    return *this;
  }

  /// Comparison operator, equal.
  ///
  /// @param[in] lhs Left hand side value which is compared to
  /// @param[in] rhs Right hand side value which is compared to
  ///
  /// @retval true  lhs equals to rhs
  /// @retval false lhs doesn't equal to rhs
  friend bool operator==(const fixed_t& lhs, const fixed_t& rhs) {
    return lhs.fixed_point_ == rhs.fixed_point_;
  }

  /// Comparison operator, not equal.
  ///
  /// @param[in] lhs Left hand side value which is compared to
  /// @param[in] rhs Right hand side value which is compared to
  ///
  /// @retval true  lhs doesn't equal to rhs
  /// @retval false lhs equals to rhs
  friend bool operator!=(const fixed_t& lhs, const fixed_t& rhs) {
    return !(lhs == rhs);
  }

  /// Comparison operator, greater than.
  ///
  /// @param[in] lhs Left hand side value which is compared to
  /// @param[in] rhs Right hand side value which is compared to
  ///
  /// @retval true  lhs is greater than rhs
  /// @retval false lhs is not greater than rhs
  friend bool operator>(const fixed_t& lhs, const fixed_t& rhs) {
    return lhs.fixed_point_ > rhs.fixed_point_;
  }

  /// Get holding fixed point value as string.
  ///
  /// @return Holding fixed point value as string.
  std::string ToString() const;

  /// Internal integral value holding as fixed point value.
  IntType fixed_point_;

 private:
  /// Bits width of decimal part of this fixed point number type.
  constexpr static std::size_t kBitsWidthOfDecimalPart = Q;
  /// Coefficient to convert to internal fixed point value.
  constexpr static IntType kCoef = 1 << Q;

  /// Convert from some integral type value
  /// to internal integral fixed point type value.
  ///
  /// This member function is overload for conversion from integral type.
  ///
  /// @tparam SrcType Some integral type to convert from
  ///
  /// @param[in] src Integral value to convert from
  ///
  /// @return Coverted internal integral fixed point type value.
  template <typename SrcType>
  constexpr static IntType ToIntType(
      typename std::enable_if<std::is_integral<SrcType>::value,
                              SrcType>::type src);

  /// Convert from some floating-point type value
  /// to internal integral fixed point type value.
  ///
  /// This member function is overload for conversion from floating-point type.
  ///
  /// @tparam SrcType Some floating-point type to convert from
  ///
  /// @param[in] src Floating-point value to convert from
  ///
  /// @return Coverted internal integral fixed point type value.
  template <typename SrcType>
  constexpr static IntType ToIntType(
      typename std::enable_if<std::is_floating_point<SrcType>::value,
                              SrcType>::type src);

  /// Convert from fixed_t which has another template params.
  ///
  /// This member function is overload for conversion
  /// from fixed_t which has another template params.
  ///
  /// @tparam SrcIntType Internal int type to hold fixed point number of source
  /// @tparam SrcQ       Bits width for decimal part of source
  ///
  /// @param[in] src fixed_t to convert from
  ///
  /// @return Coverted internal integral fixed point type value.
  template <typename SrcIntType, std::size_t SrcQ>
  constexpr static IntType ToIntType(const fixed_t<SrcIntType, SrcQ>& src);

  /// Convert to some integral type value
  /// from internal integral fixed point type value.
  ///
  /// This member function is overload for conversion to integral type.
  ///
  /// @tparam DestType Integral type to conversion to.
  ///
  /// @param[in] src Internal integral type holding fixed point value
  ///
  /// @return Coverted DestIntType value from holding fixed point value
  template <typename DestType>
  constexpr static
  typename std::enable_if<std::is_integral<DestType>::value, DestType>::type
  FromIntType(IntType src);

  /// Convert to some floating-point type value
  /// from internal integral fixed point type value.
  ///
  /// This member function is overload for conversion to floating-point type.
  ///
  /// @tparam DestType Floating-point type to conversion to.
  ///
  /// @param[in] src Internal integral type holding fixed point value
  ///
  /// @return Coverted DestFloatingType value from holding fixed point value
  template <typename DestType>
  constexpr static
  typename std::enable_if<std::is_floating_point<DestType>::value,
                          DestType>::type
  FromIntType(IntType src);
};

}  // namespace fixedpointnumber

#include "fixedpointnumber_conversion-priv.h"
#include "fixedpointnumber_stream-priv.h"
#include "fixedpointnumber_string-priv.h"

#undef FIXEDPOINTNUMBER_INTERNAL

#endif  // INCLUDE_FIXEDPOINTNUMBER_H_
