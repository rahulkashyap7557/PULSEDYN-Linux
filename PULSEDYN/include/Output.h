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

#ifndef OUTPUT_H
#define OUTPUT_H
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
//#include "allIncludes.h"

class Output
{
    public:
        /** Default constructor */
        Output();
        /** Default destructor */
        virtual ~Output();
        /** Copy constructor
         *  \param other Object to copy from
         */
        Output(const Output& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        Output& operator=(const Output& other);

        /** Access fileName
         * \return The current value of fileName
         */

        /** Set fileName
         * \param val New value to set
         */

       static void initializeOutputFiles();

       static void writeToVelFile(double val, bool endline);
       static void writeToPosFile(double val, bool endline);
       static void writeToAccFile(double val, bool endline);
       static void writeToKeFile(double val, bool endline);
       static void writeToPeFile(double val, bool endline);
       static void writeToTotFile(double val, bool endline);
       static void writeToResFile(double val, bool endline);
       static void writeToMassFile(double val, bool endline);


    protected:

    private:
        static std::string positionFileName;
        static std::string velocityFileName;
        static std::string accelerationFileName;
        static std::string keFileName;
        static std::string peFileName;
        static std::string totenFileName;
        static std::string restartFileName;
        static std::string massFileName;

        static std::ofstream velocityFile;
        static std::ofstream accelerationFile;
        static std::ofstream keFile;
        static std::ofstream peFile;
        static std::ofstream totenFile;
        static std::ofstream restartFile;
        static std::ofstream massFile;
};

#endif // OUTPUT_H
