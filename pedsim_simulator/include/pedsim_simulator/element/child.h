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
    virtual double getDistractionNeeded() const;
    virtual double getDecisionRunNeeded() const;
    virtual double getDecisionTimeNeeded() const;
    virtual double getDetectionTimeNeeded() const;

//Const
    static const double DISTRACTION_NEEDED;
    static const double DECISION_RUN_NEEDED;
    static const double DECISION_TIME_NEEDED;
    static const double DETECTION_TIME_NEEDED;

//Test
public :
    string getNom();
    string getProcessType();



};

#endif // CHILD_H
