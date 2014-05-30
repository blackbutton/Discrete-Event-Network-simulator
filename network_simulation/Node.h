
#ifndef __NODE_H__
#define __NODE_H__

#include "NetworkLink.h"
#include "NetworkInterface.h"
#include "Handler.h"
#include "OnOffApplication.h"
#include "PacketSyncApplication.h"
#include "Packet.h"
#include "Application.h"
#include "Event.h"
#include <vector>
#include <iostream>
#include <map>

using namespace std;

class NetworkLink;
class NetworkInterface;
class PacketSyncApplication;
class Application;

typedef enum Node_Typecast
{
	NODE_ROUTER,
	NODE_HOST			
}Node_Type;


class Node : public Handler
{
public:
  Node(); 
  Node(unsigned int nodeaddr, Node_Type NType);
  void ComputeRoutes();     // Populate the routing table
  void AddNeighbor(Node*, double delay, double datarate);  // Add a new interface, p2p link and neighbor node
  void AddInterface  (unsigned int, NetworkInterface*);
  void AddApplication(Application*);
  void Send(int count, int dest);  // Send bytes to specified destination
  void Receive(Packet *);  // Receive bytes from specified source
  virtual void Handle(Event*, Time_t) {}

  unsigned int getAddress()
	{
		return address;
	}
	
  std::vector<Application*> getApplication()
  	{
		return applications;
  	}
	
  vector<NetworkInterface*> getInterface()
	{
		return interfaces;
	}

  void Flagged(bool value)
	{
		flag = value;
	}
	
  bool FlagCheck(void)
	{
		return(flag?true:false);
	}
	
  void addRoute(unsigned int, unsigned int);
  void bfs();
  
  
public:
  unsigned int                   address;   
  Node_Type node_type;
  bool flag;
  std::vector<NetworkInterface*> interfaces;
  std::vector<Application*>      applications;
  std::map<int, int> nextHopRoutes;
  std::map<unsigned int, Node*> NMap;
  std::map<unsigned int, NetworkInterface*>IntMap;
};

#endif
