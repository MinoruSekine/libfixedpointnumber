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

#ifndef INCLUDE_FIXEDPOINTNUMBER_CONVERSION_PRIV_H_
#define INCLUDE_FIXEDPOINTNUMBER_CONVERSION_PRIV_H_

#include <type_traits>

#ifndef FIXEDPOINTNUMBER_INTERNAL
#error Do not include this file directly, include fixedpointnumber.h instead.
#endif

namespace fixedpointnumber {

namespace impl {

template <typename T>
constexpr T abs(T n) {
  return ((n >= static_cast<T>(0)) ? n : static_cast<T>(-n));
}

template <typename T>
constexpr T sign(T n) {
  return ((n > static_cast<T>(0))
          ? static_cast<T>(1)
          : ((n < static_cast<T>(0))
             ? static_cast<T>(-1)
             : static_cast<T>(0)));
}

}  // namespace impl

template <typename IntType, std::size_t Q>
template <typename SrcType>
constexpr IntType fixed_t<IntType, Q>::ToInternalType(
    typename std::enable_if<std::is_integral<SrcType>::value,
                            SrcType>::type src) {
  return static_cast<IntType>((impl::abs(src) << kBitsWidthOfDecimalPart)
                              * impl::sign(src));
}

template <typename IntType, std::size_t Q>
template <typename SrcType>
constexpr IntType fixed_t<IntType, Q>::ToInternalType(
    typename std::enable_if<std::is_floating_point<SrcType>::value,
                            SrcType>::type src) {
  return static_cast<IntType>(src * static_cast<SrcType>(kCoef));
}

template <typename IntType, std::size_t Q>
template <typename SrcIntType, std::size_t SrcQ>
constexpr IntType
fixed_t<IntType, Q>::ToInternalType(const fixed_t<SrcIntType, SrcQ>& src) {
  return ((Q > SrcQ)
          ? static_cast<IntType>(src.fixed_point_ << (Q - SrcQ))
          : static_cast<IntType>(src.fixed_point_ >> (SrcQ - Q)));
}

template <typename IntType, std::size_t Q>
template <typename DestType>
constexpr
typename std::enable_if<std::is_integral<DestType>::value, DestType>::type
fixed_t<IntType, Q>::FromInternalType(IntType src) {
  return static_cast<DestType>(src >> kBitsWidthOfDecimalPart);
}

template <typename IntType, std::size_t Q>
template <typename DestType>
constexpr
typename std::enable_if<std::is_floating_point<DestType>::value, DestType>::type
fixed_t<IntType, Q>::FromInternalType(IntType src) {
  return (static_cast<DestType>(src)
          * (static_cast<DestType>(1.0f) / static_cast<DestType>(kCoef)));
}

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_CONVERSION_PRIV_H_
