#ifndef _PARTICLE_HPP
#define _PARTICLE_HPP
#include <fstream>
#include <string>
#include "mt.hpp"

class PARTICLE
{
	private:
    int ID; //indentifies particle
		int L; //dimensions of 2L by 2L box
    int seed; //given to constructor for MT
    int mass; //in kg
    double X; //x position in meters
    double Y; //y position in meters
    double vX; //x component of velocity in m/s
    double vY; //y component of velocity in m/s
    double aX; //x component of acceleration in m/s/s
    double aY; //y component of acceleration in m/s/s

    void buildParticle(int ID);

  public:
    PARTICLE(int ID, int L); //default constructor

    //get functions
    const int getID() const;
    const int getMass() const;
    const double getX() const;
    const double getY() const;
    const double getvX() const;
    const double getvY() const;
    const double getaX() const;
    const double getaY() const;

		//set functions
		void setMass(int mass);
		void setX(double X);
		void setY(double Y);
		void setvX(double vX);
		void setvY(double vY);
		void setaX(double aX);
		void setaY(double aY);

    void printValues() const;
    void printToFile(std::string filename) const;
};
#endif
