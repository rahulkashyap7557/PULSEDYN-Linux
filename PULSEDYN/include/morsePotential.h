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

#ifndef MORSEPOTENTIAL_H
#define MORSEPOTENTIAL_H
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
#include "Particle.h"
#include "System.h"

class morsePotential : public System {
    public:
        /** Default constructor */
        morsePotential();
        morsePotential(Particle chainParticles);


        /** Default destructor */
        virtual ~morsePotential();
        /** Copy constructor
         *  \param other Object to copy from
         */
        morsePotential(const morsePotential& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        morsePotential& operator=(const morsePotential& other);

        //
        double Getk1() { return k1; }
        /** Set mass
         * \param val New value to set
         */
        void Setk1(double val) { k1 = val; }
        /** Access position
         * \return The current value of position
         */

        double Getk2() { return k2; }
        /** Set mass
         * \param val New value to set
         */
        void Setk2(double val) { k2 = val; }
        /** Access position
         * \return The current value of position
         */




        void f_accel(std::vector<Particle> &chainParticles);

        double f_calcPe(std::vector<Particle> &chainParticles);

        double Getpe(){ return pe;}

        void Setpe(double val){ pe = val; }

    protected:

    private:
        double k1;
        double k2;
        double pe;

};

#endif // morsePOTENTIAL_H

