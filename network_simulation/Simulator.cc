#include "Simulator.h"
#include "Event.h"
#include "Handler.h"
#include "NetworkLink.h"
#include "NetworkInterface.h"
#include "Application.h"
#include "OnOffApplication.h"
#include "PacketSyncApplication.h"
#include "Packet.h"
#include <iostream>
#include <stdio.h>

using namespace std;

void Simulator::Handle(Event *ev ,Time_t t)
{
	
	sim_stop = true;
}


void Simulator::Schedule(Time_t t,Handler * h,Event * evnt)
{	
 	evnt_list.insert(EventPair_t(t +Simulator::Now(), HandlerEvent_t(h, evnt)));
}


void Simulator::Run()
{
	int totpcksend=0;
	while(1)
	{
		EventPair_t currentEvent = *evnt_list.begin();
		evnt_list.erase(evnt_list.begin());
		now = currentEvent.first;	
		HandlerEvent_t he = currentEvent.second;
		Handler *hndl = he.first;
		Event *evnt = he.second;
		hndl->Handle(evnt, now);
		
		if(sim_stop==true || evnt_list.empty()==true)
		{
			break;
		}
		
	}
	
}


void Simulator::StopAt(Time_t t)
{
	static Event event(SIMULATOR_STOP);	
	Simulator::Schedule(t - Simulator::Now(),Simulator::instance, &event);
}


Time_t Simulator::Now()
{
	return now;
}

