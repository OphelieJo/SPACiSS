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
   void varyDistraction();
//   double getDecisonTime() const;
//   void setDecisionTime(double);

protected:
   void processCarInformation(const Agent* car);

   //Attributes
//protected:
  //double decisionTime;

   //Test
public :
   string getNom();
   string getProcessType();

};

#endif // ELDERLY_H
