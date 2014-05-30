
#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#include "CommonDefs.h"
#include "Handler.h"
#include <vector>
#include <map>


using namespace std;

class Event;
class Node;
class Handler;

typedef pair <Handler*, Event*> HandlerEvent_t;
typedef multimap <Time_t, HandlerEvent_t> EventList_t;
typedef EventList_t::value_type EventPair_t;

class Simulator : public Handler 						// Simulator is a subclass of handler
{
public:
  Simulator()
  {
    instance = this;
  }
  static void Run();
  static void StopAt(Time_t);
  static void Schedule(Time_t t, Handler *, Event* ); // Schedule a new future event
  void ComputeRoutes();                    // Compute routing tables at every node
  void Handle(Event*, Time_t); 
  static Time_t Now();				
  static Simulator *instance;
  
  static EventList_t evnt_list;  
  static bool sim_stop;
  static Time_t now;
  static vector<Node*>Hosts;
  static vector<Node*>Node_list;  
};

#endif
