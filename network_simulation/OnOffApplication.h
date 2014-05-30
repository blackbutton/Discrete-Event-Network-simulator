

#ifndef __ON_OFF_APPLICATION_H__
#define __ON_OFF_APPLICATION_H__		

#include "Application.h"
#include "Handler.h"
#include <stdlib.h>

#define PACKET_SIZE 10000


class OnOffApplication  : public Application
{
public:
  OnOffApplication(double rate0, double meanOffTime0, double meanOnTime0);
  void         SetPeerAddress(int peerAddr);
  virtual void Start(); // Start the application
  virtual void Stop() {};  // Stop the application
  virtual void Handle(Event*, Time_t);
  unsigned long SentPcktCnt; 
private:
  double rateWhenOn;
  double meanOffTime;
  double meanOnTime;
  int    peerAddress;
};

#endif
