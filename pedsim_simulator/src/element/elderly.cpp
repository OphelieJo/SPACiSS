#include <pedsim_simulator/agentstatemachine.h>
#include <pedsim_simulator/config.h>
#include <pedsim_simulator/element/elderly.h>
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

const double Elderly::DISTRACTION_PHONEALL_NEEDED = 0.5;
const double Elderly::DISTRACTION_PHONE_NEEDED = 0.25;
const double Elderly::DISTRACTION_MUSIC_NEEDEED = 0.25;
const double Elderly::DECISION_RUN_NEEDED = 27;
const double Elderly::DECISION_TIME_NEEDED = 0.88;

default_random_engine generator_eld;

Elderly::Elderly()
{
    //initialization with type ELDER
   Ped::Tagent::setType(Ped::Tagent::ELDER);

    //assign random maximal speed in m/s with mean 1.29
   normal_distribution<double> distribution(1.29, 0.24);

   vmax = distribution(generator_eld);

   nomTest = "elder";
}

string Elderly::getNom(){
    return nomTest;
}

//Methods

void Elderly::setType(Ped::Tagent::AgentType typeIn)
{   
  normal_distribution<double> speed(1.29, 0.24);
  this->setVmax(speed(RNG()));
  this->setForceFactorDesired(0.5);
  this->SetRadius(0.35);
  varyDistraction();
  initializePedestrianValues();

  // inform users
  emit typeChanged(typeIn);
}

double Elderly::getDistractionPhoneAllNeeded() const
{
       return Elderly::DISTRACTION_PHONEALL_NEEDED;
}

double Elderly::getDistractionPhoneNeeded() const
{
       return Elderly::DISTRACTION_PHONE_NEEDED;
}

double Elderly::getDistractionMusicNeeded() const
{
       return Elderly::DISTRACTION_MUSIC_NEEDEED;
}

double Elderly::getDecisionRunNeeded() const{
      return Elderly::DECISION_RUN_NEEDED;
}

double Elderly::getDecisionTimeNeeded() const{
      return Elderly::DECISION_TIME_NEEDED;
}


string Elderly::getProcessType()
{
    return processType;
}
