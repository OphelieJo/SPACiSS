#ifndef PREADOLESCENT_H
#define PREADOLESCENT_H

#include <pedsim_simulator/element/child.h>

class Preadolescent : public Child
{
public:
    Preadolescent();
    //virtual ~Preadolescent();

//public:
  // void setType(Ped::Tagent::AgentType typeIn);

public:
   void varyDistraction();
   
protected:
   double vmax;

};

#endif // PREADOLESCENT_H
