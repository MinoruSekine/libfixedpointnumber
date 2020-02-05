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

#ifndef INCLUDE_CONSTEXPR_STRING_H_
#define INCLUDE_CONSTEXPR_STRING_H_

#include <cstddef>

namespace constexprstr {

/// constexpr version of std::strlen().
///
/// @param[in] str String to calculate length
///
/// @return Length of str
constexpr std::size_t cstrlen(const char* str) {
  return ((*str == '\0') ? 0 : (1 + cstrlen(str + 1)));
}

}  // namespace constexprstr

#endif  // INCLUDE_CONSTEXPR_STRING_H_
