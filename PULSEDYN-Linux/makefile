CC=g++
CFLAGS= -Wall -fexceptions -O3 -std=c++11 -fopt-info-vec-optimized 


bin/PULSEDYN: main.o obj/boundaryConditions.o obj/force.o obj/fpuPotential.o \
		  obj/lennardJonesPotential.o obj/morsePotential.o obj/Output.o \
		  obj/Particle.o obj/Simulation.o obj/todaPotential.o
	- mkdir bin 
	- $(CC) -o bin/PULSEDYN obj/boundaryConditions.o obj/force.o obj/fpuPotential.o \
		  obj/lennardJonesPotential.o obj/morsePotential.o obj/Output.o \
		  obj/Particle.o obj/Simulation.o obj/todaPotential.o main.o $(CFLAGS)
	- chmod ugo+x bin/PULSEDYN

main.o: main.cpp include/allIncludes.h include/boundaryConditions.h \
		include/force.h include/fpuPotential.h include/lennardJonesPotential.h \
		include/morsePotential.h include/Output.h include/Particle.h \
		include/Simulation.h include/todaPotential.h	
	- $(CC) -c -o main.o -I include main.cpp $(CFLAGS)
	
obj/boundaryConditions.o: src/boundaryConditions.cpp include/allIncludes.h include/boundaryConditions.h \
		include/force.h include/fpuPotential.h include/lennardJonesPotential.h \
		include/morsePotential.h include/Output.h include/Particle.h \
		include/Simulation.h include/todaPotential.h
	- mkdir obj
	- $(CC) -c -o obj/boundaryConditions.o -I include src/boundaryConditions.cpp $(CFLAGS)
	
obj/force.o: src/force.cpp include/allIncludes.h include/boundaryConditions.h \
		include/force.h include/fpuPotential.h include/lennardJonesPotential.h \
		include/morsePotential.h include/Output.h include/Particle.h \
		include/Simulation.h include/todaPotential.h
	- $(CC) -c -o obj/force.o -I include src/force.cpp $(CFLAGS)
	
obj/fpuPotential.o: src/fpuPotential.cpp include/allIncludes.h include/boundaryConditions.h \
		include/force.h include/fpuPotential.h include/lennardJonesPotential.h \
		include/morsePotential.h include/Output.h include/Particle.h \
		include/Simulation.h include/todaPotential.h	
	- $(CC) -c -o obj/fpuPotential.o -I include src/fpuPotential.cpp $(CFLAGS)

	
obj/lennardJonesPotential.o: src/lennardJonesPotential.cpp include/allIncludes.h include/boundaryConditions.h \
		include/force.h include/fpuPotential.h include/lennardJonesPotential.h \
		include/morsePotential.h include/Output.h include/Particle.h \
		include/Simulation.h include/todaPotential.h
	- $(CC) -c -o obj/lennardJonesPotential.o -I include src/lennardJonesPotential.cpp $(CFLAGS)


obj/morsePotential.o: src/morsePotential.cpp include/allIncludes.h include/boundaryConditions.h \
		include/force.h include/fpuPotential.h include/lennardJonesPotential.h \
		include/morsePotential.h include/Output.h include/Particle.h \
		include/Simulation.h include/todaPotential.h
	- $(CC) -c -o obj/morsePotential.o -I include src/morsePotential.cpp $(CFLAGS)


obj/Output.o: src/Output.cpp include/allIncludes.h include/boundaryConditions.h \
		include/force.h include/fpuPotential.h include/lennardJonesPotential.h \
		include/morsePotential.h include/Output.h include/Particle.h \
		include/Simulation.h include/todaPotential.h
	- $(CC) -c -o obj/Output.o -I include src/Output.cpp $(CFLAGS)
		
obj/Particle.o: src/Particle.cpp include/allIncludes.h include/boundaryConditions.h \
		include/force.h include/fpuPotential.h include/lennardJonesPotential.h \
		include/morsePotential.h include/Output.h include/Particle.h \
		include/Simulation.h include/todaPotential.h
	- $(CC) -c -o obj/Particle.o -I include src/Particle.cpp $(CFLAGS)
		
obj/Simulation.o: src/Simulation.cpp include/allIncludes.h include/boundaryConditions.h \
		include/force.h include/fpuPotential.h include/lennardJonesPotential.h \
		include/morsePotential.h include/Output.h include/Particle.h \
		include/Simulation.h include/todaPotential.h
	- $(CC) -c -o obj/Simulation.o -I include src/Simulation.cpp $(CFLAGS)
		
obj/todaPotential.o: src/todaPotential.cpp include/allIncludes.h include/boundaryConditions.h \
		include/force.h include/fpuPotential.h include/lennardJonesPotential.h \
		include/morsePotential.h include/Output.h include/Particle.h \
		include/Simulation.h include/todaPotential.h
	- $(CC) -c -o obj/todaPotential.o -I include src/todaPotential.cpp $(CFLAGS)