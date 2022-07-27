#include <pedsim_simulator/element/preadolescent.h>

#include <algorithm>
#include <cmath>
#include <random>

default_random_engine generator_preado;

Preadolescent::Preadolescent()
{
    //initialization with type PREADO
   Ped::Tagent::setType(Ped::Tagent::PREADO);

    //assign random maximal speed in m/s with mean 1.25
   normal_distribution<double> distribution(1.20, 0.303);

   vmax = distribution(generator_preado);
}

