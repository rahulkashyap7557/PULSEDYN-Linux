/*
    Copyright (c) Rahul Kashyap 2017

    This file is part of Nonlin.

    Nonlin is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    Nonlin is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Nonlin.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "../include/allIncludes.h"

lennardJonesPotential::lennardJonesPotential()
{
    //ctor
    k1 = 0.0;
    k2 = 1.0;
}

//lennardJonesPotential::lennardJonesPotential(Particle chainParticles)
//{
//    //ctor
//
//
//}
//
//lennardJonesPotential::~lennardJonesPotential()
//{
//    //dtor
//}
//
//lennardJonesPotential::lennardJonesPotential(const lennardJonesPotential& other)
//{
//    //copy ctor
//    k1 = other.k1;
//    k2 = other.k2;
//}
//
//lennardJonesPotential& lennardJonesPotential::operator=(const lennardJonesPotential& rhs)
//{
//    if (this == &rhs) return *this; // handle self assignment
//    //assignment operator
//    k1 = rhs.k1;
//    k2 = rhs.k2;
//
//    return *this;
//}
