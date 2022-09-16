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
   virtual double getDistractionPhoneNeeded() const;
   virtual double getDecisionTimeNeeded() const;

//Const
   static const double DISTRACTION_PHONE_NEEDED;
   static const double DECISION_TIME_NEEDED;


   //Test
public :
   string getNom();
};

#endif // PREADOLESCENT_H
