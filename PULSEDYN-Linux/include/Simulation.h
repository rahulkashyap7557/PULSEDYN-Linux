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

#ifndef SIMULATION_H
#define SIMULATION_H
//#include "allIncludes.h"
#include "Particle.h"
#include "fpuPotential.h"
#include "todaPotential.h"
#include "morsePotential.h"
#include "lennardJonesPotential.h"
#include "Output.h"
#include "force.h"

using namespace std;


class Simulation
{
public:
    /** Default constructor */
    Simulation();

    /** Access timeStep
         * \return The current value of timeStep
         */
    double GettimeStep() { return timeStep; }
    /** Set timeStep
         * \param val New value to set
         */
    void SettimeStep(double val) { timeStep = val; }
    /** Access samplingFrequency
         * \return The current value of samplingFrequency
         */
    int GetsamplingFrequency() { return samplingFrequency; }
    /** Set samplingFrequency
         * \param val New value to set
         */
    void SetsamplingFrequency(int val) { samplingFrequency = val; }
    /** Access totalTime
         * \return The current value of totalTime
         */
    int GettotalTime() { return totalTime; }
    /** Set totalTime
         * \param val New value to set
         */
    void SettotalTime(int val) { totalTime = val; }

    string Getmethod(){return method; }

    void Setmethod(string val);

    int GetsystemSize(){return systemSize; }

    void SetsystemSize(int val);

    template <class PotType>
    void f_velocityVerlet(std::vector<Particle> &chainParticles, std::vector<PotType> &chainPotential);

    template <class PotType>
    void f_gear5(std::vector<Particle> &chainParticles, std::vector<PotType> &chainPotential, std::vector<Force> &force);//, Potential &chainPotential[])


    void f_rk4();
    void f_rk4Adaptive();

    template <class PotType>
    void f_startSim(std::vector<Particle> &chainParticles, std::vector<PotType> &chainPotential, std::vector<Force> &force);

protected:

private:
    double timeStep; //!< Member variable "timeStep"
    int samplingFrequency; //!< Member variable "samplingFrequency"
    int totalTime; //!< Member variable "totalTime"
    unsigned int systemSize;
    string method;
};


template <class PotType>
void Simulation::f_startSim(std::vector<Particle> &chainParticles, std::vector<PotType> &chainPotential, std::vector<Force> &force)//, Potential &chainPotential[])
{
    if (method == "gear5")
    {
        f_gear5(chainParticles, chainPotential, force);
    }
    else if (method == "velocityverlet")
    {
        f_velocityVerlet(chainParticles, chainPotential);
    }
}


