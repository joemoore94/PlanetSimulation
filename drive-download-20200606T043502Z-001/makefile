all: Sim

Sim: main.o simcore.o particle.o
	g++ main.o simcore.o particle.o -o Sim

main.o: main.cpp simcore.hpp
	g++ -Wall -c main.cpp

simcore.o: simcore.cpp simcore.hpp
	g++ -Wall -c simcore.cpp

particle.o: particle.cpp particle.hpp
	g++ -Wall -c particle.cpp

clean:
	rm *.o Sim
