#include <pedsim_simulator/agentstatemachine.h>
#include <pedsim_simulator/config.h>
#include <pedsim_simulator/element/adolescent.h>
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

const double Adolescent::DISTRACTION_PHONE_NEEDED = 20;

Adolescent::Adolescent()
{
    //initialization with type ADO
    Ped::Tagent::setType(Ped::Tagent::ADO);
    nomTest = "ado";
}

string Adolescent::getNom(){
    return nomTest;
}

//Methods

void Adolescent::setType(Ped::Tagent::AgentType typeIn)
{
  // call super class' method
  Ped::Tagent::setType(typeIn);

  normal_distribution<double> speed(1.34, 0.26);
  this->setVmax(speed(RNG()));
  this->SetRadius(0.35);
  varyDistraction();
  initializePedestrianValues();

  // inform users
  emit typeChanged(typeIn);
}

double Adolescent::getDistractionPhoneNeeded() const{
      return Adolescent::DISTRACTION_PHONE_NEEDED;
}


//void Adolescent::varyDistraction(){
//   //Allocation of value for "basic"/low distraction between 0 et 0.5
//   uniform_real_distribution<> dDistribution(0, 0.5);

//   //Random draw to dertimine if adolescent is very distracted (<=20)
//   uniform_real_distribution<> dist (0, 100);
//   double randomDist = dist(RNG());
//   if (randomDist > 20){
//       setDistraction(dDistribution(RNG()));
//   }
//   else {
//       uniform_real_distribution<> dDistribution(0.5, 1);
//       setDistraction(dDistribution(RNG()));
//   }
//}
