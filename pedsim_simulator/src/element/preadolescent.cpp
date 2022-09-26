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

const double Preadolescent::DISTRACTION_PHONEALL_NEEDED = 7;
const double Preadolescent::DISTRACTION_PHONE_NEEDED = 5.7;
const double Preadolescent::DISTRACTION_MUSIC_NEEDEED = 1.3;
const double Preadolescent::DECISION_TIME_NEEDED = 0.76;

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
  //this->setForceFactorDesired(0.5);
  this->SetRadius(0.35);
  varyDistraction();
  initializePedestrianValues();

  // inform users
  emit typeChanged(typeIn);
}

double Preadolescent::getDistractionPhoneAllNeeded() const
{
       return Preadolescent::DISTRACTION_PHONEALL_NEEDED;
}

double Preadolescent::getDistractionPhoneNeeded() const
{
       return Preadolescent::DISTRACTION_PHONE_NEEDED;
}

double Preadolescent::getDistractionMusicNeeded() const
{
       return Preadolescent::DISTRACTION_MUSIC_NEEDEED;
}

double Preadolescent::getDecisionTimeNeeded() const{
      return Preadolescent::DECISION_TIME_NEEDED;
}
