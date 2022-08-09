#include <pedsim_simulator/agentstatemachine.h>
#include <pedsim_simulator/config.h>
#include <pedsim_simulator/element/child.h>
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

default_random_engine generator_child;

Child::Child()
{
    //initialization with type CHILD
   Ped::Tagent::setType(Ped::Tagent::CHILD);

    //assign random maximal speed in m/s with mean 0.435
    normal_distribution<double> distribution(0.435, 0.35);

    vmax = distribution(generator_child);
}

//Child::~Child()
//{
//  // clean up
//  foreach (Force* currentForce, forces)
//  {
//    delete currentForce;
//  }
//}


//Methods

void Child::varyDistraction(){
   if(type == ROBOT)
      return;

   //Allocation of value for "basic"/low distraction between 0 et 0.5
   uniform_real_distribution<> dDistribution(0, 0.5);

   //Random draw to dertimine if child is very distracted (<=2)
   uniform_real_distribution<> dist (0, 100);
   double randomDist = dist(RNG());
   if (randomDist > 2){
       setDistraction(dDistribution(RNG()));
   }
   else {
       uniform_real_distribution<> dDistribution(0.5, 1);
       setDistraction(dDistribution(RNG()));
   }
}
