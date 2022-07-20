#include <pedsim_simulator/element/elderly.h>

#include <algorithm>
#include <cmath>
#include <random>

default_random_engine generator;

Elderly::Elderly()
{
    //initialization with type ELDER
   Ped::Tagent::setType(Ped::Tagent::ELDER);

    //assign random maximal speed in m/s with mean 1.29
   normal_distribution<double> distribution(1.29, 0.26);

   vmax = distribution(generator);
}
