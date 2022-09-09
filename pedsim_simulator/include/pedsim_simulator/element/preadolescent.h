#ifndef PREADOLESCENT_H
#define PREADOLESCENT_H

#include <pedsim_simulator/element/child.h>

class Preadolescent : public Child
{

    //Constructor
public:
    Preadolescent();



    //Methods
public:
   void setType(Ped::Tagent::AgentType typeIn);
   void varyDistraction();
   void computeForces();


   //Test
public :
   string getNom();
};

#endif // PREADOLESCENT_H
