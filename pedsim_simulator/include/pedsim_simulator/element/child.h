#ifndef CHILD_H
#define CHILD_H

#include <pedsim_simulator/element/agent.h>

class Child : public Agent
{

    //Constructor
public:
    Child();




    //Methods
public:
    void setType(Ped::Tagent::AgentType typeIn);
    void varyDistraction();
//    double getDecisonTime() const;
//    void setDecisionTime(double);

    //Attributes
//public:
   // double decisionTime;

//Test
public :
    string getNom();

};

#endif // CHILD_H
