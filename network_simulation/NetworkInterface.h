
#ifndef __NETWORK_INTERFACE_H__
#define __NETWORK_INTERFACE_H__

#include "Node.h"
#include "DropTailQueue.h"
#include "NetworkLink.h"
#include "CommonDefs.h"
#include "Handler.h"


class NetworkLink;
class Packet;
class Queue;
class Node;

class NetworkInterface : public Handler
{
public:
  NetworkInterface(); 
  void AssociateNode(Node *);
  void AddP2PLink(NetworkLink*);
  void Send(Packet*); // Send specified packet to peer
  void Handle(Event*, Time_t); // Handle event (2 events possible NETWORK_INTERFACE_RECEIVE and NETWORK_INTERFACE_SEND)
public:
  NetworkLink*      link;
  DropTailQueue*    queue; 
  Node*             node;  
  bool              busy;  
};

#endif

