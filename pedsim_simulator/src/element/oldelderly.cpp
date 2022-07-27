#include <pedsim_simulator/element/oldelderly.h>

#include <algorithm>
#include <cmath>
#include <random>

default_random_engine generator_oldeld;

Oldelderly::Oldelderly()
{
    //initialization with type OLDELDER
   Ped::Tagent::setType(Ped::Tagent::OLDELDER);

    //assign random maximal speed in m/s with mean 1.05
    normal_distribution<double> distribution(1.05, 0.24);

    vmax = distribution(generator_oldeld);
}
