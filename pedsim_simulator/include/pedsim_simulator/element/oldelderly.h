#ifndef OLDELDERLY_H
#define OLDELDERLY_H

#include <pedsim_simulator/element/elderly.h>

class Oldelderly : public Elderly
{
public:
    Oldelderly();
   // virtual ~Oldelderly();

//public:
 //  void setType(Ped::Tagent::AgentType typeIn);

protected:
    double vmax;

};

#endif // OLDELDERLY_H
