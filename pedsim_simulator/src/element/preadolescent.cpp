#include <pedsim_simulator/agentstatemachine.h>
#include <pedsim_simulator/config.h>
#include <pedsim_simulator/element/preadolescent.h>
#include <pedsim_simulator/element/waypoint.h>
#include <pedsim_simulator/force/force.h>
#include "pedsim_simulator/element/obstacle.h"
#include <pedsim_simulator/element/attractionarea.h>
#include <pedsim_simulator/scene.h>
#include <pedsim_simulator/waypointplanner/waypointplanner.h>
#include <pedsim_simulator/rng.h>

#include <pedsim_simulator/element/agentgroup.h>
#include <QSet>
#include <fstream>

#include <random>

default_random_engine generator_preado;

Preadolescent::Preadolescent()
{
    //initialization with type PREADO
   Ped::Tagent::setType(Ped::Tagent::PREADO);

    //assign random maximal speed in m/s with mean 1.23
   normal_distribution<double> distribution(1.23, 0.31);

   vmax = distribution(generator_preado);

   nomTest = "preado";
}

string Preadolescent::getNom(){
    return nomTest;
}

//Methods

void Preadolescent::setType(Ped::Tagent::AgentType typeIn)
{
  // call super class' method
  Ped::Tagent::setType(typeIn);

  normal_distribution<double> speed(1.20, 0.303);
  this->setVmax(speed(RNG()));
  this->setForceFactorDesired(0.5);
  this->SetRadius(0.35);
  varyDistraction();
  initializePedestrianValues();

  // inform users
  emit typeChanged(typeIn);
}

void Preadolescent::varyDistraction(){
   //Allocation of value for "basic"/low distraction between 0 et 0.5
   uniform_real_distribution<> dDistribution(0, 0.5);

   //Random draw to dertimine if preadolescent is very distracted (<=5)
   uniform_real_distribution<> dist (0, 100);
   double randomDist = dist(RNG());
   if (randomDist > 5){
       setDistraction(dDistribution(RNG()));
   }
   else {
       uniform_real_distribution<> dDistribution(0.5, 1);
       setDistraction(dDistribution(RNG()));
   }
    //setDistraction(0.4);
}


void Preadolescent::computeForces()
{
  // update forces
  desiredforce = desiredForce();
  if (forceFactorSocial > 0)
     socialforce = socialForce();
  if (forceFactorObstacle > 0)
    obstacleforce = obstacleForce();
  myforce = myForce(desiredDirection);

  collideAV = false;
  for (auto neighbor : getNeighbors())
  {
     if (neighbor->getId() == id)
        continue;
     if (neighbor->getType() == ROBOT){
         //verif decisionTime
         if (decisionTime >= 0.76)
         processCarInformation(neighbor);
         else decisionTime += CONFIG.getTimeStepSize();

         // is agent colliding with AV ?
         Ped::Tvector diff = neighbor->getPosition() - p;
         double physicalDistance = diff.length() -
               (this->getRadius(v.angleTo(diff),0.0) + neighbor->getRadius(neighbor->getWalkingDirection().angleTo(-diff),0.0));
           if(physicalDistance <= 0.0){
              collideAV = true;
              v = physicalForce() + obstacleforce;
              ROS_INFO_STREAM(id << " COLLIDE");
           }
      }
   }

  if (!perceiveAV) {
     this->isRunning = false;
     this->isStopped = false;
     this->isSteppingBack = false;
  }

  if(type==ROBOT){
     this->disableForce("Random");
  }
}
