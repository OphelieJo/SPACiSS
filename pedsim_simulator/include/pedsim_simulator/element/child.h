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
    void computeForces();

protected:
   void processCarInformation(const Agent* car);

    //Attributes
//public:
   // double decisionTime;

//Test
public :
    string getNom();
    string getProcessType();

};

#endif // CHILD_H
