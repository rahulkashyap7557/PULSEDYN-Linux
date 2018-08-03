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

#include "../include/allIncludes.h"

// All the simulation functions are written in the header file because
// they were defined as template functions.


Simulation::Simulation()
{
    //ctor
    timeStep = 0.00001;
    samplingFrequency = int(1/timeStep);
    totalTime = 10000;
    method = "gear5";
    systemSize = 100;

}

Simulation::~Simulation()
{
    //dtor
}

Simulation::Simulation(const Simulation& other)
{
    //copy ctor
    timeStep = other.timeStep;
    samplingFrequency = other.samplingFrequency;
    totalTime = other.totalTime;
}

Simulation& Simulation::operator=(const Simulation& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    timeStep = rhs.timeStep;
    samplingFrequency = rhs.samplingFrequency;
    totalTime = rhs.totalTime;

    return *this;
}

void Simulation::Setmethod(string val)
{
    method = val;
}

void Simulation::SetsystemSize(int val)
{
    systemSize = val;
}


