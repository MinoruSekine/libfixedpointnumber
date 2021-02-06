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

namespace constexprstr {

/// @addtogroup constexprstr constexprstr
///
/// constexprstr provides some string functions as constexpr functions.
///
/// @{

/// constexpr version of std::strlen().
///
/// This function returns length of string.
/// If the parameter is fixed at compile-time,
/// this function is compile-time resolvable as constexpr function.
///
/// @param[in] str String to calculate length
///
/// @return Length of str
constexpr std::size_t cstrlen(const char* str) {
  return ((*str == '\0') ? 0 : (1 + cstrlen(str + 1)));
}

/// constexpr version of std::strchr().
///
/// Find first position to appear specified character in string.
/// This function can be called as constexpr function.
///
/// @param[in] str '\0' terminated string to find specified character
/// @param[in] c   Character to find in string
///
/// @return Pointer to first position to appear specified character.
///         Returns nullptr, if can't find c in str.
constexpr const char* cstrchr(const char* str, int c) {
  return ((*str == c)
          ? str
          : ((*str == '\0') ? nullptr : cstrchr(str + 1, c)));
}

/// @}

}  // namespace constexprstr

#endif  // INCLUDE_CONSTEXPR_STRING_H_
