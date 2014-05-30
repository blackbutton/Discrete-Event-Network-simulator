#include "stdio.h"
#include "NetworkInterface.h"
#include "Simulator.h"
#include "Event.h"
#include "Packet.h"



NetworkInterface :: NetworkInterface()
: busy(false)
{
	queue  = new DropTailQueue(QUEUE_SIZE);
}


void NetworkInterface:: AssociateNode(Node *N)
{
	node = N;
}


void NetworkInterface :: AddP2PLink(NetworkLink *NLink)
{
	link = NLink;
}


void NetworkInterface :: Send(Packet * pckt)
{
	if((busy == true) || (queue->GetCurrentSize() !=0)) 
		queue->Enque(pckt);
    
	 
	else
	{
		Event *evnt = new Event;
		Time_t t;
		t = (pckt->count * 8)/link->dataRate;
		evnt->ev = NETWORK_INTERFACE_SEND;
		Simulator::Schedule( t,this,evnt);
		link->Send(pckt);		
		busy = true;
	}
}


void NetworkInterface :: Handle(Event* event,Time_t t)
{

	switch(event->ev)
	{
		case NETWORK_INTERFACE_SEND:
		{
			
			if(queue->GetCurrentSize() !=0)
			{
				busy = true;
				Packet * pckt = queue->Deque();				
				Event *evnt = new Event;
				Time_t t;
				t = (pckt->count * 8)/link->dataRate;
				evnt->ev = NETWORK_INTERFACE_SEND;
				Simulator::Schedule( t ,this,evnt);
				link->Send(pckt);				
			}
			else
				busy = false;
			break;		
		}
		
		case NETWORK_INTERFACE_RECEIVE:
		{
			Packet *p = event->p;			
			this->node->Receive(p);
			break;
		}
		
		default:
		{
			printf("Invalid Event\n");
			break;
		}
	}	
}
