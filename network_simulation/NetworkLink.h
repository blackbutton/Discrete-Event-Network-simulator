
#ifndef __NETWORK_LINK_H__
#define __NETWORK_LINK_H__

#include "CommonDefs.h"
#include "NetworkInterface.h"


class Node;
class Handler;
class Node;
class NetworkInterface;
class Packet;

class NetworkLink {
public:
NetworkLink(); 
NetworkLink(double delay0, double dataRate0);
void SetPeer(NetworkInterface *);
void Send(Packet*);  
public:
NetworkInterface* peerInt;
double delay; 
double dataRate; 
};


#endif