// Gear solver
template <class PotType>
void Simulation::f_gear5(std::vector<Particle> &chainParticles, std::vector<PotType> &chainPotential, std::vector<Force> &force)//, Potential &chainPotential[])
{
    cout << "Gear 5th order" << endl;

    // Initialize variables needed for the Gear 5th order algorithm

    // These three are higher order terms used to evolve position, velocity and acceleration
    // in the Gear algorithm.
    double position3[systemSize] __attribute__ ((aligned));
    double position4[systemSize] __attribute__ ((aligned));
    double position5[systemSize];
    double accelerationPredict[systemSize] __attribute__ ((aligned)); // This is the acceleration calculated by the Predictor step of the Gear algorithm
    double deltaR[systemSize] __attribute__ ((aligned)); // This is the quantity used by the corrector algorithm to adjust accelerationPredict to follow energy conservation

    // Temporary variables used to update the position, velocity and acceleration variables
    double positionTemp[systemSize] __attribute__ ((aligned));
    double velocityTemp[systemSize] __attribute__ ((aligned));
    double accelerationTemp[systemSize] __attribute__ ((aligned));

    // Initialize temporary variables
    unsigned int i;

    for (i = 0; i < systemSize; i++)
    {
        accelerationPredict[i] = 0.;
        deltaR[i] = 0.;
        positionTemp[i] = chainParticles.at(i).Getposition();
        velocityTemp[i] = chainParticles.at(i).Getvelocity();
        accelerationTemp[i] = chainParticles.at(i).Getaccel();
        position3[i] = 0.;
        position4[i] = 0.;
        position5[i] = 0.;
    }
    // Initialize KE variable to be calculated and written to file
    double totalKineticEnergy = 0.;

    // Write initial data (at t = 0) to file
    for (i = 0; i < systemSize; i++)
    {
        chainParticles.at(i).f_calcKe();
        if (i != systemSize - 1)
        {
            Output::writeToPosFile(chainParticles.at(i).Getposition(), false); // Writes to position file
            Output::writeToVelFile(chainParticles.at(i).Getvelocity(), false); // Writes to velocity file
            Output::writeToAccFile(chainParticles.at(i).Getaccel(), false); // Writes to acceleration file
            Output::writeToMassFile(chainParticles.at(i).Getmass(), false); // Writes to masses file
            Output::writeToKeFile(chainParticles.at(i).Getke(), false); // Writes to KE file
        }
        else
        {
            Output::writeToPosFile(chainParticles.at(i).Getposition(), true); // Next few write steps are for last entry and then add an endline
            Output::writeToVelFile(chainParticles.at(i).Getvelocity(), true);
            Output::writeToAccFile(chainParticles.at(i).Getaccel(), true);
            Output::writeToMassFile(chainParticles.at(i).Getmass(), true);
            Output::writeToKeFile(chainParticles.at(i).Getke(), true);
        }

        totalKineticEnergy += chainParticles.at(i).Getke();
    }

    // Calculate potential and total energy of the chain

    double totalPotentialEnergy = 0.;
    totalPotentialEnergy = chainPotential[0].f_calcPe(chainParticles);

    double totalEnergy = 0.;
    totalEnergy = totalKineticEnergy + totalPotentialEnergy; // calculate total energy

    Output::writeToTotFile(totalEnergy, true);

    // Set up solver variables

    // The same coefficients as the Predictor step. They are used here as well
    // Initialized here so that they are not reinitialized repeatedly inside time loop
    double c[5];
    c[0] = timeStep;
    c[1] = c[0]*timeStep/2.;
    c[2] = c[1]*timeStep/3.;
    c[3] = c[2]*timeStep/4.;
    c[4] = c[3]*timeStep/5.;

    // Calculate the inverses of c[i] to use later as multiplication rather than dividing to increase speed.
    // Initialized here so that they are not reinitialized repeatedly inside time loop
    double cInverse[5];
    cInverse[0] = 1/timeStep;
    cInverse[1] = 1/c[1];
    cInverse[2] = 1/c[2];
    cInverse[3] = 1/c[3];
    cInverse[4] = 1/c[4];

    // Initialize coefficients for the Corrector step to adjust the position, velocity and acceleration variables according to Corrector step
    // Initialized here so that they are not reinitialized repeatedly inside time loop
    double a[6];
    a[0] = 3./20;
    a[1] = 251./360;
    a[2] = 1.;
    a[3] = 11./18;
    a[4] = 1./6;
    a[5] = 1./60;

    double tCurrent = 0.;

    // Now start simulation loop
    int n = 1; // Counter for total time
    int n1 = 1; // Counter for data write times

    while (n < totalTime)
    {
        // Calculate dynamical variables
        for (i = 0; i < systemSize; i++)
        {
            positionTemp[i] += c[0]*velocityTemp[i] + c[1]*accelerationTemp[i] + c[2]*position3[i] + c[3]*position4[i] + c[4]*position5[i];
            velocityTemp[i] += c[0]*accelerationTemp[i] + c[1]*position3[i] + c[2]*position4[i] + c[3]*position5[i];
            accelerationTemp[i] += c[0]*position3[i] + c[1]*position4[i] + c[2]*position5[i];
            position3[i] = position3[i] + c[0]*position4[i] + c[1]*position5[i];
            position4[i] = position4[i] + c[0]*position5[i];
            position5[i] += 0.;
            accelerationPredict[i] = accelerationTemp[i];
        }

        // Set variables back in object
        for (i = 0; i < systemSize; i++)
        {
            chainParticles.at(i).Setposition(positionTemp[i]);
            chainParticles.at(i).Setvelocity(velocityTemp[i]);
            chainParticles.at(i).Setaccel(accelerationTemp[i]);
        }

        // Calculate accelerations for corrector step
        chainPotential[0].f_accel(chainParticles);

        // Calculate external driving force

        // Do something about the force loop here---------------------------------------------------------------------------------------------

        for (i = 0; i < systemSize; i++)
        {
            double force_i = 0.;
            accelerationPredict[i] = chainParticles.at(i).Getaccel();

            // Calculate external force on each particle and add to the force from the springs
            if (tCurrent > force.at(i).Gett1() && tCurrent < force.at(i).Gett3())
            {
                force_i = force.at(i).f_forceCalc(tCurrent);
            }
            accelerationPredict[i] = accelerationPredict[i] + force_i - chainParticles.at(i).Getvelocity() * force.at(i).Getgamma();
            double c1 = timeStep*timeStep/2.0; // One of the 5 coefficients used by Predictor step of the algorithm.
            deltaR[i] = c1 * (accelerationPredict[i] - accelerationTemp[i]);
        }

        // Run corrector steps using information about calculated acceleration
        for (i = 0; i < systemSize; i++)
        {
            positionTemp[i] += a[0]*deltaR[i];
            velocityTemp[i] += a[1]*deltaR[i]*cInverse[0];
            accelerationTemp[i] += a[2]*deltaR[i]*cInverse[1];
            position3[i] += a[3]*deltaR[i]*cInverse[2];
            position4[i] += a[4]*deltaR[i]*cInverse[3];
            position5[i] += a[5]*deltaR[i]*cInverse[4];
        }

        // Again set values of dynamical variables
        for (i =0; i < systemSize; i++)
        {
            chainParticles.at(i).Setposition(positionTemp[i]);
            chainParticles.at(i).Setvelocity(velocityTemp[i]);
            chainParticles.at(i).Setaccel(accelerationTemp[i]);
        }

        int counter = n1/samplingFrequency; // variable to decide when to write to file

        if (counter == 1)
        {
            printf("complete: %3f%%\n", n*100./totalTime);
            totalKineticEnergy = 0.;
            totalPotentialEnergy = 0.;
            totalEnergy = 0.;

            for (i = 0; i < systemSize; i++)
            {
                chainParticles.at(i).f_calcKe();
                if (i != systemSize - 1)
                {
                    Output::writeToPosFile(chainParticles.at(i).Getposition(), false); // Writes to position file
                    Output::writeToVelFile(chainParticles.at(i).Getvelocity(), false); // Writes to velocity file
                    Output::writeToAccFile(chainParticles.at(i).Getaccel(), false); // Writes to acceleration file
                    Output::writeToMassFile(chainParticles.at(i).Getmass(), false); // Writes to masses file
                    Output::writeToKeFile(chainParticles.at(i).Getke(), false); // Writes to KE file
                }
                else
                {
                    Output::writeToPosFile(chainParticles.at(i).Getposition(), true); // Next few write steps are for last entry and then add an endline
                    Output::writeToVelFile(chainParticles.at(i).Getvelocity(), true);
                    Output::writeToAccFile(chainParticles.at(i).Getaccel(), true);
                    Output::writeToMassFile(chainParticles.at(i).Getmass(), true);
                    Output::writeToKeFile(chainParticles.at(i).Getke(), true);
                }

                totalKineticEnergy += chainParticles.at(i).Getke();
            }

            totalPotentialEnergy = chainPotential[0].f_calcPe(chainParticles);
            totalEnergy = totalKineticEnergy + totalPotentialEnergy; // calculate total energu

            Output::writeToTotFile(totalEnergy, true);

            // n is the counter for recorded steps, n1 is the counter to check when to write

            n++;
            n1 = 1;
        }
        if (samplingFrequency > 1)
        {
            n1++;
        }
        tCurrent += timeStep;
    }

    // After the simulation is done, write restart step

    for (i = 0; i < systemSize; i++)
    {
        Output::writeToResFile(chainParticles.at(i).Getposition(), false);
        Output::writeToResFile(chainParticles.at(i).Getvelocity(), false);
        Output::writeToResFile(chainParticles.at(i).Getaccel(), true);
    }

}

