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

#include "fixedpointnumber.h"

#include "pi_by_leibniz.h"
#include "pi_by_monte_carlo.h"

int main(int, char**) {
  fixedpointnumber::sample::PrintPiByLeibniz();

  fixedpointnumber::sample::PrintPiByMonteCarlo(100.0f, 1.0f);

  using monte_carlo_fixed_t = fixedpointnumber::fixed_t<int32_t, 16>;
  fixedpointnumber::sample::PrintPiByMonteCarlo<monte_carlo_fixed_t>(
      monte_carlo_fixed_t(100.0f), monte_carlo_fixed_t(1.0f));

  return 0;
}
