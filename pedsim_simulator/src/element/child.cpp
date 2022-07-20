#include <pedsim_simulator/element/child.h>

#include <algorithm>
#include <cmath>
#include <random>

default_random_engine generator;

Child::Child()
{
    //initialization with type CHILD
   Ped::Tagent::setType(Ped::Tagent::CHILD);

    //assign random maximal speed in m/s with mean 0.435
    normal_distribution<double> distribution(0.435, 0.26);

    vmax = distribution(generator);
}
