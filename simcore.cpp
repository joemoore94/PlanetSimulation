#include "simcore.hpp"

void SIMCORE::tasks(std::string param_filename)
{
  // simple list of tasks for the constructor to do
  readParamsFile(param_filename);
  populateParticles();
  clearFiles();
}

SIMCORE::SIMCORE()
{
  tasks("params.dat");
}

SIMCORE::SIMCORE(std::string param_filename)
{
  tasks(param_filename);
}

void SIMCORE::runEngine()
{
  printParticlesToFile();
  for(int j=0; j<Niterations; j++)
  {
    for(int i=0; i<Nparticles; i++)
    {
      sunDestroyer(i);
      calculateNeighbors(i);
      calculateX(i, dt);
      calculateY(i, dt);
      calculateVelX(i, dt);
      calculateVelY(i, dt);
      calculateAccelX(i);
      calculateAccelY(i);
    }
    printParticlesToFile();
  }
}

void SIMCORE::planetSim()
{
  // sets up particles to produce planets by setting them up to orbit the sun
  double x, y, r, theta, v;
  for(int i=0; i<Nparticles; i++)
  {
    x = particles.at(i).getX();
    y = particles.at(i).getY();
    theta = atan2(y,x);
    r = sqrt(x*x + y*y);
    v = sqrt(G*sunMass/r);
    particles.at(i).setvX(-v*sin(theta));
    particles.at(i).setvY(v*cos(theta));
  }
}

void SIMCORE::readParamsFile(std::string param_filename)
{
  std::string junk;
  std::ifstream dataIn(param_filename);
	if(!dataIn.is_open())
		std::cout << "Error while opening the file" << std::endl;
  dataIn >> junk;
  dataIn >> Nparticles;
  dataIn >> junk;
  dataIn >> Niterations;
  dataIn >> junk;
  dataIn >> sunMass;
  dataIn >> junk;
  dataIn >> dt;
  dataIn >> junk;
  dataIn >> L;
  dataIn.close();
}

void SIMCORE::populateParticles()
{
  // populates the particles vector with particle objects
  for(int i=0; i<Nparticles; i++)
  {
    PARTICLE particle(i, L);
    particles.push_back(particle);
  }
}

void SIMCORE::clearFiles() const
{
  system("rm -f particles/*");
}

void SIMCORE::printParticlesToFile() const
{
  int ID;
  std::string filename;
  std::stringstream ss;
  for(int i=0; i<Nparticles; i++)
  {
    ID = i;
    ss.clear();
    ss << "particles/" << ID << ".dat";
    ss >> filename;
    particles.at(i).printToFile(filename);
  }
}

void SIMCORE::printParticle(int i) const
{
  particles.at(i).printValues();
}

const int SIMCORE::getNparticles() const
{
  return this -> Nparticles;
}

void SIMCORE::sunDestroyer(int i)
{
  // destroys particle that flies into the sun
  double delX, delY, r;
  delX = particles.at(i).getX();
  delY = particles.at(i).getY();
  r = sqrt(delX*delX + delY*delY);
  if(r<5)
  {
    clearParticle(i);
  }
}

void SIMCORE::clearParticle(int i)
{
  // clears particle and sets it at the orgin
  particles.at(i).setMass(0);
  particles.at(i).setX(0);
  particles.at(i).setY(0);
  particles.at(i).setvX(0);
  particles.at(i).setvY(0);
  particles.at(i).setaX(0);
  particles.at(i).setaY(0);
}

void SIMCORE::calculateNeighbors(int i)
{
  double delX, delY, r;
  neighbors.clear();
  for(int j=0; j<Nparticles; j++)
  {
    delX = particles.at(i).getX() - particles.at(j).getX();
    delY = particles.at(i).getY() - particles.at(j).getY();
    r = sqrt(delX*delX + delY*delY);
    //std::cout << r << std::endl;
    if(r<10 && r>0.5)
    {
      neighbors.push_back(j);
      //std::cout << j << std::endl;
    }
    if(r<=0.5 && r!=0)
    {
      combine(i,j);
    }
  }
}

void SIMCORE::combine(int i, int j)
{
  // conserves momentum for an inelastic collosions
  int m1, m2, mass;
  double vX, vY;
  m1 = particles.at(i).getMass();
  m2 = particles.at(j).getMass();
  mass = m1 + m2;
  vX = (m1*particles.at(i).getvX() + m2*particles.at(j).getvX())/mass;
  vY = (m1*particles.at(i).getvY() + m2*particles.at(j).getvY())/mass;
  particles.at(i).setMass(mass);
  particles.at(i).setvX(vX);
  particles.at(i).setvX(vY);
  clearParticle(j);
}

// The following function produce position, velocity and acceleration 

void SIMCORE::calculateAccelX(int i)
{
  double aX, delX, delY, r;
  delX = particles.at(i).getX();
  delY = particles.at(i).getY();
  r = sqrt(delX*delX + delY*delY);
  aX = -G*sunMass/pow(r,3)*delX;
  for(unsigned int j=0; j<neighbors.size(); j++)
  {
    delY = particles.at(i).getY() - particles.at(neighbors.at(j)).getY();
    delX = particles.at(i).getX() - particles.at(neighbors.at(j)).getX();
    r = sqrt(delY*delY + delX*delX);
    aX -= G*particles.at(neighbors.at(j)).getMass()/pow(r,3)*delX;
  }
  particles.at(i).setaX(aX);
}

void SIMCORE::calculateAccelY(int i)
{
  double aY, delX, delY, r;
  delX = particles.at(i).getX();
  delY = particles.at(i).getY();
  r = sqrt(delX*delX + delY*delY);
  aY = -G*sunMass/pow(r,3)*delY;
  for(unsigned int j=0; j<neighbors.size(); j++)
  {
    delY = particles.at(i).getY() - particles.at(neighbors.at(j)).getY();
    delX = particles.at(i).getX() - particles.at(neighbors.at(j)).getX();
    r = sqrt(delY*delY + delX*delX);
    aY -= G*particles.at(neighbors.at(j)).getMass()/pow(r,3)*delY;
  }
  particles.at(i).setaY(aY);
}

void SIMCORE::calculateVelX(int i, double dt)
{
  double vX;
  vX = particles.at(i).getvX() + dt*particles.at(i).getaX();
  particles.at(i).setvX(vX);
}

void SIMCORE::calculateVelY(int i, double dt)
{
  double vY;
  vY = particles.at(i).getvY() + dt*particles.at(i).getaY();
  particles.at(i).setvY(vY);
}

void SIMCORE::calculateX(int i, double dt)
{
  double X;
  X = particles.at(i).getX() + dt*particles.at(i).getvX() + 0.5*dt*dt*particles.at(i).getaX();
  particles.at(i).setX(X);
}

void SIMCORE::calculateY(int i, double dt)
{
  double Y;
  Y = particles.at(i).getY() + dt*particles.at(i).getvY() + 0.5*dt*dt*particles.at(i).getaY();
  particles.at(i).setY(Y);
}
