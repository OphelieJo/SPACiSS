/**
* Copyright 2014 Social Robotics Lab, University of Freiburg
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*    # Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*    # Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*    # Neither the name of the University of Freiburg nor the names of its
*       contributors may be used to endorse or promote products derived from
*       this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
* \author Billy Okal <okal@cs.uni-freiburg.de>
* \author Sven Wehner <mail@svenwehner.de>
*/

#include <pedsim_simulator/element/agentcluster.h>
#include <pedsim_simulator/element/waitingqueue.h>
#include <pedsim_simulator/rng.h>
#include <pedsim_simulator/scene.h>

AgentCluster::AgentCluster(double xIn, double yIn, int countIn) //mettre le type en paramètre ?
{
  static int lastID = 0;

  // initialize values
  id = ++lastID;
  position = Ped::Tvector(xIn, yIn);
  theta = Ped::Tangle::fromRadian(0.0);
  count = countIn;
  distribution = QSizeF(0, 0);

  agentType = Ped::Tagent::ADULT;

  shallCreateGroups = true;
  purpose = Agent::AgentPurpose::UNKNOWN;
};

AgentCluster::~AgentCluster()
{
}

QList<Agent*> AgentCluster::dissolve()
{
  QList<Agent*> agents;

  std::uniform_real_distribution<double> randomX(-distribution.width() / 2, distribution.width() / 2);
  std::uniform_real_distribution<double> randomY(-distribution.height() / 2, distribution.height() / 2);

  // create and initialize agents
  for (int i = 0; i < count; ++i)
  {
      Agent* a;
      if (agentType == Ped::Tagent::CHILD)
         a = new Child();
      else if (agentType == Agent::PREADO)
         a = new Preadolescent();
      else if (agentType == Agent::ADO)
         a = new Adolescent();
      else if (agentType == Agent::ELDER)
         a = new Elderly();
      else if (agentType == Agent::OLDELDER)
         a = new Oldelderly;
      else a = new Agent();

    double randomizedX,randomizedY;

    bool overlapFree = false;
    int count = 0;
    while(!overlapFree && count<20)
    {
        randomizedX = position.x;
        randomizedY = position.y;
        // handle dx=0 or dy=0 cases
        if (distribution.width() != 0)
            randomizedX += randomX(RNG());
        if (distribution.height() != 0)
            randomizedY += randomY(RNG());

        //First agent case
        if(agents.empty())
            overlapFree = true;

        for (Agent* agent : agents)
        {
            //If agent is closer than 50cm (medium body size) with an other agent, pick a new position
            if(sqrt(pow(agent->getx()-randomizedX, 2)+pow(agent->gety()-randomizedY, 2)) < 0.5)
            {
                overlapFree = false;
                break;
            }
            else overlapFree = true;
        }
        count ++;
    }

    a->setPosition(randomizedX, randomizedY);
    // orientation
    a->setvx(cos(theta.toRadian())/100);
    a->setvy(sin(theta.toRadian())/100);

    a->setType(agentType);
    a->setPurpose(purpose);

    // add waypoints to the agent
    foreach (Waypoint* waypoint, waypoints)
      a->addWaypoint(waypoint);

    // add agent to the scene
    SCENE.addAgent(a);

    // add agent to the return list
    agents.append(a);
  }

  return agents;
}

int AgentCluster::getId() const
{
  return id;
}

int AgentCluster::getCount() const
{
  return count;
}

void AgentCluster::setCount(int countIn)
{
  count = countIn;
}

const QList<Waypoint*>& AgentCluster::getWaypoints() const
{
  return waypoints;
}

void AgentCluster::addWaypoint(Waypoint* waypointIn)
{
  // keep track of waypoint
  waypoints.append(waypointIn);
}

bool AgentCluster::removeWaypoint(Waypoint* waypointIn)
{
  // don't keep track of waypoint anymore
  int removedWaypoints = waypoints.removeAll(waypointIn);

  // inform user about successful removal
  if (removedWaypoints > 0)
    return true;
  else
    return false;
}

void AgentCluster::addWaitingQueue(WaitingQueue* queueIn)
{
  Waypoint* waypoint = dynamic_cast<Waypoint*>(queueIn);

  // keep track of waiting queues
  waypoints.append(waypoint);
}

bool AgentCluster::removeWaitingQueue(WaitingQueue* queueIn)
{
  Waypoint* waypoint = dynamic_cast<Waypoint*>(queueIn);

  // don't keep track of waypoint anymore
  int removedWaitingQueues = waypoints.removeAll(waypoint);

  // inform user about successful removal
  return (removedWaitingQueues > 0);
}

Ped::Tvector AgentCluster::getPosition() const
{
  return position;
}

void AgentCluster::setPosition(const Ped::Tvector& positionIn)
{
  position = positionIn;

  // inform users
  emit positionChanged(position.x, position.y);
}

void AgentCluster::setPosition(double px, double py)
{
  setPosition(Ped::Tvector(px, py));
}

void AgentCluster::setX(double xIn)
{
  position.x = xIn;

  // inform users
  emit positionChanged(position.x, position.y);
}

void AgentCluster::setY(double yIn)
{
  position.y = yIn;

  // inform users
  emit positionChanged(position.x, position.y);
}

void AgentCluster::setTheta(Ped::Tangle thetaIn)
{
  theta = thetaIn;
}

int AgentCluster::getType() const
{
  return agentType;
}

void AgentCluster::setType(Ped::Tagent::AgentType typeIn)
{
    agentType = typeIn;

  if (agentType == Agent::ELDER)
  {
    Agent* a = new Elderly();
  }
  else if (agentType == Agent::OLDELDER)
  {
    Agent* a = new Oldelderly();
  }
  else if (agentType == Agent::CHILD)
  {
    Agent* a = new Child();
  }
  else if (agentType == Agent::PREADO)
  {
    Agent* a = new Preadolescent();
  }
  else {
    Agent* a = new Agent();
  }

  // inform users
  emit typeChanged(agentType);
}

int AgentCluster::getPurpose() const
{
   return purpose;
}
void AgentCluster::setPurpose(Agent::AgentPurpose purposeIn)
{
   purpose = purposeIn;

   // inform users
   emit purposeChanged(purpose);
}

bool AgentCluster::getShallCreateGroups() const
{
  // TODO: actually use this
  return shallCreateGroups;
}

void AgentCluster::setShallCreateGroups(bool shallCreateGroupsIn)
{
  shallCreateGroups = shallCreateGroupsIn;
}

QSizeF AgentCluster::getDistribution() const
{
  return distribution;
}

void AgentCluster::setDistribution(double xIn, double yIn)
{
  distribution.setWidth(xIn);
  distribution.setHeight(yIn);
}

void AgentCluster::setDistributionWidth(double xIn)
{
  distribution.setWidth(xIn);
}

void AgentCluster::setDistributionHeight(double yIn)
{
  distribution.setHeight(yIn);
}

QPointF AgentCluster::getVisiblePosition() const
{
  return QPointF(position.x, position.y);
}

void AgentCluster::setVisiblePosition(const QPointF& positionIn)
{
  setPosition(positionIn.x(), positionIn.y());
}

QString AgentCluster::toString() const
{
  return tr("AgentCluster (@%1,%2)").arg(position.x).arg(position.y);
}
