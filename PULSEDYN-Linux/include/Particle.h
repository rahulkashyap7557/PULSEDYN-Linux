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

#ifndef PARTICLE_H
#define PARTICLE_H
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

using namespace std;
//#include "allIncludes.h"


class Particle
{
    public:
        /** Default constructor */
        Particle();

        /** Access mass
         * \return The current value of mass
         */
        double Getmass() { return mass; }
        /** Set mass
         * \param val New value to set
         */
        void Setmass(double val) { mass = val; }
        /** Access position
         * \return The current value of position
         */
        double Getposition() { return position; }
        /** Set position
         * \param val New value to set
         */
        void Setposition(double val) { position = val; }
        /** Access velocity
         * \return The current value of velocity
         */
        double Getvelocity() { return velocity; }
        /** Set velocity
         * \param val New value to set
         */
        void Setvelocity(double val) { velocity = val; }
        /** Access accel
         * \return The current value of accel
         */
        double Getaccel() { return accel; }
        /** Set accel
         * \param val New value to set
         */
        void Setaccel(double val) { accel = val; }

        double Getke(){return ke; }

        void Setke(double val){ ke = val; }

        string Getlboundary() { return lboundary; }

        /** Set left boundary
         * \param val New value to set
         */
        void Setlboundary(string val) { lboundary = val; }

                /** Access boundary
         * \return The current value of boundary
         */
        string Getrboundary() { return rboundary; }

        /** Set boundary
         * \param val New value to set
         */
        void Setrboundary(string val) { rboundary = val; }

        double f_calcKe();





    protected:

    private:
        double mass; //!< Member variable "mass"
        double position; //!< Member variable "position"
        double velocity; //!< Member variable "velocity"
        double accel; //!< Member variable "acceleration"
        double ke; //!< Member variable "kinetic energy"
        string lboundary;
        string rboundary ;
};

#endif // PARTICLE_H
