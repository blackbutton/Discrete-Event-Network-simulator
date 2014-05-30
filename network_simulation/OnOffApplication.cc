#include "OnOffApplication.h"		
#include "Simulator.h"
#include "Event.h"
#include "Node.h"
 
OnOffApplication:: OnOffApplication(double rate0,double meanOffTime0,double meanOnTime0)
{
   rateWhenOn=rate0; 
   meanOffTime=meanOffTime0; 
   meanOnTime=meanOnTime0; 
   SentPcktCnt=0;	
   AppType = ON_OFF_APPLICATION;
}


void OnOffApplication::Start()
{
	Time_t t = drand48();	
	Event *evnt = new Event;
	evnt->ev = ON_OFF_APP_START_SEND;
	Simulator::Schedule(t, this,evnt);	
}


void OnOffApplication::SetPeerAddress(int peerAddr)
{
	peerAddress = peerAddr;
}


void OnOffApplication::Handle(Event *evnt,Time_t t)
{
	Time_t T_ON = drand48() * 2 * meanOnTime;
	unsigned long Tot_Bytes = (T_ON * rateWhenOn)/8;
	unsigned long Tot_Packets = Tot_Bytes / PACKET_SIZE;
	unsigned int NodeSize = Simulator::Hosts.size();
	unsigned int DestAdrs;
	unsigned int i;
	
    do
	{
		i=rand() % NodeSize;
		DestAdrs = Simulator::Hosts[i]->getAddress();
		
	}while(DestAdrs == node->getAddress());
	
	while(Tot_Packets>0)
	{
		Tot_Packets--;
		SentPcktCnt++;
		node->Send(PACKET_SIZE,DestAdrs);
	}
	

	Time_t T_OFF = drand48() *2 * meanOffTime; 	
	Event * evt = new Event;
	evt->ev = ON_OFF_APP_START_SEND;
	Simulator::Schedule(T_ON +T_OFF, this, evt);
}

