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

const double Adolescent::DISTRACTION_PHONEALL_NEEDED = 25;
const double Adolescent::DISTRACTION_PHONE_NEEDED = 15.25;
const double Adolescent::DISTRACTION_MUSIC_NEEDEED = 9.75;

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

double Adolescent::getDistractionPhoneAllNeeded() const
{
       return Adolescent::DISTRACTION_PHONEALL_NEEDED;
}

double Adolescent::getDistractionPhoneNeeded() const
{
       return Adolescent::DISTRACTION_PHONE_NEEDED;
}

double Adolescent::getDistractionMusicNeeded() const
{
       return Adolescent::DISTRACTION_MUSIC_NEEDEED;
}

