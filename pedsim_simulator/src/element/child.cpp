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

const double Child::DISTRACTION_PHONEALL_NEEDED = 2.9;
const double Child::DISTRACTION_PHONE_NEEDED = 1.6;
const double Child::DISTRACTION_MUSIC_NEEDEED = 1.3;
const double Child::DECISION_RUN_NEEDED = 63.5;
const double Child::DECISION_TIME_NEEDED = 0.87;

default_random_engine generator_child;

Child::Child()
{
    //initialization with type CHILD
   Ped::Tagent::setType(Ped::Tagent::CHILD);

    //assign random maximal speed in m/s with mean 0.43
    normal_distribution<double> distribution(0.43, 0.35);
    vmax = distribution(generator_child);

    nomTest="child";
}

string Child::getNom()
{
 return nomTest;
}

//Methods


void Child::setType(Ped::Tagent::AgentType typeIn)
{
  // call super class' method
  Ped::Tagent::setType(typeIn);

  normal_distribution<double> speed(0.435, 0.35);
  this->setVmax(max(0.1,speed(RNG())));
  varyDistraction();
  initializePedestrianValues();
  this->setForceFactorSocial(this->forceFactorSocial*0.10);
  this->setForceFactorObstacle(this->forceFactorObstacle*0.10);

  // inform users
  emit typeChanged(typeIn);
}

double Child::getDistractionPhoneAllNeeded() const
{
       return Child::DISTRACTION_PHONEALL_NEEDED;
}

double Child::getDistractionPhoneNeeded() const
{
       return Child::DISTRACTION_PHONE_NEEDED;
}

double Child::getDistractionMusicNeeded() const
{
       return Child::DISTRACTION_MUSIC_NEEDEED;
}

double Child::getDecisionRunNeeded() const{
      return Child::DECISION_RUN_NEEDED;
}

double Child::getDecisionTimeNeeded() const{
      return Child::DECISION_TIME_NEEDED;
}



string Child::getProcessType()
{
      return processType;
}
