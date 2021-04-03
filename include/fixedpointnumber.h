//
// Copyright 2019,2020,2021 Minoru Sekine
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

#ifndef INCLUDE_FIXEDPOINTNUMBER_H_
#define INCLUDE_FIXEDPOINTNUMBER_H_

#include <string>
#include <type_traits>

#define FIXEDPOINTNUMBER_INTERNAL

#include "fixedpointnumber_wider_int-priv.h"

namespace fixedpointnumber {

/// Type for fixed point number.
///
/// This template class provides fixed point number
/// with specified integer type and specified Q value.
///
/// @tparam internal_int_t Internal integral type to hold fixed point number
/// @tparam Q              Bits width for decimal part
template <typename internal_int_t, std::size_t Q>
class fixed_t {
 public:
  /// Alias of internal integer type which holding fixed point number.
  using type = internal_int_t;

  /// Bits width of decimal part of this fixed point number type.
  constexpr static std::size_t kBitsWidthOfDecimalPart = Q;
  /// Bits mask of decimal part of this type.
  constexpr static internal_int_t kDecimalPartMask =
      static_cast<internal_int_t>((impl::wider_int_t<internal_int_t>(1)
                                   << kBitsWidthOfDecimalPart)
                                  - 1);
  static_assert(kDecimalPartMask > 0,
                "Can't calculate mask for decimal part.");
  /// Bits mask of integral part of this type.
  constexpr static internal_int_t kIntegralPartMask =
      static_cast<internal_int_t>(~kDecimalPartMask);

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
      : fixed_point_(ToInternalType<SrcType>(src)) {
  }

  /// Construction from fixed_t which has another template param.
  ///
  /// @tparam SrcIntType Internal int type to hold fixed point number of source
  /// @tparam SrcQ       Bits width for decimal part of source
  ///
  /// @param[in] src fixed_t to construct from
  template <typename SrcIntType, std::size_t SrcQ>
  constexpr explicit fixed_t(const fixed_t<SrcIntType, SrcQ>& src)
      : fixed_point_(ToInternalType<SrcIntType, SrcQ>(src)) {
  }

  /// Construction directly from internal integer value.
  ///
  /// This constructor should be mostlty internal use.
  ///
  /// @param[in] src fixed_t to construct from
  constexpr fixed_t(internal_int_t src, bool)
      : fixed_point_(src) {
  }

