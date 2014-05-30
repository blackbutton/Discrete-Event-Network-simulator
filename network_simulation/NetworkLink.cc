#include "NetworkLink.h"
#include "Simulator.h"
#include "Event.h"


NetworkLink :: NetworkLink(double delay0,double dataRate0)
{
	delay = delay0;
    dataRate = dataRate0;
}


void NetworkLink :: SetPeer(NetworkInterface *NInt)
{
	peerInt = NInt;	
}


void NetworkLink :: Send(Packet *pckt)
{
  Event * evnt = new Event;  
  Time_t t; 
  
  t = delay + (pckt->count * 8)/dataRate;
  evnt->ev = NETWORK_INTERFACE_RECEIVE;
  evnt->p = pckt;
  Simulator::Schedule(t , peerInt,evnt);
}

