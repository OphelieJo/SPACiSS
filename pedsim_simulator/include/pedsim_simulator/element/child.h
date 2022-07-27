#ifndef CHILD_H
#define CHILD_H

#include <pedsim_simulator/element/agent.h>

class Child : public Agent
{
public:
    Child();
    //virtual ~Child();

//public:
//    void setType(Ped::Tagent::AgentType typeIn);


/*public:
    void varyDistraction();
    double getDecisonTime() const;
    void setDecisionTime(double);*/

protected:
    double vmax;
   // double decisionTime;

};

#endif // CHILD_H
