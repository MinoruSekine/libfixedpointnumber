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

#ifndef INCLUDE_FIXEDPOINTNUMBER_H_
#define INCLUDE_FIXEDPOINTNUMBER_H_

namespace fixedpointnumber {

template <typename IntType, std::size_t Q>
class fixed_t {
 public:
  template <typename SrcIntType>
  explicit fixed_t(SrcIntType src)
      : fixed_point_(src << kBitsWidthOfDecimalPart) {
  }

  template <typename DestIntType>
  operator DestIntType() const {
    return static_cast<DestIntType>(fixed_point_ >> kBitsWidthOfDecimalPart);
  }

 private:
  constexpr static std::size_t kBitsWidthOfDecimalPart = Q;

  IntType fixed_point_;
};

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_H_
