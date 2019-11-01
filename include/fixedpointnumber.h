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

template <typename IntType, std::size_t Q>
class fixed_t {
 public:
  template <typename SrcType>
  explicit fixed_t(SrcType src)
      : fixed_point_(ToIntType(src)) {
  }

  template <typename DestType>
  operator DestType() const {
    return FromIntType<DestType>(fixed_point_);
  }

 private:
  constexpr static std::size_t kBitsWidthOfDecimalPart = Q;

  template <typename SrcType>
  static IntType ToIntType(SrcType src) {
    return ToIntType(src, std::is_integral<SrcType>());
  }

  template <typename SrcType>
  static IntType ToIntType(SrcType src, std::true_type) {
    return src << kBitsWidthOfDecimalPart;
  }

  template <typename DestType>
  static DestType FromIntType(IntType src) {
    return FromIntType<DestType>(src, std::is_integral<DestType>());
  }

  template <typename DestIntType>
  static DestIntType FromIntType(IntType src, std::true_type) {
    return static_cast<DestIntType>(src >> kBitsWidthOfDecimalPart);
  }

  IntType fixed_point_;
};

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_H_
