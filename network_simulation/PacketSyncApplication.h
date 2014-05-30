
#ifndef __PACKET_SYNC__APPLICATION_H__
#define __PACKET_SYNC__APPLICATION_H__

#include "Application.h"
#include "Handler.h"
#include "Packet.h"

class PacketSyncApplication  : public Application
{
public:
  PacketSyncApplication();
  void         SetPeerAddress(int peerAddr);
  virtual void Start(); // Start the application
  virtual void Stop();  // Stop the application
  virtual void Handle(Event*, Time_t);
  void PacketReceive(Packet *);
public:
  int totalPacketsReceived;  // statistics
  int totalBytesReceived;
};

#endif
