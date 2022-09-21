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
   void setType(Ped::Tagent::AgentType typeIn);
   virtual double getDistractionPhoneAllNeeded() const;
   virtual double getDistractionPhoneNeeded() const;
   virtual double getDistractionMusicNeeded() const;

//Const
   static const double DISTRACTION_PHONEALL_NEEDED;
   static const double DISTRACTION_PHONE_NEEDED;
   static const double DISTRACTION_MUSIC_NEEDEED;

   //Test
public :
   string getNom();
};

#endif // ADOLESCENT_H
