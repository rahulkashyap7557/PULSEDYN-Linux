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

//#include "../include/boundaryConditions.h"
#include "../include/allIncludes.h"

// Function to calculate the dx for acceleration from left end of left boundary particle

double f_leftBoundaryConditionsAccel(std::vector<Particle> &chainParticles)
{
    double fac1 = 0.0;
    string lb;
    lb = chainParticles.at(0).Getlboundary();

    if (lb == "fixed")
    {
        fac1 = chainParticles.at(0).Getposition();
    }
    else if (lb == "open")
    {
        fac1 = 0.0;
    }
    else if (lb == "periodic") // periodic bc on left follows
    {
        int N = chainParticles.size() - 1;
        fac1 = chainParticles.at(0).Getposition() - chainParticles.at(N).Getposition();
    }
    else // assume fixed boundary at right
    {
        fac1 = chainParticles.at(0).Getposition();
        cout << "Assuming left boundary is fixed - accel" << endl;
    }

    return fac1;


}

// Function to calculate the dx for acceleration from right end of right boundary particle

double f_rightBoundaryConditionsAccel(std::vector<Particle> &chainParticles)
{
    double fac2 = 0.0;;
    string rb;
    int N = chainParticles.size() - 1;
    rb = chainParticles.at(N).Getrboundary();

    if (rb == "fixed")
    {
        fac2 = chainParticles.at(N).Getposition();
    }
    else if (rb == "open")
    {
        fac2 = 0.0;
    }
    else if (rb == "periodic") // periodic bc on right follows
    {
        fac2 = -chainParticles.at(0).Getposition() + chainParticles.at(N).Getposition();
    }
    else // Assume fixed boundary at right
    {
        fac2 = chainParticles.at(N).Getposition();
        cout << "Assume right boundary is fixed" << endl;
    }
    return fac2;
}

// Function to calculate the dx for pe from left end of left boundary particles


double f_leftBoundaryConditionsPe(std::vector<Particle> &chainParticles)
{
    double fac1;
    string lb;
    lb = chainParticles.at(0).Getlboundary();
    if (lb == "fixed")
    {
        fac1 = chainParticles.at(0).Getposition();
    }
    else if (lb == "open")
    {
        fac1 = 0.0;
    }
    else if (lb == "periodic") // periodic bc on left follows
    {
        int N = chainParticles.size() - 1;
        fac1 = chainParticles.at(0).Getposition() - chainParticles.at(N).Getposition();
    }
    else // assume fixed boundary at right
    {
        fac1 = chainParticles.at(0).Getposition();
        cout << "Assuming left boundary is fixed - pe" << endl;
    }

    return fac1;
}

// Function to calculate the dx for pe from right end of right boundary particle


double f_rightBoundaryConditionsPe(std::vector<Particle> &chainParticles)
{
    double fac2;
    string rb;
    int N = chainParticles.size() - 1;
    rb = chainParticles.at(N).Getrboundary();

    if (rb == "fixed")
    {
        fac2 = chainParticles.at(N).Getposition();

    }
    else if (rb == "open")
    {
        fac2 = 0.0;

    }
    else if (rb == "periodic") // periodic bc on right follows
    {
        fac2 = 0.0; // Set this equal to zero to avoid over-counting of boundary spring

    }
    else // Assume fixed boundary at right
    {
        fac2 = chainParticles.at(N).Getposition();
        cout << "Assume right boundary is fixed" << endl;
    }
    return fac2;
}
