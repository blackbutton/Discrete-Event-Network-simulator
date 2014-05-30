# Makefile for NetSim
# ECE8893 Final Project, Fall 2012

OBJECTS = NetSim.o Application.o OnOffApplication.o PacketSyncApplication.o DropTailQueue.o Packet.o NetworkLink.o NetworkInterface.o Node.o Simulator.o


NetSim:	$(OBJECTS)
	g++ -g -o NetSim $(OBJECTS)

clean:
	rm -f $(OBJECTS)


