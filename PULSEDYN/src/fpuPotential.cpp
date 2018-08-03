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

fpuPotential::fpuPotential()
{
    //ctor
    k1 = 0.0;
    k2 = 0.0;
    k3 = 1.0;

}

fpuPotential::fpuPotential(Particle chainParticles)
{
    //ctor


}

fpuPotential::~fpuPotential()
{
    //dtor
}

fpuPotential::fpuPotential(const fpuPotential& other)
{
    //copy ctor
    k1 = other.k1;
    k2 = other.k2;
    k3 = other.k3;
}

fpuPotential& fpuPotential::operator=(const fpuPotential& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    k1 = rhs.k1;
    k2 = rhs.k2;
    k3 = rhs.k3;

    return *this;
}

void fpuPotential::f_accel(std::vector<Particle> &chainParticles)
{
    double fac;
    double fac1;
    double fac2;
    double fac12;
    double fac22;
    double fac23;
    double fac13;
    double mass;
    double a = 0.0;
    int N = chainParticles.size() - 1;
    double dxi, twodxi, dxipl1, dximn1, chainlength;
    string lb, rb;
    chainlength = chainParticles.size();

    lb = chainParticles.at(0).Getlboundary();
    rb = chainParticles.at(N).Getrboundary();


	unsigned int i, k;
	int j;


		for (i = 0; i < chainParticles.size(); i++) {
		j = i - 1;
		k = i + 1;
		a = 0.;
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
		fac12 = fac1*fac1;
		fac22 = fac2*fac2;
		fac13 = fac1*fac1*fac1;
		fac23 = fac2*fac2*fac2;
		a = -2.0*k1*(fac1 + fac2) + 3.0*k2*(-fac12 + fac22) - 4.0*k3*(fac13 + fac23);
		a = a/mass;
		chainParticles[i].Setaccel(a);

	}

}

double fpuPotential::f_calcPe(std::vector<Particle> &chainParticles)
{
     int i;
     int j;
     double dx;
     double fac;
     double lastSpring;
     double potentialEnergy;
     double totalPotentialEnergy = 0.;
     int systemSize = chainParticles.size();
     for (int i = 0; i < systemSize; i++)
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
     lastSpring = f_rightBoundaryConditionsPe(chainParticles);
     // Technically, it should be k1*(-lastSpring)*(-lastSpring) etc...,
     // But the even powers take care of the negative signs. For other potentials, this makes a difference.
     potentialEnergy = k1*lastSpring*lastSpring - k2*(lastSpring)*(lastSpring)*(lastSpring) + k3*lastSpring*lastSpring*lastSpring*lastSpring;
     totalPotentialEnergy += potentialEnergy;
     Output::writeToPeFile(potentialEnergy, true);
     return totalPotentialEnergy;

}



