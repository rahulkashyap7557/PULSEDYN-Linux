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

#ifndef LENNARDJONESPOTENTIAL_H
#define LENNARDJONESPOTENTIAL_H
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

class lennardJonesPotential
{
    public:
        /** Default constructor */
        lennardJonesPotential();
        lennardJonesPotential(Particle chainParticles);

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
			double a;
			
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
				
				double k1p;
                k1p = pow(k1, 6);
				
				double Dfac1, Dfac2;
                Dfac1 = fac1 + k1;
                Dfac2 = k1 - fac2;
				double term1;
                term1 = pow(Dfac1, -7) - k1p*pow(Dfac1, -13);
				double term2;
                term2 = pow(Dfac2, -7) - k1p*pow(Dfac2, -13);
				
                a = 0.;
                a = term2 - term1;
                a = 12.0*k2*k1p*a;
                a = a/mass;
                chainParticles[i].Setaccel(a);
            }
        }

        double f_calcPe(std::vector<Particle> &chainParticles)
        {
             int j;
             double dx;
             unsigned int systemSize = chainParticles.size();
             double potentialEnergy;
             double totalPotentialEnergy = 0.;
             

             unsigned int i;

             for (i = 0; i < systemSize; i++)
             {

                 j = i - 1;
                  if (j == -1)
                  {
                      dx = f_leftBoundaryConditionsPe(chainParticles);;
                  }
                  else
                  {
                      dx = chainParticles.at(i).Getposition() - chainParticles.at(j).Getposition();
                  }
				  
				  double term1, term2;
                  term1 = pow(k1, 12) * pow(k1 + dx, -12);
                  term2 = 2.*pow(k1, 6) * pow(k1 + dx, -6);

                  potentialEnergy = k2*(term1 - term2 + 1.); // calculates and records potential energy at t = 0
                  Output::writeToPeFile(potentialEnergy, false);
                  totalPotentialEnergy +=  potentialEnergy;
             }

             double lastSpring;
             lastSpring = f_rightBoundaryConditionsPe(chainParticles);
			 
			 double term1, term2;
             term1 = pow(k1, 12) * pow(k1 - lastSpring, -12);
             term2 = 2.*pow(k1, 6) * pow(k1 - lastSpring, -6);

             potentialEnergy = k2*(term1 - term2 + 1.);
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

#endif // LENNARDJONESPOTENTIAL_H


