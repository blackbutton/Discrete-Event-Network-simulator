
#ifndef __DROP_TAIL_QUEUE_H__
#define __DROP_TAIL_QUEUE_H__

#include "Queue.h"
#include "Packet.h"
#include <deque>

#define QUEUE_SIZE 5000


class DropTailQueue : public Queue
{
public:
  DropTailQueue(int maxLth);    
  virtual bool Enque(Packet*);  // Enqueue a packet
  virtual Packet* Deque();      //Dequeue a packet
  unsigned int GetMaxSize();
  unsigned int GetCurrentSize();
private:
  unsigned int MaxSize;
  unsigned int CurrentSize;
  unsigned int PacketDropCnt;
  std::deque<Packet*> PacketQueue;
};

#endif



