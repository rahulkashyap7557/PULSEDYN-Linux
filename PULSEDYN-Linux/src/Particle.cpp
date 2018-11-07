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

#include "../include/Particle.h"


Particle::Particle()
{
    //ctor
    mass = 1.0;
    position = 0.0;
    velocity = 0.0;
    accel = 0.0;
    lboundary = "fixed";
    rboundary = "fixed";
}

//Particle::~Particle()
//{
//    //dtor
//}
//
//Particle::Particle(const Particle& other)
//{
//    //copy ctor
//    mass = other.mass;
//    position = other.position;
//    velocity = other.velocity;
//    accel = other.accel;
//}
//
//Particle& Particle::operator=(const Particle& rhs)
//{
//    if (this == &rhs) return *this; // handle self assignment
//    //assignment operator
//    mass = rhs.mass;
//    position = rhs.position;
//    velocity = rhs.velocity;
//    accel = rhs.accel;
//
//    return *this;
//}

double Particle::f_calcKe()
{
    double k = 0.5*mass*velocity*velocity;
    Setke(k);
    return k;
}
