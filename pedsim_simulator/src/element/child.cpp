#include <pedsim_simulator/element/child.h>

#include <algorithm>
#include <cmath>
#include <random>

default_random_engine generator_child;

Child::Child()
{
    //initialization with type CHILD
   Ped::Tagent::setType(Ped::Tagent::CHILD);

    //assign random maximal speed in m/s with mean 0.435
    normal_distribution<double> distribution(0.435, 0.35);

    vmax = distribution(generator_child);
}
