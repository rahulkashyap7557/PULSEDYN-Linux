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
#include "boundaryConditions.h"
//#include "allIncludes.h"
class fpuPotential
{
    public:
        /** Default constructor */
        fpuPotential();

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


       void f_accel(std::vector<Particle> &chainParticles)
        {
            double fac1;
            double fac2;
            double fac12;
            double fac22;
            double fac23;
            double fac13;
            double mass;
            double a;

            string lb, rb;

            unsigned int N = chainParticles.size() - 1;

            lb = chainParticles.at(0).Getlboundary();
            rb = chainParticles.at(N).Getrboundary();


            unsigned int i, k;
            int j;


            for (i = 0; i < N + 1; i++)
            {
                j = i - 1;
                k = i + 1;
                a = 0.;
                if (j == -1)
                {
                    fac1 = f_leftBoundaryConditionsAccel(chainParticles);
                }
                else
                {
                    fac1 = chainParticles.at(i).Getposition() - chainParticles.at(j).Getposition();
                }

                if (k == chainParticles.size())
                {
                    fac2 = f_rightBoundaryConditionsAccel(chainParticles);
                }
                else
                {
                    fac2 = chainParticles.at(i).Getposition() - chainParticles.at(k).Getposition();
                }

                mass = chainParticles.at(i).Getmass();

                fac12 = fac1*fac1;
                fac22 = fac2*fac2;
                fac13 = fac1*fac12;
                fac23 = fac2*fac22;


                a = -2.0*k1*(fac1 + fac2) + 3.0*k2*(-fac12 + fac22) - 4.0*k3*(fac13 + fac23);
                a = a/mass;
                chainParticles[i].Setaccel(a);
            }
        }

        double f_calcPe(std::vector<Particle> &chainParticles)
        {
             int j;
             unsigned int i;
             double dx;
             double fac;
             double potentialEnergy;
             double totalPotentialEnergy = 0.;

             unsigned int systemSize = chainParticles.size();
             for (i = 0; i < systemSize; i++)
             {
                 j = i - 1;
                  if (j == -1)
                  {
                      dx = f_leftBoundaryConditionsPe(chainParticles);
                  }
                  else
                  {
                      dx = chainParticles.at(i).Getposition() - chainParticles.at(j).Getposition();
                  }
                  fac = dx*dx;

                  potentialEnergy = k1*fac + k3*fac*fac + k2*dx*dx*dx;
                  Output::writeToPeFile(potentialEnergy, false);
                  totalPotentialEnergy +=  potentialEnergy;
             }

             // Calculate energies
             double lastSpring;
             lastSpring = f_rightBoundaryConditionsPe(chainParticles);

             // Technically, it should be k1*(-lastSpring)*(-lastSpring) etc...,
             // But the even powers take care of the negative signs. For other potentials, this makes a difference.
             potentialEnergy = k1*lastSpring*lastSpring + k2*(-lastSpring)*(-lastSpring)*(-lastSpring) + k3*lastSpring*lastSpring*lastSpring*lastSpring;
             totalPotentialEnergy += potentialEnergy;
             Output::writeToPeFile(potentialEnergy, true);
             return totalPotentialEnergy;
        }



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
