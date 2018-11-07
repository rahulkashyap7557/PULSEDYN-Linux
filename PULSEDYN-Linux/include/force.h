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

#ifndef FORCE_H
#define FORCE_H
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
//#include "allIncludes.h"
using namespace std;


class Force
{
    public:
        /** Default constructor */
        Force();

        string Gettype() { return type; }
        /** Set type
         * \param val New value to set
         */
        void Settype(string val) { type = val; }
        /** Access t1
         * \return The current value of t1
         */
        double Gett1() { return t1; }
        /** Set t1
         * \param val New value to set
         */
        void Sett1(double val) { t1 = val; }
        /** Access t2
         * \return The current value of t2
         */
        double Gett2() { return t2; }
        /** Set t2
         * \param val New value to set
         */
        void Sett2(double val) { t2 = val; }
        /** Access t3
         * \return The current value of t3
         */
        double Gett3() { return t3; }
        /** Set t3
         * \param val New value to set
         */
        void Sett3(double val) { t3 = val; }
        /** Access frequency
         * \return The current value of frequency
         */
        double Getfrequency() { return frequency; }
        /** Set frequency
         * \param val New value to set
         */
        void Setfrequency(double val) { frequency = val; }
        /** Access ramp
         * \return The current value of ramp
         */
        double Getramp() { return ramp; }
        /** Set ramp
         * \param val New value to set
         */
        void Setramp(double val) { ramp = val; }
        /** Access amp
         * \return The current value of amp
         */
        double Getamp() { return amp; }
        /** Set amp
         * \param val New value to set
         */
        void Setamp(double val) { amp = val; }
        /** Access gamma
         * \return The current value of amp
         */
        double Getgamma() { return gamma; }
        /** Set gamma
         * \param val New value to set
         */
        void Setgamma(double val) { gamma = val; }

        // force functions

        double f_forceCalc(double tCurrent);

        double f_cosine(double tCurrent);
        double f_sine(double tCurrent);

    protected:

    private:
        string type; //!< Member variable "type"
        double t1; //!< Member variable "t1"
        double t2; //!< Member variable "t2"
        double t3; //!< Member variable "t3"
        double frequency; //!< Member variable "frequency"
        double ramp; //!< Member variable "ramp"
        double amp; //!< Member variable "amp"
        double gamma; //!< Member variable "gamma"
};

#endif // FORCE_H
