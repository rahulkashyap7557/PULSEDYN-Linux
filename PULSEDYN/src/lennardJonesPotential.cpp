/*
    Copyright (c) Rahul Kashyap 2017

    This file is part of Nonlin.

    Nonlin is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    Nonlin is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Nonlin.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "../include/allIncludes.h"

lennardJonesPotential::lennardJonesPotential()
{
    //ctor
    k1 = 0.0;
    k2 = 1.0;

}

lennardJonesPotential::lennardJonesPotential(Particle chainParticles)
{
    //ctor


}

lennardJonesPotential::~lennardJonesPotential()
{
    //dtor
}

lennardJonesPotential::lennardJonesPotential(const lennardJonesPotential& other)
{
    //copy ctor
    k1 = other.k1;
    k2 = other.k2;
}

lennardJonesPotential& lennardJonesPotential::operator=(const lennardJonesPotential& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    k1 = rhs.k1;
    k2 = rhs.k2;

    return *this;
}

void lennardJonesPotential::f_accel(std::vector<Particle> &chainParticles)
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
		double k1p = pow(k1, 6);
		double Dfac1 = fac1 + k1;
		double Dfac2 = k1 - fac2;

		double term1 = pow(Dfac1, -7) - k1p*pow(Dfac1, -13);
		double term2 = pow(Dfac2, -7) - k1p*pow(Dfac2, -13);
		a = term2 - term1;
		a = 12.0*k2*k1p*a;
		a = a/mass;
		chainParticles[i].Setaccel(a);

	}

}

double lennardJonesPotential::f_calcPe(std::vector<Particle> &chainParticles)
{
     int i;
     int j;
     double dx;
     double term1;
     double term2;
     double lastSpring;
     double potentialEnergy;
     double totalPotentialEnergy = 0.;
     int systemSize = chainParticles.size();
     for (int i = 0; i < systemSize; i++)
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
          term1 = pow(k1, 12) * pow(k1 + dx, -12);
          term2 = 2.*pow(k1, 6) * pow(k1 + dx, -6);

          potentialEnergy = k2*(term1 - term2 + 1.); // calculates and records potential energy at t = 0
          Output::writeToPeFile(potentialEnergy, false);
          totalPotentialEnergy +=  potentialEnergy;

     }
     lastSpring = f_rightBoundaryConditionsPe(chainParticles);
     term1 = pow(k1, 12) * pow(k1 - lastSpring, -12);
     term2 = 2.*pow(k1, 6) * pow(k1 - lastSpring, -6);

     potentialEnergy = k2*(term1 - term2 + 1.);
     totalPotentialEnergy += potentialEnergy;
     Output::writeToPeFile(potentialEnergy, true);
     return totalPotentialEnergy;

}




