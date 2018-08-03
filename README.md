# README #

This README would normally document whatever steps are necessary to get your application up and running.

### What is this repository for? ###

This is a software for solving equations of motion of 1D nonlinear many-body systems. A suplied user manual and documentation contain the information needed to run the software. The software has the following features,

Potentials: FPUT, Toda, Morse and Lennard-Jones 
Methods: Gear 5th order predictor corrector, Velocity Verlet 
Boundary Conditions: open, fixed, periodic 
Force: Sine, Cosine (chirping can be set)
Dissipation: Velocity dependent
Parameter file interface with predefined commands (refer to user manual for details).
A list of files making up the software is found in the documentation file available with the software.

### How do I get set up? ###

You can simply doubleclick on the PULSEDYN.o file with a parameter.txt file next to it. However, it does not open a terminal window and show the progress of the simulations. A better way to do this is to open a terminal window and 
run the object file using the command ./PULSEDYN. 
Pre-defined commands to be included in the parameter file are given in the user manual. 

You can also modify the code. Download the code and open the code blocks project. You can make changes to the code using the project.
You will need a C++ compiler to build the project if you make any changes to it. 

### Who do I talk to? ###

Rahul Kashyap
Email me at rahulkashyap7557@gmail.com