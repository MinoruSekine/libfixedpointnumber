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

#include <type_traits>

#ifndef INCLUDE_FIXEDPOINTNUMBER_H_
#define INCLUDE_FIXEDPOINTNUMBER_H_

namespace fixedpointnumber {

/// Type for fixed point number.
///
/// @tparam IntType Internal integral type to hold fixed point number
/// @tparam Q       Bits width for decimal part
template <typename IntType, std::size_t Q>
class fixed_t {
 public:
  /// Copy constructor.
  ///
  /// @param[in] src Value to construct from
  constexpr explicit fixed_t(const fixed_t& src) = default;

  /// Construction from integral/floating-point types.
  ///
  /// @tparam SrcType Type to construct from
  ///
  /// @param[in] src Value to construct from
  template <typename SrcType>
  constexpr explicit fixed_t(SrcType src)
      : fixed_point_(ToIntType(src)) {
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

  /// Cast operator to specified integral floating-point types.
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

  /// Internal integral value holding as fixed point value.
  IntType fixed_point_;

 private:
  /// Bits width of decimal part of this fixed point number type.
  constexpr static std::size_t kBitsWidthOfDecimalPart = Q;
  /// Coefficient to convert to internal fixed point value.
  constexpr static IntType kCoef = 1 << Q;

  /// Convert to internal integral fixed point type value.
  ///
  /// @tparam SrcType Type to construct from
  ///
  /// @param[in] src Value to convert from
  ///
  /// @return Coverted internal intgral fixed point type value.
  template <typename SrcType>
  constexpr static IntType ToIntType(SrcType src) {
    return ToIntType(src, std::is_integral<SrcType>());
  }

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
  constexpr static IntType ToIntType(SrcType src, std::true_type) {
    return static_cast<IntType>(src << kBitsWidthOfDecimalPart);
  }

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
  constexpr static IntType ToIntType(SrcType src, std::false_type) {
    return static_cast<IntType>(src * static_cast<SrcType>(kCoef));
  }

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
  constexpr static IntType ToIntType(const fixed_t<SrcIntType, SrcQ>& src) {
    return ((Q > SrcQ)
            ? static_cast<IntType>(src.fixed_point_ << (Q - SrcQ))
            : static_cast<IntType>(src.fixed_point_ >> (SrcQ - Q)));
  }

  /// Convert from internal integral fixed point type value.
  ///
  /// @tparam DestType Type to conversion to.
  ///
  /// @param[in] src Internal integral type holding fixed point value
  ///
  /// @return Coverted DestType value from holding fixed point value
  template <typename DestType>
  constexpr static DestType FromIntType(IntType src) {
    return FromIntType<DestType>(src, std::is_integral<DestType>());
  }

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
  template <typename DestIntType>
  constexpr static DestIntType FromIntType(IntType src, std::true_type) {
    return static_cast<DestIntType>(src >> kBitsWidthOfDecimalPart);
  }

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
  template <typename DestFloatingType>
  constexpr static DestFloatingType FromIntType(IntType src, std::false_type) {
    return (static_cast<DestFloatingType>(src)
            * (static_cast<DestFloatingType>(1.0f)
               / static_cast<DestFloatingType>(kCoef)));
  }
};

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_H_
