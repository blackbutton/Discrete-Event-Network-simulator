
#ifndef __QUEUE_H__
#define __QUEUE_H__

class Packet;

class Queue 
{
  public:
  Queue() {};                         
  virtual bool Enque(Packet*) = 0;  
  virtual Packet* Deque() = 0;     
};

#endif

