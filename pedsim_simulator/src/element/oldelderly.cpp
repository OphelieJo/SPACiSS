#include <pedsim_simulator/agentstatemachine.h>
#include <pedsim_simulator/config.h>
#include <pedsim_simulator/element/oldelderly.h>
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

default_random_engine generator_oldeld;

Oldelderly::Oldelderly()
{
    //initialization with type OLDELDER
   Ped::Tagent::setType(Ped::Tagent::OLDELDER);

    //assign random maximal speed in m/s with mean 1.05
    normal_distribution<double> distribution(1.05, 0.24);

    vmax = distribution(generator_oldeld);

    nomTest = "Oldelder";
 }

 string Oldelderly::getNom(){
     return nomTest;
 }



