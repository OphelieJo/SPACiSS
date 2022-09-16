#ifndef ELDERLY_H
#define ELDERLY_H

#include <pedsim_simulator/element/agent.h>

class Elderly : public Agent
{
    //Constructor
public:
    Elderly();


   //Methods
public:
   void setType(Ped::Tagent::AgentType typeIn);
   virtual double getDistractionPhoneNeeded() const;
   virtual double getDecisionRunNeeded() const;
   virtual double getDecisionTimeNeeded() const;

//Const
   static const double DISTRACTION_PHONE_NEEDED;
   static const double DECISION_RUN_NEEDED;
   static const double DECISION_TIME_NEEDED;

   //Test
public :
   string getNom();
   string getProcessType();

};

#endif // ELDERLY_H
