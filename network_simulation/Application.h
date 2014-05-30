
#ifndef __APPLICATION_H__
#define __APPLICATION_H__		

#include "CommonDefs.h"
#include "Handler.h"

class Node;

typedef enum App_Typecast
{
	ON_OFF_APPLICATION,	
	TRAFFIC_SYNC_APPLICATION
}App_Type;

class Application : public Handler
{
  public:
  Application() {}; 
  void AttachToNode(Node*); // Attach this application to a node
  virtual void Start() = 0; // Start the application
  virtual void Stop()  = 0; // Stop the application
  virtual void Handle(Event*, Time_t) =0; // Handle events
  public:
  Node* node;
  App_Type AppType;
};


#endif