template <class PotType>
void Simulation::f_velocityVerlet(std::vector<Particle> &chainParticles, std::vector<PotType> &chainPotential)
{
    cout << "Velocity Verlet" << endl;

    // Initialize variables needed for the velocity Verlet algorithm

    // Temporary variables used to update the position, velocity and acceleration variables

    double positionTemp[systemSize] __attribute__ ((aligned));
    double velocityTemp[systemSize] __attribute__ ((aligned));
    double accelTemp[systemSize] __attribute__ ((aligned));

    // Initialize temporary variables
    unsigned int i;

    for (i = 0; i < systemSize; i++)
    {
        positionTemp[i] = chainParticles.at(i).Getposition();
        velocityTemp[i] = chainParticles.at(i).Getvelocity();
        accelTemp[i] = chainParticles.at(i).Getaccel();
    }

    // Initialize variables for energies to be calculated and written to file

    double totalKineticEnergy = 0.;

    // Write initial data (at t = 0) to file

    for (i = 0; i < systemSize; i++)
    {
        chainParticles.at(i).f_calcKe();
        if (i != systemSize - 1)
        {
            Output::writeToPosFile(chainParticles.at(i).Getposition(), false); // Writes to position file
            Output::writeToVelFile(chainParticles.at(i).Getvelocity(), false); // Writes to velocity file
            Output::writeToAccFile(chainParticles.at(i).Getaccel(), false); // Writes to acceleration file
            Output::writeToMassFile(chainParticles.at(i).Getmass(), false); // Writes to masses file
            Output::writeToKeFile(chainParticles.at(i).Getke(), false); // Writes to KE file
        }
        else
        {
            Output::writeToPosFile(chainParticles.at(i).Getposition(), true); // Next few write steps are for last entry and then add an endline
            Output::writeToVelFile(chainParticles.at(i).Getvelocity(), true);
            Output::writeToAccFile(chainParticles.at(i).Getaccel(), true);
            Output::writeToMassFile(chainParticles.at(i).Getmass(), true);
            Output::writeToKeFile(chainParticles.at(i).Getke(), true);
        }
        totalKineticEnergy += chainParticles.at(i).Getke();
    }

    double totalPotentialEnergy = 0.;
    totalPotentialEnergy = chainPotential[0].f_calcPe(chainParticles);

    double totalEnergy = 0.;
    totalEnergy = totalKineticEnergy + totalPotentialEnergy; // calculate total energu

    Output::writeToTotFile(totalEnergy, true);

    // Initialize counter variables to decide when to write to file

    int counter;
    int n = 1; // Counter for total time
    int n1 = 1; // Counter for data write times

    // Now start simulation loop
    while (n < totalTime)
    {
        // Positions and half-way velocities calculated first
        for (i = 0; i < systemSize; i++)
        {
            positionTemp[i] += timeStep*velocityTemp[i] + 0.5*timeStep*timeStep*accelTemp[i];
            velocityTemp[i] += 0.5*timeStep*accelTemp[i];
        }
        for (i = 0; i < systemSize; i++)
        {
            chainParticles.at(i).Setposition(positionTemp[i]);
            chainParticles.at(i).Setvelocity(velocityTemp[i]);
        }

        // Calculate accelerations
        chainPotential.at(0).f_accel(chainParticles);

        for (i = 0; i < systemSize; i++)
        {
            accelTemp[i] = chainParticles.at(i).Getaccel();
        }

        // Calculate full step velocity
        for (i = 0; i < systemSize; i++)
        {
            velocityTemp[i] += 0.5*timeStep*accelTemp[i];
        }

        for (i = 0; i < systemSize; i++)
        {
            chainParticles.at(i).Setvelocity(velocityTemp[i]);
        }

        counter = n1/samplingFrequency;

        if (counter == 1)
        {
            printf("complete: %3f%%\n", n*100./totalTime);
            totalKineticEnergy = 0.;
            totalPotentialEnergy = 0.;
            totalEnergy = 0.;

            for (i = 0; i < systemSize; i++)
            {
                chainParticles.at(i).f_calcKe();
                if (i != systemSize - 1)
                {
                    Output::writeToPosFile(chainParticles.at(i).Getposition(), false); // Writes to position file
                    Output::writeToVelFile(chainParticles.at(i).Getvelocity(), false); // Writes to velocity file
                    Output::writeToAccFile(chainParticles.at(i).Getaccel(), false); // Writes to acceleration file
                    Output::writeToMassFile(chainParticles.at(i).Getmass(), false); // Writes to masses file
                    Output::writeToKeFile(chainParticles.at(i).Getke(), false); // Writes to KE file
                }
                else
                {
                    Output::writeToPosFile(chainParticles.at(i).Getposition(), true); // Next few write steps are for last entry and then add an endline
                    Output::writeToVelFile(chainParticles.at(i).Getvelocity(), true);
                    Output::writeToAccFile(chainParticles.at(i).Getaccel(), true);
                    Output::writeToMassFile(chainParticles.at(i).Getmass(), true);
                    Output::writeToKeFile(chainParticles.at(i).Getke(), true);
                }

                totalKineticEnergy += chainParticles.at(i).Getke();
            }

            totalPotentialEnergy = chainPotential[0].f_calcPe(chainParticles);
            totalEnergy = totalKineticEnergy + totalPotentialEnergy; // calculate total energu

            Output::writeToTotFile(totalEnergy, true);

            // n is the counter for recorded steps, n1 is the counter to check when to write

            n++;
            n1 = 1;

        }
        if (samplingFrequency > 1)
        {
            n1++;
        }
    }

    // After the simulation is done, write restart step
    for (i = 0; i < systemSize; i++)
    {
        Output::writeToResFile(chainParticles.at(i).Getposition(), false);
        Output::writeToResFile(chainParticles.at(i).Getvelocity(), false);
        Output::writeToResFile(chainParticles.at(i).Getaccel(), true);
    }

}

#endif // SIMULATION_H
