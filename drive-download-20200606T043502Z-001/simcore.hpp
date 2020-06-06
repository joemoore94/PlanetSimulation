#ifndef _SIMCORE_HPP
#define _SIMCORE_HPP

#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "simcore.hpp"
#include "particle.hpp"

class SIMCORE
{
	private:
    // Class attributes
    int Nparticles; //starting number of particles
    long int sunMass; //mass of sun in kg
    int Niterations; //number of iterations
    int L; //dimensions of 2L by 2L box
    double dt; //delta time
    double G = 6.674e-11; //universal gravitational constant in m3 kg-1 s-2
    std::vector<PARTICLE> particles; //vector of particle objects
    std::vector<int> neighbors; //populated with the relevant neighbors of a particle

    // Initialization functions
    void tasks(std::string param_filename);
    void readParamsFile(std::string param_filename); //reads in the parameters from a params file
    void populateParticles(); //populates solor system with particles
		void clearFiles() const;
    void printParticlesToFile() const;
		void sunDestroyer(int i);
		void clearParticle(int i);
    void calculateNeighbors(int i);
		void combine(int i, int j);
    void calculateAccelX(int i);
    void calculateAccelY(int i);
    void calculateVelX(int i, double dt);
    void calculateVelY(int i, double dt);
    void calculateX(int i, double dt);
    void calculateY(int i, double dt);

  public:
    SIMCORE(); // default constructor
    SIMCORE(std::string param_filename); // constructor that takes custom parameters filename

		void runEngine();
		void planetSim();
    void printParticle(int i) const;
    const int getNparticles() const;

};
#endif