  /// Cast operator to specified integral or floating-point types.
  ///
  /// @tparam DestType Type to cast to.
  ///
  /// @return Casted DestType value converted from holding fixed point number.
  template <typename DestType>
  constexpr operator DestType() const {
    return FromInternalType<DestType>(fixed_point_);
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
    // from int to short (if internal_int_t is short) cast implicitly,
    // and it can be error by compiler option -Werror=conversion.
    fixed_point_ = static_cast<internal_int_t>(fixed_point_ + rhs.fixed_point_);
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

  /// Compound assignment operator-=.
  ///
  /// @param[in] rhs Value to substruct from this instance
  ///
  /// @return Reference to this instance substructed rhs from.
  fixed_t& operator-=(const fixed_t& rhs) {
    // Simplifying following expression as
    //   fixed_point_ += rhs.fixed_point_;
    // is not valid on some environments.
    // Because implicit integer promotion makes
    // from int to short (if internal_int_t is short) cast implicitly,
    // and it can be error by compiler option -Werror=conversion.
    fixed_point_ = static_cast<internal_int_t>(fixed_point_ - rhs.fixed_point_);
    return *this;
  }

  /// Sub operator.
  ///
  /// @param[in] lhs One of two operand at left hand side
  /// @param[in] rhs One of two operand at right hand side
  ///
  /// @return Sub result.
  friend fixed_t operator-(fixed_t lhs, const fixed_t& rhs) {
    lhs -= rhs;
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

  /// Decrement operator.
  ///
  /// @return Reference to this instance decremented.
  fixed_t& operator--() {
    constexpr fixed_t kOne(1);
    *this -= kOne;
    return *this;
  }

  /// Compound assignment operator*=.
  ///
  /// @param[in] rhs Value to multiply into this instance
  ///
  /// @return Reference to this instance multiplied rhs into.
  fixed_t& operator*=(const fixed_t& rhs) {
    *this = *this * rhs;
    return *this;
  }

  /// Compound assignment operator/=.
  ///
  /// @param[in] rhs Value to divide into this instance
  ///
  /// @return Reference to this instance divided rhs into.
  fixed_t& operator/=(const fixed_t& rhs) {
    *this = *this / rhs;
    return *this;
  }

  /// Unary operator+.
  ///
  /// @return Same value as source
  fixed_t operator+() {
    return *this;
  }

  /// Unary operator+.
  ///
  /// @return Same value as source
  fixed_t operator-() {
    // static_cast is necessary here because of implicit integral promotion.
    fixed_point_ = static_cast<internal_int_t>(-fixed_point_);
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

  /// Comparison operator, greater than or equals.
  ///
  /// @param[in] lhs Left hand side value which is compared to
  /// @param[in] rhs Right hand side value which is compared to
  ///
  /// @retval true  lhs is greater than rhs, or equals to rhs
  /// @retval false lhs is not greater than rhs and doesn't equal to rhs
  friend bool operator>=(const fixed_t& lhs, const fixed_t& rhs) {
    return (rhs <= lhs);
  }

  /// Comparison operator, less than.
  ///
  /// @param[in] lhs Left hand side value which is compared to
  /// @param[in] rhs Right hand side value which is compared to
  ///
  /// @retval true  lhs is less than rhs
  /// @retval false lhs is not less than rhs
  friend bool operator<(const fixed_t& lhs, const fixed_t& rhs) {
    return (rhs > lhs);
  }

  /// Comparison operator, less than or equals.
  ///
  /// @param[in] lhs Left hand side value which is compared to
  /// @param[in] rhs Right hand side value which is compared to
  ///
  /// @retval true  lhs is less than rhs, or equals to rhs
  /// @retval false lhs is not greater than rhs and doesn't equal to rhs
  friend bool operator<=(const fixed_t& lhs, const fixed_t& rhs) {
    return !(lhs > rhs);
  }

  /// Get holding fixed point value as string.
  ///
  /// @return Holding fixed point value as string.
  std::string ToString() const;

  /// Set holding fixed point value with string.
  ///
  /// @param[in] str Stringificated integer or floating point value,
  ///                like as "23", "4.5".
  ///
  /// @return Reference to this instance.
  fixed_t& FromString(const char* str) {
    return fixed_point_ = this->ToInternalType<const char*>(str), *this;
  }

  /// Internal integral value holding as fixed point value.
  internal_int_t fixed_point_;

 private:
  /// Coefficient to convert from/to floating point type.
  ///
  /// This coefficient will be used
  /// both conversion from floating point type to internal type,
  /// and conversion from internal type to floating point type.
  constexpr static internal_int_t kCoef = static_cast<internal_int_t>(1) << Q;

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
  constexpr static internal_int_t ToInternalType(
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
  constexpr static internal_int_t ToInternalType(
      typename std::enable_if<std::is_floating_point<SrcType>::value,
                              SrcType>::type src);

  template <typename SrcType>
  constexpr static internal_int_t ToInternalType(
    typename std::enable_if<std::is_same<SrcType, const char*>::value,
                            SrcType>::type str);

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
  constexpr static
  internal_int_t ToInternalType(const fixed_t<SrcIntType, SrcQ>& src);

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
  FromInternalType(internal_int_t src);

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
  FromInternalType(internal_int_t src);
};

/// Function to multiply fixed_t with keeping precision.
///
/// Result fixed_t<> type is not same as both lhs and rhs type.
/// That type has enough precision to keep multiply result,
/// twice bit width to keep fixed point data
/// and bits width to assign for keeping decimal parts will be widen.
///
/// @tparam internal_int_t Internal integral type to hold fixed point number
/// @tparam l_Q            Bits width for decimal part of lhs
/// @tparam r_Q            Bits width for decimal part of rhs
///
/// @param lhs Left hand side value to multiply
/// @param rhs Right hand side value to multiply
///
/// @return Multiply result
template <typename internal_int_t, std::size_t l_Q, std::size_t r_Q>
auto fixed_mul(fixed_t<internal_int_t, l_Q> lhs,
               const fixed_t<internal_int_t, r_Q> rhs)
    -> fixed_t<impl::wider_int_t<internal_int_t>, l_Q + r_Q> {
  using wider_int_t = impl::wider_int_t<internal_int_t>;
  const auto lhs_wide = static_cast<wider_int_t>(lhs.fixed_point_);
  const auto rhs_wide = static_cast<wider_int_t>(rhs.fixed_point_);

  using result_t = fixed_t<wider_int_t, l_Q + r_Q>;

  return result_t(static_cast<wider_int_t>(lhs_wide * rhs_wide), true);
}

/// Function to divide fixed_t with keeping precision.
///
/// Result fixed_t<> type is not same as both lhs and rhs type.
/// That type has enough precision to keep divide result,
/// twice bit width to keep fixed point data
/// and bits width to assign for keeping decimal parts will be widen.
///
/// @tparam internal_int_t Internal integral type to hold fixed point number
/// @tparam l_Q            Bits width for decimal part of lhs
/// @tparam r_Q            Bits width for decimal part of rhs
///
/// @param lhs Left hand side value to divide
/// @param rhs Right hand side value to divide
///
/// @return Divide result
template <typename internal_int_t, std::size_t l_Q, std::size_t r_Q>
auto fixed_div(fixed_t<internal_int_t, l_Q> lhs,
               const fixed_t<internal_int_t, r_Q> rhs)
    -> fixed_t<impl::wider_int_t<internal_int_t>,
               l_Q
               + (sizeof(impl::wider_int_t<internal_int_t>) * 8U
                  - sizeof(internal_int_t) * 8U)
               - r_Q> {
  using wider_int_t = impl::wider_int_t<internal_int_t>;
  constexpr std::size_t kResultBits = sizeof(wider_int_t) * 8U;
  constexpr std::size_t kSrcBits    = sizeof(internal_int_t) * 8U;
  const auto lhs_wide = static_cast<wider_int_t>(lhs.fixed_point_);
  const auto rhs_wide = static_cast<wider_int_t>(rhs.fixed_point_);

  using result_t = fixed_t<wider_int_t, l_Q + (kResultBits - kSrcBits) - r_Q>;

  const auto wider_int_result =
      static_cast<wider_int_t>((lhs_wide << (kResultBits - kSrcBits))
                               / rhs_wide);

  return result_t(wider_int_result, true);
}

/// Multiply operator.
///
/// This operator keeps same type as lhs and rhs after multiply.
///
/// @tparam internal_int_t Internal integral type to hold fixed point number
/// @tparam Q              Bits width for decimal part
///
/// @return Multiply result
///
/// @note Precision of multiply result can be lossy in this operator
template <typename internal_int_t, std::size_t Q>
fixed_t<internal_int_t, Q> operator*(fixed_t<internal_int_t, Q> lhs,
                                     const fixed_t<internal_int_t, Q>& rhs) {
  return static_cast<fixed_t<internal_int_t, Q>>(fixed_mul(lhs, rhs));
}

/// Division operator.
///
/// This operator keeps same type as lhs and rhs after divide.
///
/// @tparam internal_int_t Internal integral type to hold fixed point number
/// @tparam Q              Bits width for decimal part
///
/// @return Divide result
///
/// @note Precision of multiply result can be lossy in this operator
template <typename internal_int_t, std::size_t Q>
fixed_t<internal_int_t, Q> operator/(fixed_t<internal_int_t, Q> lhs,
                                     const fixed_t<internal_int_t, Q>& rhs) {
  return static_cast<fixed_t<internal_int_t, Q>>(fixed_div(lhs, rhs));
}

}  // namespace fixedpointnumber

#include "fixedpointnumber_conversion-priv.h"
#include "fixedpointnumber_stream-priv.h"
#include "fixedpointnumber_string-priv.h"

#undef FIXEDPOINTNUMBER_INTERNAL

#endif  // INCLUDE_FIXEDPOINTNUMBER_H_
