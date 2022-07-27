#ifndef ELDERLY_H
#define ELDERLY_H

#include <pedsim_simulator/element/agent.h>

class Elderly : public Agent
{
public:
    Elderly();
//    virtual ~Elderly();

//public:
//   void setType(Ped::Tagent::AgentType typeIn);

/*public:
   void varyDistraction();
   double getDecisonTime() const;
   void setDecisionTime(double);*/

protected:
   void processCarInformation(const Elderly* car);

protected:
  double vmax;
  //double decisionTime;

};

#endif // ELDERLY_H
