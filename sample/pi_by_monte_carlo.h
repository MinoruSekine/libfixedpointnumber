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

#ifndef SAMPLE_PI_BY_MONTE_CARLO_H_
#define SAMPLE_PI_BY_MONTE_CARLO_H_

#include <iostream>
#include <typeinfo>

namespace fixedpointnumber {

namespace sample {

namespace impl {

template <typename T>
T CalcPiByMonteCarlo(T radius, T step) {
  const T num_of_all_grid = (radius / step + T(1)) * (radius / step + T(1));
  T num_of_grid_in_radius(0);
  for (T y(0); y <= radius; y += step) {
    for (T x(0); x <= radius; x += step) {
      if ((x * x + y * y) < (radius * radius)) {
        ++num_of_grid_in_radius;
      }
    }
  }
  return num_of_grid_in_radius * T(4) / num_of_all_grid;
}

}  // namespace impl

template <typename T>
void PrintPiByMonteCarlo(T radius, T step) {
  std::cout << "Pi by Monte Carlo ("
            << typeid(T).name()
            << ") = "
            << impl::CalcPiByMonteCarlo<T>(radius, step)
            << std::endl;

  return;
}

}  // namespace sample

}  // namespace fixedpointnumber

#endif  // SAMPLE_PI_BY_MONTE_CARLO_H_
