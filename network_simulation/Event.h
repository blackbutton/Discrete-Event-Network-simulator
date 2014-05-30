

#ifndef __EVENT_H__
#define __EVENT_H__		

class Packet;

typedef enum 
{
  NoEvent,
	NETWORK_INTERFACE_SEND,
	NETWORK_INTERFACE_RECEIVE,
	ON_OFF_APP_START_SEND,
	SIMULATOR_STOP,
}Event_t ;
  
class Event
{
  public:
    Event() : ev(NoEvent) { }   
    Event(Event_t t) : ev(t) {} // Specific event constructor
    Event_t EventType();       
  public:
    Event_t ev;
	  Packet *p;							
};
#endif


