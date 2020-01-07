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

#ifndef INCLUDE_FIXEDPOINTNUMBER_CONVERSION_PRIV_H_
#define INCLUDE_FIXEDPOINTNUMBER_CONVERSION_PRIV_H_

#ifndef FIXEDPOINTNUMBER_INTERNAL
#error Do not include this file directly, include fixedpointnumber.h instead.
#endif

namespace fixedpointnumber {

template <typename IntType, std::size_t Q>
template <typename SrcType>
constexpr IntType fixed_t<IntType, Q>::ToInternalType(
    typename std::enable_if<std::is_integral<SrcType>::value,
                            SrcType>::type src) {
  return static_cast<IntType>(src << kBitsWidthOfDecimalPart);
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
