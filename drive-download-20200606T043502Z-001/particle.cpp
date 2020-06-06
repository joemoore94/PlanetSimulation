#include <iostream>
#include "particle.hpp"

//default constructor
PARTICLE::PARTICLE(int ID, int L)
{
  this -> L = L;
  buildParticle(ID);
}

void PARTICLE::buildParticle(int ID)
{
  block::MT ran;
  auto val = ran.rand_real(-L, L);
  this -> ID = ID;
  this -> mass = 5; //kg
  this -> X = val(-1); //meters
  this -> Y = val(-1); //meters
  this -> vX = 0; //m/s
  this -> vY = 0; //m/s
  this -> aX = 0; //m/s/s
  this -> aY = 0; //m/s/s
}

//get functions
const int PARTICLE::getID() const {return this -> ID;}
const int PARTICLE::getMass() const {return this -> mass;}
const double PARTICLE::getX() const {return this -> X;}
const double PARTICLE::getY() const {return this -> Y;}
const double PARTICLE::getvX() const {return this -> vX;}
const double PARTICLE::getvY() const {return this -> vY;}
const double PARTICLE::getaX() const {return this -> aX;}
const double PARTICLE::getaY() const {return this -> aY;}

//set functions
void PARTICLE::setMass(int mass) {this -> mass = mass;}
void PARTICLE::setX(double X) {this -> X = X;}
void PARTICLE::setY(double Y) {this -> Y = Y;}
void PARTICLE::setvX(double vX) {this -> vX = vX;}
void PARTICLE::setvY(double vY) {this -> vY = vY;}
void PARTICLE::setaX(double aX) {this -> aX = aX;}
void PARTICLE::setaY(double aY) {this -> aY = aY;}

void PARTICLE::printToFile(std::string filename) const
{
  std::ofstream dataOut(filename, std::ios::app | std::ios::ate);
  if(!dataOut.is_open())
    std::cout << "Error while opening the file" << std::endl;

  dataOut << this -> mass << " ";
  dataOut << this -> X << " ";
  dataOut << this -> Y << " ";
  dataOut << this -> vX << " ";
  dataOut << this -> vY << " ";
  dataOut << this -> aX << " ";
  dataOut << this -> aY << std::endl;
  dataOut.close();
}

void PARTICLE::printValues() const
{
  std::cout << "--- Particle Values ---" << std::endl;
  std::cout << "ID: " << this -> ID << std::endl;
  std::cout << "mass: " << this -> mass << std::endl;
  std::cout << "x: " << this -> X << std::endl;
  std::cout << "y: " << this -> Y << std::endl;
  std::cout << "v_x: " << this -> vX << std::endl;
  std::cout << "v_y: " << this -> vY << std::endl;
  std::cout << "a_x: " << this -> aX << std::endl;
  std::cout << "a_y: " << this -> aY << std::endl;
}
