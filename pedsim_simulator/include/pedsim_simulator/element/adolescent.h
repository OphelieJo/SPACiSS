#ifndef ADOLESCENT_H
#define ADOLESCENT_H

#include <pedsim_simulator/element/agent.h>

class Adolescent : public Agent
{

    //Constructor and Destructor
public:
   Adolescent();
  //virtual ~Adolescent();

//public:
//   void setType(Ped::Tagent::AgentType typeIn);

public:
   void varyDistraction();

protected:
    double vmax;

};

#endif // ADOLESCENT_H
