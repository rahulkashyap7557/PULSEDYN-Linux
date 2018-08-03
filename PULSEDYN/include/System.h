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

#ifndef SYSTEM_H
#define SYSTEM_H

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


class System
{
    public:
        /** Default constructor */
        System();
        /** Default destructor */
        virtual ~System();
        /** Copy constructor
         *  \param other Object to copy from
         */
        System(const System& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        System& operator=(const System& other);

        /** Access left boundary
         * \return The current value of boundary
         */





    protected:


    private:


};

#endif // SYSTEM_H
