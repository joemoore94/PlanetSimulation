#include <iostream>
#include <fstream>
#include "simcore.hpp"

int main(int argc, char** argv)
{
  SIMCORE sim;
  sim.planetSim();
  sim.runEngine();
  return EXIT_SUCCESS;
}
