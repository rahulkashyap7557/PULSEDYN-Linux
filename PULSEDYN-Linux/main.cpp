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

//#include "include/Simulation.h"
//#include "include/System.h"
//#include "include/Particle.h"
#include "include/allIncludes.h"
//#include "include/fpuPotential.h"
using namespace std;

int main()
{
    // Set up a timer to start a clock and estimate running times

    // Record start time
    auto start = std::chrono::high_resolution_clock::now();

    // Initialize the default Simulation object variables
    unsigned int systemSize = 100;
    double dt = 0.01;
    int samplingFrequency = 1/dt;
    double pi = 3.14159;
    int totalTime = 100;
    std::string method = "gear5";

    // Initialize model parameters - default FPUT model
    double k1 = 0.2;
    double k2 = 0.0;
    double k3 = 1.0;
    //    double k4 = 0.0;
    //    double k5 = 0.0;

    std::vector<double> mass;
    double defaultMass = 1.0;
    string springType = "fput";

    // Initialize boundary conditions
    string lboundary = "periodic";
    string rboundary = "periodic";

    // Initialize force initialization containers
    std::vector<string> forceType;// = "cosine";
    std::vector<double> forceT1;
    std::vector<double> forceT2;
    std::vector<double> forceT3;
    std::vector<double> forceRamp;
    std::vector<double> forceAmp;
    std::vector<unsigned int> forceParticles;
    std::vector<double> forceGamma;
    std::vector<double> forceFrequency;
    std::vector<unsigned int> dissipationParticles;
    std::vector<double> dissipationStrength;

    std::vector<unsigned int> perturbedParticles;
    std::vector<string> perturbationType;
    std::vector<double> perturbationAmplitude;
    std::vector<unsigned int> impurityParticles;
    std::vector<double> impurityValue;

    int fileFlag = 0;
    int sampleFlag = 0;

    string line, line1;
    unsigned int j = 0;
    unsigned int i;

    std::ifstream parametersFile("parameters.txt");
    std::ofstream logFile("log.txt");

    if (!parametersFile)
    {
        // Turn off commenting below if you want to stop code from running without parameter file.
        //throw std::runtime_error("Can't open parameters file. Running with default values.");
        logFile << "Can't open parameters file. Running with default values" << endl;
    }
    else
    {
        while (getline(parametersFile, line))
        {
            if (line == "")
            {
                cout << "Skipping blank line." << endl;
                logFile << "line "<< j+1 << ":"<<"Skipping blank line." << endl;
                continue;
            }
            else
            {
                cout << "Reading from parameter file" << endl;
                logFile << "line "<< j+1 << ":" <<"Reading from parameter file" << endl;
                logFile << line << endl;
                std::vector<std::string> inputList;

                stringstream ss(line);
                string tmp;
                while(std::getline(ss, tmp, ' '))
                {
                    auto tmp1 = std::regex_replace(tmp,std::regex("\\s+"), "");
                    inputList.push_back(tmp1);
                }
                string a = inputList.at(0);
                string b;
                //             string b = inputList.at(1);
                string c;
                string d;
                string e;
                string f;
                string g;
                string h;
                if (inputList.size() > 1)
                {
                    b = inputList.at(1);
                }

                if (inputList.size() > 2)
                {
                    c = inputList.at(2);
                }
                if (inputList.size() > 3)
                {
                    d = inputList.at(3);
                }
                if (inputList.size() > 4)
                {
                    e = inputList.at(4);
                }
                if (inputList.size() > 5)
                {
                    f = inputList.at(5);
                }
                if (inputList.size() > 6)
                {
                    g = inputList.at(6);
                }
                if (inputList.size() > 7)

                {
                    h = inputList.at(7);
                }
                int goodCommand = 0; // To check if valid command has been read.

                // Check if comment line is encountered
                if (a == "#")
                {
                    cout << "Encountered comment, skipping to next line." << endl;
                    logFile << "line "<< j+1 << ":" << "Encountered comment, skipping to next line." << endl;
                    continue;
                }

                // Load model type and parameters
                if (a == "model:")
                {
                    springType = b;
                    if (inputList.size() > 2){
                        k1 = atof((c.c_str()));
                    }
                    if (inputList.size() > 3){
                        k2 = atof(d.c_str());
                    }
                    if (inputList.size() > 4){
                        k3 = atof(e.c_str());
                    }
                    //                if (inputList.size() > 5){
                    //                    k4 = atof(f.c_str());
                    //                }
                    //                if (inputList.size() > 6){
                    //                    k5 = atof(g.c_str());
                    //                }
                    goodCommand = 1;

                }

                // Set up forces
                if (a == "force:")
                {
                    if (b == "all")
                    {
                        forceParticles.push_back(0);
                    }
                    else
                    {
                        forceParticles.push_back(atoi(b.c_str()));
                    }

                    forceType.push_back(c);
                    forceAmp.push_back(atof(d.c_str()));
                    forceT1.push_back(atof(e.c_str()));
                    forceT2.push_back(atof(f.c_str()));
                    forceT3.push_back(atof(g.c_str()));
                    forceRamp.push_back(atof(h.c_str()));
                    forceFrequency.push_back(2*pi/(atof(f.c_str())));
                    goodCommand = 1;
                }

                // Set up dissipation
                if (a == "dissipation:")
                {
                    if (b == "all")
                    {
                        dissipationParticles.push_back(0);
                    }
                    else
                    {
                        dissipationParticles.push_back(atoi(b.c_str()));
                    }
                    dissipationStrength.push_back(atof(c.c_str()));
                    goodCommand = 1;
                }

                // Set up boundaries
                if (a == "boundary:")
                {
                    if (b == "left")
                    {
                        cout << "this: " << c << endl;
                        lboundary = c;
                    }
                    else if (b == "right")
                    {
                        rboundary = c;
                    }
                    else
                    {
                        cout << "Cannot read boundary conditions." << endl;
                        cout << "Continuing simulation with default boundaries" << endl;
                    }
                    goodCommand = 1;
                }

                // Set up initial perturbation
                if(a == "init:")
                {
                    // Can open initial conditions from file, if name is given
                    if (b == "file")
                    {
                        fileFlag = 1;
                        std::string fileName = c;
                        std::ifstream initFile(c.c_str());
                        if (!initFile)
                        {
                            // Turn off commenting below if you want to stop code from running without init file.
                            //throw std::runtime_error("Cannot open initial conditions file. Starting with default initial conditions");
                            logFile << "line "<< j+1 << ":" << "Cannot open initial conditions file. Starting with default initial conditions" << endl;
                        }
                        else
                        {
                            int fileLineC = 0;
                            int partic = 0;
                            std::vector<std::string> initList(3);
                            while (getline(initFile, line1))
                            {
                                if (line1 == "")
                                {
                                    cout << "Blank line encountered in initial conditions file at line " << fileLineC + 1 << "." << endl;
                                    cout << "Skipping blank line in initial conditions file." <<endl;
                                    logFile << "Blank line encountered in initial conditions file at line " << fileLineC + 1 << "." << endl;
                                    logFile << "Skipping blank line in initial conditions file." <<endl;
                                }
                                else
                                {
                                    stringstream ss1(line1);
                                    string tmpx, tmpv, tmpa;
                                    ss1 >> tmpx >> tmpv >> tmpa;
                                    partic = fileLineC + 1;

                                    perturbedParticles.push_back(partic);
                                    perturbationType.push_back("pos");
                                    perturbationAmplitude.push_back(atof(tmpx.c_str()));
                                    perturbedParticles.push_back(partic);
                                    perturbationType.push_back("vel");
                                    perturbationAmplitude.push_back(atof(tmpv.c_str()));
                                    perturbedParticles.push_back(partic);
                                    perturbationType.push_back("acc");
                                    perturbationAmplitude.push_back(atof(tmpa.c_str()));
                                    fileLineC += 1;
                                }

                            }
                            systemSize = partic;
                        }
                    }

                    else
                    {
                        perturbedParticles.push_back(atoi(b.c_str()));
                        perturbationType.push_back(c);
                        if (d == "random")
                        {
                            double low = atof(e.c_str());
                            double high = atof(f.c_str());
                            double num = low + (high - low)*(static_cast<double>(rand() % 100))/100;
                            perturbationAmplitude.push_back(num);
                        }
                        else
                        {
                            perturbationAmplitude.push_back(atof(d.c_str()));

                        }
                    }
                    goodCommand = 1;
                }

                // Set up masses
                if (a == "mass:")
                {
                    if (b == "all")
                    {
                        impurityParticles.push_back(0);
                    }
                    else
                    {
                        impurityParticles.push_back(atoi(b.c_str()));
                    }
                    impurityValue.push_back(atof(c.c_str()));
                    goodCommand = 1;
                }

                // Set up total run time
                if (a == "recsteps:")
                {
                    totalTime = atof(b.c_str());
                    goodCommand = 1;
                }

                // Set up system size
                if (a == "systemsize:")
                {
                    systemSize = atof(b.c_str());
                    goodCommand = 1;
                }

                // Set up time step
                if (a == "timestep:")
                {
                    dt = atof(b.c_str());
                    goodCommand = 1;
                }

                // Set up sampling steps
                if (a == "printint:")
                {
                    samplingFrequency = atoi(b.c_str());
                    sampleFlag = 1;
                    goodCommand = 1;
                }

                // Set up integration method
                if (a == "method:")
                {
                    method = b;
                    goodCommand = 1;
                }

                if (goodCommand == 0)
                {
                    cout << "Command not recognized. Please make sure the commands are entered correctly in the code." << endl;
                    cout << "If you want to write comments in the parameter file, make sure that you start the line with a #, leave a space and then write your comment." <<endl;
                    cout << "Make sure that every comment line is preceded with the comment symbol i.e. #." << endl;
                    logFile << "line "<< j+1 << ":" << "Command not recognized. Please make sure the commands are entered correctly in the code." << endl;
                    logFile << "If you want to write comments in the parameter file, make sure that you start the line with a #, leave a space and then write your comment." <<endl;
                    logFile << "Make sure that every comment line is preceded with the comment symbol i.e. #." << endl;

                    return 0;
                    logFile.close();
                }
                cout << line << endl;
                j++;
            }
        }
    }
    logFile.close();
    parametersFile.close();
    cout <<"Read in parameters" << endl;

    if (fileFlag == 1)
    {
        cout << "Read initial conditions from file" << endl;
    }

    // Sample commands that you can tweak to print out to a log.txt file.
    // If you edit the code and need to check if your parameter file is working fine modify these and use them.

    //      ofstream outputFile;
    //     outputFile.open("log.txt");
    //     outputFile << "system:" << '\t' << springType << '\n';
    //     outputFile << "k1:" << '\t' << k1 << '\n';
    //     outputFile << "k2:" << '\t' << k2 << '\n';
    //     outputFile << "k3:" << '\t' << k3 << '\n'
    //     //outputFile << "amplitude:" << '\t' << amplitude << '\n';
    //     outputFile << "time step:" << '\t' << dt << '\n';
    //     outputFile << "total recorded time:" << '\t' << totalTime << '\n';
    //     outputFile << "system size:" << '\t' << systemSize  << '\n';
    //     outputFile << "method:" << '\t' << method << '\n';
    //
    //     outputFile << " velocity perturbations of size 'amplitude' seeded in following particles" << '\n';
    //
    //     for (i = 0; i < perturbedParticles.size();i++){
    //
    //          outputFile << "particle:" << '\t' << perturbedParticles.at(i) << '\t' << perturbationType.at(i) << '\t' << perturbationAmplitude.at(i) << '\n';
    //     }
    //
    //     outputFile.close();

    // Create particle object
    std::vector<Particle> chainParticles(systemSize);
    double defaultx = 0.;
    double defaultv = 0.;
    double defaulta = 0.;

    // Next create an object with info about the springs
    if (lboundary == "periodic")
    {
        rboundary = lboundary;
    }
    if (rboundary == "periodic")
    {
        lboundary = rboundary;
    }

    // Initialize positions, velocities and accelerations
    for (i = 0; i < systemSize; i++)
    {
        chainParticles[i].Setvelocity(defaultv);
        chainParticles[i].Setposition(defaultx);
        chainParticles[i].Setaccel(defaulta);
        chainParticles[i].Setmass(defaultMass);
        chainParticles[i].Setlboundary(lboundary);
        chainParticles[i].Setrboundary(rboundary);
    }

    double amp;
    unsigned int w;
    if (perturbedParticles.size() > 0)
    {
        for (i = 0; i < perturbedParticles.size(); i++)
        {
            w = perturbedParticles.at(i);
            amp = perturbationAmplitude.at(i);
            if (w - 1 < systemSize)
            {
                if (perturbationType.at(i) == "vel")
                {
                    chainParticles[w-1].Setvelocity(amp);
                }
                if (perturbationType.at(i) == "pos")
                {
                    chainParticles[w-1].Setposition(amp);
                }
                if (perturbationType.at(i) == "acc")
                {
                    chainParticles[w-1].Setaccel(amp);
                }
            }
        }
    }

    std::string type;
    double t1;
    double t2;
    double t3;
    double frequency;
    double ramp;

    // Initialize force object to default values
    std::vector<Force> force(systemSize);
    for (i = 0; i < systemSize; i++)
    {
        force[i].Settype("cosine");
        force[i].Sett1(0.);
        force[i].Sett2(0.);
        force[i].Sett3(0.);
        force[i].Setfrequency(0.);
        force[i].Setramp(0.);
        force[i].Setamp(0.);
        force[i].Setgamma(0.);
    }

    // Retrieve initial conditions from values in parameter file
    if (forceParticles.size() > 0)
    {
        for (i = 0; i < forceParticles.size(); i++)
        {
            w = forceParticles.at(i);
            type = forceType.at(i);
            amp = forceAmp.at(i);
            t1 = forceT1.at(i);
            t2 = forceT2.at(i);
            t3 = forceT3.at(i);
            frequency = forceFrequency.at(i);
            ramp = forceRamp.at(i);
            amp = forceAmp.at(i);

            if (w == 0)
            {
                for (j = 0; j < systemSize; j++)
                {
                    force[j].Settype(type);
                    force[j].Sett1(t1);
                    force[j].Sett2(t2);
                    force[j].Sett3(t3);
                    force[j].Setfrequency(frequency);
                    force[j].Setramp(ramp);
                    force[j].Setamp(amp);
                }
            }
            else
            {
                j = w-1;
                force[j].Settype(type);
                force[j].Sett1(t1);
                force[j].Sett2(t2);
                force[j].Sett3(t3);
                force[j].Setfrequency(frequency);
                force[j].Setramp(ramp);
                force[j].Setamp(amp);
            }
        }
    }

    // Initialize dissipation object to default values
    for (i = 0; i < systemSize; i++)
    {
        force[i].Setgamma(0.);
    }

    // Retrieve dissipation values from dissipation object
    if(dissipationParticles.size() > 0)
    {
        for (i = 0; i < dissipationParticles.size(); i++)
        {
            w = dissipationParticles.at(i);
            amp = dissipationStrength.at(i);

            if (w == 0)
            {
                for (j = 0; j < systemSize; j++)
                {
                    force[j].Setgamma(amp);
                }
            }
            else
            {
                j = w-1;
                force[j].Setgamma(amp);
            }
        }
    }

    // Set mass is 1.0 first
    for (i = 0; i < systemSize; i++)
    {
        mass.push_back(defaultMass);
    }
    // Retrieve values of impurities if there are any
    if (impurityParticles.size() > 0)
    {
        for (i = 0; i < impurityParticles.size(); i++)
        {
            w = impurityParticles.at(i);
            amp = impurityValue.at(i);
            if (w == 0)
            {
                for (j = 0; j < systemSize; j++)
                {
                    chainParticles[j].Setmass(amp);
                }
            }
            else
            {
                j = w-1;
                chainParticles[j].Setmass(amp);
            }
        }
    }

    // Check that mass is greater than 0
    for (i = 0; i < systemSize; i++)
    {
        amp = chainParticles.at(i).Getmass();
        if (amp <= 0.00000000001)
        {
            chainParticles[i].Setmass(defaultMass);
            cout << "Mass at %d th particle was less than or equal to 0." << endl;
        }
    }

    // Create simulation object
    Simulation simParams;
    if (sampleFlag == 0)
    {
        samplingFrequency = 1/dt;
        if (samplingFrequency < 1)
        {
            samplingFrequency = 10;
        }
    }

    simParams.SettimeStep(dt);
    simParams.SetsamplingFrequency(samplingFrequency);
    simParams.SettotalTime(totalTime);
    simParams.Setmethod(method);
    simParams.SetsystemSize(systemSize);

    // Sanity check for parameters
    // Turn on if you want to see what code is reading. Build in more if necessary.

    //    cout << "dt" << simParams.GettimeStep() << endl;
    //    cout << "samplingFreq" << simParams.GetsamplingFrequency() << endl;
    //    cout << "total time" << simParams.GettotalTime() <<  endl;
    //    cout << "method" << simParams.Getmethod() << endl;

    // Check if files with the same names as the output from this simulation exist. If they do delete them.
    // Check if position file exists and delete if it does.
    std::string fileNameCheck;
    std::string errOut;
    fileNameCheck = "position.dat";

    if(ifstream(fileNameCheck.c_str()))
    {
        cout << "Existing file will be deleted - "<< fileNameCheck << endl;
        if( remove( fileNameCheck.c_str() ) != 0 )
        {
            errOut = "Error deleting file "+fileNameCheck;
            perror( errOut.c_str() );
            cout << endl;
        }
        else
        {
            errOut = fileNameCheck+" successfully deleted.";
            puts( errOut.c_str() );
            cout << endl;
        }
    }

    // Check if velocity file exists and delete if it does.
    fileNameCheck = "velocity.dat";

    if(ifstream(fileNameCheck.c_str()))
    {
        cout << "Existing file will be deleted - "<< fileNameCheck << endl;
        if( remove( fileNameCheck.c_str() ) != 0 )
        {
            errOut = "Error deleting file "+fileNameCheck;
            perror( errOut.c_str() );
            cout << endl;
        }
        else
        {
            errOut = fileNameCheck+" successfully deleted.";
            puts( errOut.c_str() );
            cout << endl;
        }
    }

    // Check if acceleration file exists and delete if it does.
    fileNameCheck = "acceleration.dat";

    if(ifstream(fileNameCheck.c_str()))
    {
        cout << "Existing file will be deleted - "<< fileNameCheck << endl;
        if( remove( fileNameCheck.c_str() ) != 0 )
        {
            errOut = "Error deleting file "+fileNameCheck;
            perror( errOut.c_str() );
            cout << endl;
        }
        else
        {
            errOut = fileNameCheck+" successfully deleted.";
            puts( errOut.c_str() );
            cout << endl;
        }
    }

    // Check if mass file exists and delete if it does.
    fileNameCheck = "mass.dat";

    if(ifstream(fileNameCheck.c_str()))
    {
        cout << "Existing file will be deleted - "<< fileNameCheck << endl;
        if( remove( fileNameCheck.c_str() ) != 0 )
        {
            errOut = "Error deleting file "+fileNameCheck;
            perror( errOut.c_str() );
            cout << endl;
        }
        else
        {
            errOut = fileNameCheck+" successfully deleted.";
            puts( errOut.c_str() );
            cout << endl;
        }
    }

    // Check if kinetic energy file exists and delete if it does.
    fileNameCheck = "ke.dat";

    if(ifstream(fileNameCheck.c_str()))
    {
        cout << "Existing file will be deleted - "<< fileNameCheck << endl;
        if( remove( fileNameCheck.c_str() ) != 0 )
        {
            errOut = "Error deleting file "+fileNameCheck;
            perror( errOut.c_str() );
            cout << endl;
        }
        else
        {
            errOut = fileNameCheck+" successfully deleted.";
            puts( errOut.c_str() );
            cout << endl;
        }
    }

    // Check if potential energy file exists and delete if it does.
    fileNameCheck = "pe.dat";

    if(ifstream(fileNameCheck.c_str()))
    {
        cout << "Existing file will be deleted - "<< fileNameCheck << endl;
        if( remove( fileNameCheck.c_str() ) != 0 )
        {
            errOut = "Error deleting file "+fileNameCheck;
            perror( errOut.c_str() );
            cout << endl;
        }
        else
        {
            errOut = fileNameCheck+" successfully deleted.";
            puts( errOut.c_str() );
            cout << endl;
        }
    }

    // Check if total energy file exists and delete if it does.
    fileNameCheck = "totalEnergy.dat";

    if(ifstream(fileNameCheck.c_str()))
    {
        cout << "Existing file will be deleted - "<< fileNameCheck << endl;
        if( remove( fileNameCheck.c_str() ) != 0 )
        {
            errOut = "Error deleting file "+fileNameCheck;
            perror( errOut.c_str() );
            cout << endl;
        }
        else
        {
            errOut = fileNameCheck+" successfully deleted.";
            puts( errOut.c_str());
            cout << endl;
        }
    }

    // Check if restart file exists and delete if it does.
    fileNameCheck = "restart.dat";

    if(ifstream(fileNameCheck.c_str()))
    {
        cout << "Existing file will be deleted - "<< fileNameCheck << endl;
        if( remove( fileNameCheck.c_str() ) != 0 )
        {
            errOut = "Error deleting file "+fileNameCheck;
            perror( errOut.c_str() );
            cout << endl;
        }
        else
        {
            errOut = fileNameCheck+" successfully deleted.";
            puts( errOut.c_str() );
            cout << endl;
        }
    }

    cout << "Setting up simulation" << endl;

    // Create all kinds of Spring Objects
    std::vector<fpuPotential> fpuObject(1);
    std::vector<todaPotential> todaObject(1);
    std::vector<morsePotential> morseObject(1);
    std::vector<lennardJonesPotential> lennardJonesObject(1);

    // Check which model is chosen and accordingly start simulation
    if (springType == "toda")
    {
        todaObject[0].Setk1(k1);
        todaObject[0].Setk2(k2);
        simParams.f_startSim(chainParticles, todaObject, force);
    }
    else if (springType == "fput")
    {
        fpuObject[0].Setk1(k1);
        fpuObject[0].Setk2(k2);
        fpuObject[0].Setk3(k3);
        simParams.f_startSim(chainParticles, fpuObject, force);
    }
    else if (springType == "morse")
    {
        morseObject[0].Setk1(k1);
        morseObject[0].Setk2(k2);
        simParams.f_startSim(chainParticles, morseObject, force);
    }
    else if (springType == "lennardjones")
    {
        lennardJonesObject[0].Setk1(k1);
        lennardJonesObject[0].Setk2(k2);
        simParams.f_startSim(chainParticles, lennardJonesObject, force);
    }
    else
    {
        cout << "No recognized model type specified. Exiting program." << endl;
        return 0;
    }

    // Get current time after code completion
    auto finish = std::chrono::high_resolution_clock::now();

    // Calculate elapsed time
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Time elapsed: " << elapsed.count() << "s" << endl;

    // Write the time taken into the log-file
    logFile.open ("log.txt", std::ofstream::out | std::ofstream::app);
    logFile << endl;
    logFile << "Time elapsed: " << elapsed.count() << " " << "s" << endl;

    // Close log file
    logFile.close();

    return 0;
}
