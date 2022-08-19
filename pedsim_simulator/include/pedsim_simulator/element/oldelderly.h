#ifndef OLDELDERLY_H
#define OLDELDERLY_H

#include <pedsim_simulator/element/elderly.h>

class Oldelderly : public Elderly
{
    //Constructor
public:
    Oldelderly();

    //Methods
public :
    void setType(Ped::Tagent::AgentType typeIn);

    //Test
 public :
    string getNom();

};

#endif // OLDELDERLY_H
