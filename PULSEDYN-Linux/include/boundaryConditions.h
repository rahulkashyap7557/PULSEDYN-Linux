/*
    Copyright (c) Rahul Kashyap 2017

    This file is part of PULSEDYN.

    PULSEDYN is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    PULSEDYN is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with PULSEDYN.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef BOUNDARYCONDITIONS_H
#define BOUNDARYCONDITIONS_H
#include <algorithm>
#include <cstdlib>
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>
#include <iterator>
#include <iomanip>
#include <sstream>
#include "allIncludes.h"

using namespace std;

double f_leftBoundaryConditionsAccel(std::vector<Particle> &chainParticles);
double f_rightBoundaryConditionsAccel(std::vector<Particle> &chainParticles);
double f_leftBoundaryConditionsPe(std::vector<Particle> &chainParticles);
double f_rightBoundaryConditionsPe(std::vector<Particle> &chainParticles);
#endif // BOUNDARYCONDITIONS_H


