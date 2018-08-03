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
#include "../include/allIncludes.h"

morsePotential::morsePotential()
{
    //ctor
    k1 = 0.0;
    k2 = 1.0;

}

morsePotential::morsePotential(Particle chainParticles)
{
    //ctor


}

morsePotential::~morsePotential()
{
    //dtor
}

morsePotential::morsePotential(const morsePotential& other)
{
    //copy ctor
    k1 = other.k1;
    k2 = other.k2;
}

morsePotential& morsePotential::operator=(const morsePotential& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    k1 = rhs.k1;
    k2 = rhs.k2;

    return *this;
}

void morsePotential::f_accel(std::vector<Particle> &chainParticles)
{
    double fac1;
    double fac2;
    double mass;
    double a = 0.;

	unsigned int i, k;
	int j;


        for (i = 0; i < chainParticles.size(); i++) {
		j = i - 1;
		k = i + 1;
		if (j == -1) {

			fac1 = f_leftBoundaryConditionsAccel(chainParticles);
		} else {
			fac1 = chainParticles.at(i).Getposition() - chainParticles.at(j).Getposition();
		}

		if (k == chainParticles.size()) {

			fac2 = f_rightBoundaryConditionsAccel(chainParticles);
		} else {
			fac2 = chainParticles.at(i).Getposition() - chainParticles.at(k).Getposition();
		}

		mass = chainParticles.at(i).Getmass();
		a = 2.*k2*k1*(exp(k2*fac2) - exp(2.*k2*fac2) + exp(-2.*k2*fac1) - exp(-k2*fac1));
		a = a/mass;

		chainParticles[i].Setaccel(a);

	}

}

double morsePotential::f_calcPe(std::vector<Particle> &chainParticles)
{
     int i;
     int j;
     double dx;
     double lastSpring;
     double potentialEnergy;
     double totalPotentialEnergy = 0.;
     int systemSize = chainParticles.size();
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

          potentialEnergy = k1*(exp(-k2*dx) - 1)*(exp(-k2*dx) - 1); // calculates and records potential energy at t = 0
          Output::writeToPeFile(potentialEnergy, false);
          totalPotentialEnergy +=  potentialEnergy;

     }
     lastSpring = f_rightBoundaryConditionsPe(chainParticles);
     potentialEnergy = k1*(exp(-k2*(-lastSpring)) - 1)*(exp(-k2*(-lastSpring)) - 1);
     totalPotentialEnergy += potentialEnergy;
     Output::writeToPeFile(potentialEnergy, true);
     return totalPotentialEnergy;

}



