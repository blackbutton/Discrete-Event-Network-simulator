#include "DropTailQueue.h"


DropTailQueue :: DropTailQueue(int maxLth)
{
	 MaxSize = maxLth; 
	 CurrentSize = 0; 
	 PacketDropCnt = 0;
}


bool DropTailQueue :: Enque(Packet * pckt)
{
	if(CurrentSize != MaxSize)
	{
		PacketQueue.push_back(pckt);
		CurrentSize++;
	}
	
	else
	{
		PacketDropCnt++;
		return false;
	}	
	return true;
}


Packet* DropTailQueue :: Deque()
{
	Packet * Pckt;
	if(!PacketQueue.empty())
	{
		Pckt = PacketQueue.front();
		PacketQueue.pop_front();
		CurrentSize--;
		
	}
	
	else
		return NULL;
    
    return Pckt;
}


 unsigned int DropTailQueue ::  GetMaxSize()
 {
	return MaxSize;
 }
 

 unsigned int DropTailQueue :: GetCurrentSize()
 {
	return CurrentSize;
 }

