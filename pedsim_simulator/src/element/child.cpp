#include <pedsim_simulator/agentstatemachine.h>
#include <pedsim_simulator/config.h>
#include <pedsim_simulator/element/child.h>
#include <pedsim_simulator/element/waypoint.h>
#include <pedsim_simulator/force/force.h>
#include "pedsim_simulator/element/obstacle.h"
#include <pedsim_simulator/element/attractionarea.h>
#include <pedsim_simulator/scene.h>
#include <pedsim_simulator/waypointplanner/waypointplanner.h>
#include <pedsim_simulator/rng.h>

#include <pedsim_simulator/element/agentgroup.h>
#include <QSet>
#include <fstream>

#include <random>

default_random_engine generator_child;

Child::Child()
{
    //initialization with type CHILD
   Ped::Tagent::setType(Ped::Tagent::CHILD);

    //assign random maximal speed in m/s with mean 0.435
    normal_distribution<double> distribution(0.435, 0.35);
    vmax = distribution(generator_child);

    nomTest="child";
}

string Child::getNom()
{
 return nomTest;
}

//Methods


void Child::setType(Ped::Tagent::AgentType typeIn)
{
  // call super class' method
  Ped::Tagent::setType(typeIn);

  normal_distribution<double> speed(0.435, 0.35); //0.435, 0.35
  this->setVmax(speed(RNG()));
  this->setForceFactorDesired(0.5);
  this->SetRadius(0.35);
  varyDistraction();
  initializePedestrianValues();

  // inform users
  emit typeChanged(typeIn);
}

void Child::varyDistraction(){
   //Allocation of value for "basic"/low distraction between 0 et 0.5
   uniform_real_distribution<> dDistribution(0, 0.5);

   //Random draw to dertimine if child is very distracted (<=2)
   uniform_real_distribution<> dist (0, 100);
   double randomDist = dist(RNG());
   if (randomDist > 2){
       setDistraction(dDistribution(RNG()));
   }
   else {
       uniform_real_distribution<> dDistribution(0.5, 1);
       setDistraction(dDistribution(RNG()));
   }
}

