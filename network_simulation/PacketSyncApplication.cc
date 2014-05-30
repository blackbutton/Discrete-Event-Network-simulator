#include "PacketSyncApplication.h"

PacketSyncApplication::PacketSyncApplication()
{
	totalPacketsReceived=0; 
	totalBytesReceived=0;
	AppType= TRAFFIC_SYNC_APPLICATION;
}


void PacketSyncApplication::Start()
{
}


void PacketSyncApplication::Stop()
{
}


void PacketSyncApplication::Handle(Event *e,Time_t t)
{
}


void PacketSyncApplication::PacketReceive(Packet * p)
{
	totalPacketsReceived++;
	totalBytesReceived += p->count;
}

