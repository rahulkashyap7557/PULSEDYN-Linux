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

#include "../include/Output.h"

std::string Output::positionFileName = "position.dat";
std::string Output::velocityFileName = "velocity.dat";
std::string Output::accelerationFileName = "acceleration.dat";
std::string Output::keFileName = "ke.dat";
std::string Output::peFileName = "pe.dat";
std::string Output::totenFileName = "totalEnergy.dat";
std::string Output::restartFileName = "restart.dat";
std::string Output::massFileName = "mass.dat";
std::ofstream positionFile;
//
//Output::Output()
//{
//    //ctor
//}
//
//Output::~Output()
//{
//    //dtor
//}
//
//Output::Output(const Output& other)
//{
//    //copy ctor
//}
//
//Output& Output::operator=(const Output& rhs)
//{
//    if (this == &rhs) return *this; // handle self assignment
//    //assignment operator
//    return *this;
//}
//
//void Output::initializeOutputFiles()
//{
//
//
//}

void Output::writeToPosFile(double val, bool endline)
{
    std::ofstream positionFile;
    positionFile.open (positionFileName.c_str(), std::ofstream::out | std::ofstream::app); // Uncomment this line if you want to append to files instead of overwriting
    positionFile.precision(15);
    positionFile << val;

    if (endline)
    {
        positionFile << '\n';
    }
    else
    {
        positionFile << '\t';
    }


}

void Output::writeToVelFile(double val, bool endline)
{
    std::ofstream velocityFile;
    velocityFile.open (velocityFileName.c_str(), std::ofstream::out | std::ofstream::app);
    velocityFile.precision(15);

    velocityFile << val;

    if (endline)
    {
        velocityFile << '\n';
    }
    else
    {
        velocityFile << '\t';
    }

}

void Output::writeToAccFile(double val, bool endline)
{
    std::ofstream accelerationFile;
    accelerationFile.open (accelerationFileName.c_str(), std::ofstream::out | std::ofstream::app);
    accelerationFile.precision(15);

    accelerationFile << val;

    if (endline)
    {
        accelerationFile << '\n';
    }
    else
    {
        accelerationFile << '\t';
    }

}

void Output::writeToKeFile(double val, bool endline)
{
    std::ofstream keFile;
    keFile.open (keFileName.c_str(), std::ofstream::out | std::ofstream::app);
    keFile.precision(15);

    keFile << val;

    if (endline)
    {
        keFile << '\n';
    }
    else
    {
        keFile << '\t';
    }

}

void Output::writeToPeFile(double val, bool endline)
{
    std::ofstream peFile;
    peFile.open (peFileName.c_str(), std::ofstream::out | std::ofstream::app);
    peFile.precision(15);

    peFile << val;

    if (endline)
    {
        peFile << '\n';
    }
    else
    {
        peFile << '\t';
    }

}

void Output::writeToTotFile(double val, bool endline)
{
    std::ofstream totenFile;
    totenFile.open (totenFileName.c_str(), std::ofstream::out | std::ofstream::app);
    totenFile.precision(15);

    totenFile << val;

    if (endline)
    {
        totenFile << '\n';
    }
    else
    {
        totenFile << '\t';
    }

}

void Output::writeToResFile(double val, bool endline)
{
    std::ofstream restartFile;
    restartFile.open (restartFileName.c_str(), std::ofstream::out | std::ofstream::app);
    restartFile.precision(15);

    restartFile << val;

    if (endline)
    {
        restartFile << '\n';
    }
    else
    {
        restartFile << '\t';
    }

}

void Output::writeToMassFile(double val, bool endline)
{
    std::ofstream massFile;
    massFile.open (massFileName.c_str(), std::ofstream::out | std::ofstream::app);
    massFile.precision(15);

    massFile << val;

    if (endline)
    {
        massFile << '\n';
    }
    else
    {
        massFile << '\t';
    }

}
