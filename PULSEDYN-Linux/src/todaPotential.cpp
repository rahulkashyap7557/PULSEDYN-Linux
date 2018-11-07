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

todaPotential::todaPotential()
{
    //ctor
    k1 = 0.0;
    k2 = 1.0;

}

//todaPotential::todaPotential(Particle chainParticles)
//{
//    //ctor
//
//
//}
//
//todaPotential::~todaPotential()
//{
//    //dtor
//}
//
//todaPotential::todaPotential(const todaPotential& other)
//{
//    //copy ctor
//    k1 = other.k1;
//    k2 = other.k2;
//}
//
//todaPotential& todaPotential::operator=(const todaPotential& rhs)
//{
//    if (this == &rhs) return *this; // handle self assignment
//    //assignment operator
//    k1 = rhs.k1;
//    k2 = rhs.k2;
//
//    return *this;
//}
