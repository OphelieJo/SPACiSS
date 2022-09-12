#ifndef ADOLESCENT_H
#define ADOLESCENT_H

#include <pedsim_simulator/element/agent.h>

class Adolescent : public Agent
{

    //Constructor
public:
   Adolescent();

   //Methods
public:
   void setType(Ped::Tagent::AgentType typeIn);
   virtual double getDistractionNeeded() const;

//Const
   static const double DISTRACTION_NEEDED;

   //Test
public :
   string getNom();
};

#endif // ADOLESCENT_H
