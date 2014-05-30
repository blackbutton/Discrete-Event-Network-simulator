#include "Packet.h"
#include <iostream>

Packet::Packet()
{
}

Packet::Packet(int source0, int destination0, int count0)
{
	source=source0;
	destination=destination0;
	count=count0;
}

