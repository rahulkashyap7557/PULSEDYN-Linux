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
#include "Output.h"
#include "force.h"

using namespace std;


class Simulation : public System
{
    public:
        /** Default constructor */
        Simulation();
        /** Default destructor */
        virtual ~Simulation();
        /** Copy constructor
         *  \param other Object to copy from
         */
        Simulation(const Simulation& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        Simulation& operator=(const Simulation& other);

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
        void f_velocityVerlet(std::vector<Particle> &chainParticles, std::vector<PotType> &chainPotential, std::vector<Force> &force);

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
        int systemSize;
        string method;
};
// start simulation

template <class PotType>
void Simulation::f_startSim(std::vector<Particle> &chainParticles, std::vector<PotType> &chainPotential, std::vector<Force> &force)//, Potential &chainPotential[])
{

    if (method == "gear5")
    {
        f_gear5(chainParticles, chainPotential, force);
    }
    else if (method == "velocityverlet")
    {
        f_velocityVerlet(chainParticles, chainPotential, force);
    }
}

// Gear solver
template <class PotType>
void Simulation::f_gear5(std::vector<Particle> &chainParticles, std::vector<PotType> &chainPotential, std::vector<Force> &force)//, Potential &chainPotential[])
{


    cout << "Gear 5th order" << endl;
    int n = 1; // Counter for total time
    int n1 = 1; // Counter for data write times

    double accelerationPredict[systemSize]; // This is the acceleration calculated by the Predictor step of the Gear algorithm
    double deltaR[systemSize]; // This is the quantity used by the corrector algorithm to adjust accelerationPredict to follow energy conservation
    double c1 = timeStep*timeStep/2.0; // One of the 5 coefficients used by Predictor step of the algorithm.


    int i;
    int j;
    int k;

    // Initialize variables needed for the Gear 5th order algorithm

    // These three are higher order terms used to evolve position, velocity and acceleration
    // in the Gear algorithm.

    double position3[systemSize];
    double position4[systemSize];
    double position5[systemSize];

    // Temporary variables used to update the position, velocity and acceleration variables

    double positionTemp[systemSize];
    double velocityTemp[systemSize];
    double accelerationTemp[systemSize];

    // Initialize variables for energies to be calculated and written to file
    double totalEnergy = 0.;
    double totalKineticEnergy = 0.;
    double totalPotentialEnergy = 0.;


    // Initialize counter variable to decide when to write to file

    int counter;

    // Initialize temporary variables

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
     totalPotentialEnergy = chainPotential[0].f_calcPe(chainParticles);

     totalEnergy = totalKineticEnergy + totalPotentialEnergy; // calculate total energy

     Output::writeToTotFile(totalEnergy, true);

     // Set up solver variables

    /* The same coefficients as the Predictor step. They are used here as well */
     double c[5];
     c[0] = timeStep;
     c[1] = c[0]*timeStep/2.;
     c[2] = c[1]*timeStep/3.;
     c[3] = c[2]*timeStep/4.;
     c[4] = c[3]*timeStep/5.;

     /* Initialize coefficients for the Corrector step to adjust the position, velocity and acceleration variables according to Corrector step */

     double a[6];
     a[0] = 3./20;
     a[1] = 251./360;
     a[2] = 1.;
     a[3] = 11./18;
     a[4] = 1./6;
     a[5] = 1./60;

     // Initialize force term

     double force_i;

     // Initialize time

     double tCurrent = 0.;



     // Now start simulation loop

     while (n < totalTime)
      {
//          tCurrent = static_cast<double> (n + n1*timeStep);
         // Run predictor step for gear 5th order algorithm
         for (i = 0; i < systemSize; i++)
          {



             positionTemp[i] += c[0]*chainParticles.at(i).Getvelocity() + c[1]*chainParticles.at(i).Getaccel() + c[2]*position3[i] + c[3]*position4[i] + c[4]*position5[i];

             velocityTemp[i] += c[0]*chainParticles.at(i).Getaccel() + c[1]*position3[i] + c[2]*position4[i] + c[3]*position5[i];
             accelerationTemp[i] += c[0]*position3[i] + c[1]*position4[i] + c[2]*position5[i];
             position3[i] += c[0]*position4[i] + c[1]*position5[i];
             position4[i] += c[0]*position5[i];
             position5[i] += 0.;
             accelerationPredict[i] = accelerationTemp[i];

             chainParticles.at(i).Setposition(positionTemp[i]);
             chainParticles.at(i).Setvelocity(velocityTemp[i]);
             chainParticles.at(i).Setaccel(accelerationTemp[i]);

          }

         // Calculate accelerations

         chainPotential[0].f_accel(chainParticles);


         // Run corrector step for gear 5th order algorithm
        for (i = 0; i < systemSize; i++)
         {
             force_i = 0.;
         /* Using the equations of the system, Corrector step will correct position, velocity and acceleration so the energy is conserved */
         accelerationPredict[i] = chainParticles.at(i).Getaccel();



             if (tCurrent > force.at(i).Gett1() && tCurrent < force.at(i).Gett3())
             {
                 force_i = force.at(i).f_forceCalc(chainParticles, tCurrent);
             }


             accelerationPredict[i] = accelerationPredict[i] + force_i - chainParticles.at(i).Getvelocity() * force.at(i).Getgamma();

         deltaR[i] = c1 * (accelerationPredict[i] - accelerationTemp[i]);

         }

        for (i = 0; i < systemSize; i++)
         {
            positionTemp[i] += a[0]*deltaR[i];
            velocityTemp[i] += a[1]*deltaR[i]/c[0];
            accelerationTemp[i] += a[2]*deltaR[i]/c[1];
            position3[i] += a[3]*deltaR[i]/c[2];
            position4[i] += a[4]*deltaR[i]/c[3];
            position5[i] += a[5]*deltaR[i]/c[4];
            chainParticles.at(i).Setposition(positionTemp[i]);
            chainParticles.at(i).Setvelocity(velocityTemp[i]);
            chainParticles.at(i).Setaccel(accelerationTemp[i]);
         }

         counter = n1/samplingFrequency;

         if (counter == 1)
         {

             printf("complete: %3f%%\n", n*100./totalTime);
             totalKineticEnergy = 0;
             totalPotentialEnergy = 0;
             totalEnergy = 0;

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
void Simulation::f_velocityVerlet(std::vector<Particle> &chainParticles, std::vector<PotType> &chainPotential, std::vector<Force> &force)
{

    cout << "Velocity Verlet" << endl;

    double k1 = chainPotential.at(0).Getk1();
    double k2 = chainPotential.at(0).Getk2();


    int n = 1; // Counter for total time
    int n1 = 1; // Counter for data write times

    double accelerationPredict[systemSize]; // This is the acceleration calculated by the Predictor step of the Gear algorithm
    double deltaR[systemSize]; // This is the quantity used by the corrector algorithm to adjust accelerationPredict to follow energy conservation
    double c1 = timeStep*timeStep/2.0; // One of the 5 coefficients used by Predictor step of the algorithm.

    int i;
    int j;
    int k;

    // Initialize variables needed for the velocity Verlet algorithm

    double dx; // difference between displacement of adjact particles i.e. bond stretch or extension. x[k + 1] - x[k].

    // Temporary variables used to update the position, velocity and acceleration variables

    double positionTemp[systemSize];
    double velocityTemp[systemSize];
    double accelerationTemp[systemSize];

    // Initialize variables for energies to be calculated and written to file

    double potentialEnergy;
    double totalEnergy = 0.;
    double totalKineticEnergy = 0.;
    double totalPotentialEnergy = 0.;
    double fac;

    // Initialize counter variable to decide when to write to file

    int counter;

    // Initialize temporary variables

    for (i = 0; i < systemSize; i++)
       {
           positionTemp[i] = chainParticles.at(i).Getposition();
           velocityTemp[i] = chainParticles.at(i).Getvelocity();
           accelerationTemp[i] = chainParticles.at(i).Getaccel();
       }

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

     totalPotentialEnergy = chainPotential[0].f_calcPe(chainParticles);
     totalEnergy = totalKineticEnergy + totalPotentialEnergy; // calculate total energu

     Output::writeToTotFile(totalEnergy, true);

     // Now start simulation loop

     while (n < totalTime)
      {

          // Positions and half-way velocities calculated first

         for (i = 0; i < systemSize; i++)
          {
             positionTemp[i] += timeStep*chainParticles.at(i).Getvelocity() + 0.5*timeStep*timeStep*chainParticles.at(i).Getaccel();
             velocityTemp[i] += 0.5*timeStep*chainParticles.at(i).Getaccel();

             chainParticles.at(i).Setposition(positionTemp[i]);
             chainParticles.at(i).Setvelocity(velocityTemp[i]);
          }

         // Calculate accelerations

         chainPotential.at(0).f_accel(chainParticles);

         // Calculate full step velocity


        for (i = 0; i < systemSize; i++)
         {
            velocityTemp[i] += 0.5*timeStep*chainParticles.at(i).Getaccel();

            chainParticles.at(i).Setvelocity(velocityTemp[i]);
         }

         counter = n1/samplingFrequency;

         if (counter == 1)
         {

             printf("complete: %3f%%\n", n*100./totalTime);
             totalKineticEnergy = 0;
             totalPotentialEnergy = 0;
             totalEnergy = 0;

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
         if (samplingFrequency > 1){
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
