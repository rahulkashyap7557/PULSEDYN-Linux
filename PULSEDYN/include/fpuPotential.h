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
#ifndef FPUPOTENTIAL_H
#define FPUPOTENTIAL_H
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
//#include "allIncludes.h"
class fpuPotential : public System {
    public:
        /** Default constructor */
        fpuPotential();
        fpuPotential(Particle chainParticles);


        /** Default destructor */
        virtual ~fpuPotential();
        /** Copy constructor
         *  \param other Object to copy from
         */
        fpuPotential(const fpuPotential& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        fpuPotential& operator=(const fpuPotential& other);

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

         double Getk3() { return k3; }
        /** Set mass
         * \param val New value to set
         */
        void Setk3(double val) { k3 = val; }
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
        double k3;
        double pe;

};

#endif // POTENTIAL_H
