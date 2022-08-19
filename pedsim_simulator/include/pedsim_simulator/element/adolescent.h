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
   void varyDistraction();

   //Test
public :
   string getNom();
};

#endif // ADOLESCENT_H