void Child::processCarInformation(const Agent* car)
{
       // Physical collision radius
       double collisionRadius =  this->agentRadius + car->getAgentRadius();
       // Danger radius
       double radiusDanger = this->agentRadius + car->getAgentRadius() + dangerRadius;
       // Risk radius
       double radiusRisk =  this->agentRadius + car->getAgentRadius() + riskRadius;

       // AV speed
       double carvx = car->getvx();
       double carvy = car->getvy();

       double carx = car->getPosition().x;
       double cary = car->getPosition().y;

       // Velocity vector of pedestrian with his ideal speed
       Ped::Tvector pedIdealVelocity = this->getVelocity().normalized().scaled(vmax);
      if(isSteppingBack)
         pedIdealVelocity = this->desiredDirection.normalized().scaled(vmax/3);

       double b = 2*(this->getx()-carx)*(pedIdealVelocity.x-carvx) + 2*(this->gety()-cary)*(pedIdealVelocity.y-carvy);
       double a = pow(pedIdealVelocity.x-carvx, 2)+ pow(pedIdealVelocity.y-carvy,2);
       double cDanger = pow(this->getx()-carx, 2) + pow(this->gety()-cary,2)-pow(radiusDanger,2);
       double cRisk = pow(this->getx()-carx, 2) + pow(this->gety()-cary,2)-pow(radiusRisk,2);
       double cCollision = pow(this->getx()-carx, 2) + pow(this->gety()-cary,2)-pow(collisionRadius,2);
       double deltaDanger = pow(b, 2)-4*a*cDanger;
       double deltaRisk = pow(b, 2)-4*a*cRisk;
       double deltaCollision = pow(b, 2)-4*a*cCollision;
       double ttc = 10;


       // if physical collision possible (in past or present or future)
       if(deltaDanger>=0)
       {
          // first time to collision
         ttc = min((-b+sqrt(deltaDanger))/(2*a), (-b-sqrt(deltaDanger))/(2*a));

          // Colision in near future (< 5s)
          if(ttc>ttcLow && ttc<ttcUp)
          {
             Ped::Tvector pedPos = p;
             Ped::Tvector pedVelo = pedIdealVelocity;
             if(isInGroup()) {
                pedVelo = group->getWalkingDirection();
                if(deltaCollision>0 && min((-b+sqrt(deltaCollision))/(2*a),(-b-sqrt(deltaCollision))/(2*a))<ttcImminent ){
                   myforce = Ped::Tvector();
                   //ROS_INFO_STREAM("temp leave group");
                } else {
                  pedPos = group->getCenterOfMass();
                }
             }


             Ped::Tangle diffAngle = Ped::Tvector(carvx, carvy).angleTo(pedVelo);
             double degreeDiffAngle = diffAngle.toDegree();
             //ROS_INFO_STREAM(id<< " "<<"ANGLE DIFFERENCE CAR - PEDESTRIAN IN DEGREE " << degreeDiffAngle);

             // if car in front or back -> turn instead of following social force
             // it is not enough to set social force stronger, because may cause to follow the car move...
             if (!isSteppingBack && (degreeDiffAngle > (180.0 - angleFrontalCollisionRisk) ||  degreeDiffAngle < angleFrontalCollisionRisk - 180.0
                 || (degreeDiffAngle >0 && degreeDiffAngle<angleFrontalCollisionRisk) || (degreeDiffAngle<0 && degreeDiffAngle > -angleFrontalCollisionRisk))){

                this->isStopped = false;
                this->isRunning = false;

                Ped::Tvector diffDirection = (pedPos-car->getPosition()).normalized();
                Ped::Tangle angle = car->getVelocity().angleTo(diffDirection);
                Ped::Tvector turnVector = angle.sign() * car->getVelocity().leftNormalVector().normalized();
                socialforce = turnVector + physicalForce();
               // ROS_INFO_STREAM(id<<"tttuuuurn");
             }
             else{
                // Bearing angle considers the AV size now
                double margin = 0.0;
                if(car->getVelocity().length()<0.2)
                   hesitationThreshold = 0.8;
                Ped::Tvector carNearestSide = Ped::Tvector(car->getPosition().x + (car->getRadius((Ped::Tvector(carvx, carvy).angleTo(pedPos-car->getPosition())),margin) * (pedPos-car->getPosition()).normalized()).x/*(car->getVelocity().normalized().x)*/,
                                      car->getPosition().y + (car->getRadius((Ped::Tvector(carvx, carvy).angleTo(pedPos-car->getPosition())),margin) * (pedPos-car->getPosition()).normalized()).y);
                // Bearing angle from ped point of view
                Ped::Tangle bearingAngle = pedVelo.angleTo(carNearestSide - pedPos);
                double bearingAngleDeriv = (carNearestSide - pedPos).angleTo((carNearestSide - pedPos)+(Ped::Tvector(carvx, carvy) - pedVelo)).toRadian();
                // Bearing angle from car point of view
                Ped::Tangle bearingAngleC = (Ped::Tvector(carvx, carvy).angleTo(pedPos-carNearestSide));
                double bearingAngleDerivC = (pedPos-carNearestSide).angleTo((pedPos-carNearestSide)+(pedVelo-Ped::Tvector(carvx, carvy))).toRadian();

                double cx = ((this->getx()+pedIdealVelocity.x*ttc)*this->agentRadius + (car->getx()+carvx*ttc)*car->getAgentRadius())/radiusDanger;
                double cy = ((this->gety()+pedIdealVelocity.y*ttc)*this->agentRadius + (car->gety()+carvy*ttc)*car->getAgentRadius())/radiusDanger;
                Ped::Tvector collisionPoint = Ped::Tvector(cx, cy);
                Ped::Tvector pedToColl = collisionPoint - Ped::Tvector(this->getx()+pedIdealVelocity.x * ttc,this->gety()+pedIdealVelocity.y * ttc);

                // if both converge/diverge -> already crossed
                if((bearingAngle.sign()*bearingAngleDeriv<0 && bearingAngleC.sign()*bearingAngleDerivC<0)
                      || (bearingAngle.sign()*bearingAngleDeriv>0 && bearingAngleC.sign()*bearingAngleDerivC>0)
                      ||abs(pedToColl.angleTo(this->getWalkingDirection()).toDegree())>120
                      ){
                   //ROS_INFO_STREAM("already crossed");
                   this->isStopped = false;
                   this->isSteppingBack=false;
                   this->isRunning=false;
                }

               else{
                //ROS_INFO_STREAM(id<<" "<<bearingAngle.sign()*bearingAngleDeriv<<" "<<bearingAngleC.sign()*bearingAngleDerivC);
                if(!isSteppingBack &&!isRunning && !isStopped && fabs(bearingAngleDeriv) <= hesitationThreshold)
                {
                  //ROS_INFO_STREAM("hesitation: run or stop");

                   // Follow group decision
                   if(this->isInGroup() && pedPos == group->getCenterOfMass())
                   {
                      AgentGroup* group = getGroup();

                      // check all group members
                      foreach (Agent* member, group->getMembers())
                      {
                         // ignore agent himself
                         if (member == this)
                           continue;
                         if(member->getIsStopped()){
                            this->isSteppingBack=true;//this->wantStop();
                            break;
                         }
                         else if(member->getIsRunning()){
                            this->wantRun();
                            break;
                         }
                     }
                   }
                   // If no decision (not in groupe or first to decide)
                   if(!isRunning && !isStopped){
                       uniform_real_distribution<> decision (0, 100);
                       double randomDecision = decision(RNG());
                          if (randomDecision >63.5){
                            this->wantStop();
                         }
                         else{ //For value 0 they run, taht is the 25% remaining
                              this->wantRun();
                         }
                  }
                }


                // if ped will arrive first
                else if (bearingAngle.sign()*bearingAngleDeriv > hesitationThreshold || (bearingAngle.sign()*bearingAngleDeriv >=0.0 && isRunning)){
                   this->wantRun();
                }
                // if ped will arrive second
                else if (bearingAngle.sign()*bearingAngleDeriv < -hesitationThreshold || (bearingAngle.sign()*bearingAngleDeriv <=0.0 && isStopped)){
                   if (bearingAngle.sign()*bearingAngleDeriv > -hesitationThreshold && isStopped ){
                      this->isSteppingBack=true;
                   }
                   else{
                      this->wantStop();
                      this->isSteppingBack=false;
                   }
                }
              }
          }
           }
          else if (isSteppingBack){
            this->isSteppingBack = false;
            this->wantStop();
         }
       }
        else if (isSteppingBack){
          this->isSteppingBack = false;
          this->wantStop();
       }


       // if will be in risky distance
       if(deltaRisk >= 0)
       {
          // last time of risk
          double ttcRisk = max((-b+sqrt(deltaRisk)/2*a), (-b-sqrt(deltaRisk)/2*a));
          // if risky not ended and running/stopped, continue to run/stop
          if (ttcRisk>0){
            // myforce = Ped::Tvector(); //ignore group forces
             if (isRunning || isStopped || isSteppingBack){}
          }
          else {
             this->isRunning = false;
             this->isStopped = false;
             this->isSteppingBack = false;
          }
       }
       else {  //out of risky zone
          this->isRunning = false;
          this->isStopped = false;
          this->isSteppingBack = false;
       }

       // action: run or stop
       if (isRunning){
          socialforce = physicalForce();
          if(isInGroup())
             desiredforce = (group->getWalkingDirection().normalized().scaled(runVmax) - v)/relaxationTime;
          else desiredforce = (v.normalized().scaled(runVmax) - v)/relaxationTime;
       }
       else if (isSteppingBack)
       {
          socialforce = physicalForce();
          desiredforce = -desiredforce;
       }
       else if (isStopped){
          if(ttc<ttcImminent){
              socialforce = physicalForce();
              desiredforce = (-v/relaxationTime);
          }else
             socialforce = -car->getVelocity().normalized() + physicalForce();
       }
       processType = "Childdd";
    }

    string Child::getProcessType()
    {
        return processType;
    }
