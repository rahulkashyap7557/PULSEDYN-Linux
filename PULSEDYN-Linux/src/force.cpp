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

#include "../include/force.h"

Force::Force()
{
    //ctor
    type = "cosine";
    t1 = 0.;
    t2 = 0.;
    t3 = 0.;
    frequency = 0.;
    ramp = 0.;
    amp = 0.;

}
//
//Force::~Force()
//{
//    //dtor
//}
//
//Force::Force(const Force& other)
//{
//    //copy ctor
//    type = other.type;
//    t1 = other.t1;
//    t2 = other.t2;
//    t3 = other.t3;
//    frequency = other.frequency;
//    ramp = other.ramp;
//    amp = other.amp;
//}
//
//Force& Force::operator=(const Force& rhs)
//{
//    if (this == &rhs) return *this; // handle self assignment
//    //assignment operator
//    type = rhs.type;
//    t1 = rhs.t1;
//    t2 = rhs.t2;
//    t3 = rhs.t3;
//    frequency = rhs.frequency;
//    ramp = rhs.ramp;
//    amp = rhs.amp;
//
//    return *this;
//
//    return *this;
//}

double Force::f_forceCalc(double tCurrent)
{
    double force = 0.;
    if (type == "cosine")
    {
        force = f_cosine(tCurrent);
    }
    else if(type == "sine")
    {
        force = f_sine(tCurrent);
    }
    return force;
}

double Force::f_cosine(double tCurrent)
{
    double force;
    double freq1;
    freq1 = frequency + ramp*tCurrent;
    force = amp*cos(freq1*tCurrent);
    return force;
}

double Force::f_sine(double tCurrent)
{
    double force;
    double freq1;
    freq1 = frequency + ramp*tCurrent;
    force = amp*sin(freq1*tCurrent);
    return force;
}

