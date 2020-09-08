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

#ifndef INCLUDE_FIXEDPOINTNUMBER_STREAM_PRIV_H_
#define INCLUDE_FIXEDPOINTNUMBER_STREAM_PRIV_H_

#include <iostream>

#ifndef FIXEDPOINTNUMBER_INTERNAL
#error Do not include this file directly, include fixedpointnumber.h instead.
#endif

namespace fixedpointnumber {

/// Stream operator to output fixed_t as string.
///
/// @tparam IntType Internal integral type to hold fixed point number
/// @tparam Q       Bits width for decimal part
///
/// @param os    ostream to output to
/// @param fixed Instance of fixed_t value to output
///
/// @return Reference to ostream
///
/// @relates fixed_t
template <typename IntType, std::size_t Q>
std::ostream& operator<<(std::ostream& os, const fixed_t<IntType, Q>& fixed) {
  os << fixed.ToString();

  return os;
}

}  // namespace fixedpointnumber

#endif  // INCLUDE_FIXEDPOINTNUMBER_STREAM_PRIV_H_
