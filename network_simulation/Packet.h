

#ifndef __PACKET_H__
#define __PACKET_H__

class Packet 
{
  public:
  Packet(); 
  Packet(int source0, int destination0, int count0);
public:
  int source;      // Source Node address
  int destination; //Destination Node Address
  int count;      
};
#endif
