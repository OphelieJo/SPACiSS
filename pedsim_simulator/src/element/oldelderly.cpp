#include <pedsim_simulator/element/oldelderly.h>

#include <algorithm>
#include <cmath>
#include <random>

default_random_engine generator;

Oldelderly::Oldelderly()
{
    //initialization with type OLDELDER
   Ped::Tagent::setType(Ped::Tagent::OLDELDER);

    //assign random maximal speed in m/s with mean 1.05
    normal_distribution<double> distribution(1.05, 0.26);

    vmax = distribution(generator);
}
