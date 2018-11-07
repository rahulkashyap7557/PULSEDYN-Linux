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
#include "boundaryConditions.h"

class morsePotential
{
    public:
        /** Default constructor */
        morsePotential();
        morsePotential(Particle chainParticles);

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


        void f_accel(std::vector<Particle> &chainParticles)
        {
            double fac1;
            double fac2;
            unsigned int i, k;
            int j;
			
            for (i = 0; i < chainParticles.size(); i++)
            {
                j = i - 1;
                k = i + 1;
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
				double mass;
                mass = chainParticles.at(i).Getmass();
				
				double a = 0.;
                a = 2.*k2*k1*(exp(k2*fac2) - exp(2.*k2*fac2) + exp(-2.*k2*fac1) - exp(-k2*fac1));
                a = a/mass;

                chainParticles[i].Setaccel(a);
            }
        }

        double f_calcPe(std::vector<Particle> &chainParticles)
        {
             unsigned int i;
             int j;
             double dx;

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

                  potentialEnergy = k1*(exp(-k2*dx) - 1)*(exp(-k2*dx) - 1); // calculates and records potential energy at t = 0
                  Output::writeToPeFile(potentialEnergy, false);
                  totalPotentialEnergy +=  potentialEnergy;

             }
             double lastSpring;
             lastSpring = f_rightBoundaryConditionsPe(chainParticles);

             potentialEnergy = k1*(exp(-k2*(-lastSpring)) - 1)*(exp(-k2*(-lastSpring)) - 1);
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
        double pe;

};

#endif // morsePOTENTIAL_H

