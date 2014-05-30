#include "Node.h"
#include "Simulator.h"
#include "PacketSyncApplication.h"
#include "Application.h"
#include <stdio.h>
#include <vector>
#include <map>


Node :: Node()
{
}


Node :: Node(unsigned int nodeaddr, Node_Type NType)
: address(nodeaddr), node_type(NType)
{
	if(NType == NODE_HOST)
	Simulator::Hosts.push_back(this);
	

}


void Node :: AddApplication(Application * app)
{
	applications.push_back(app);
}


void Node :: AddInterface(unsigned int neighboraddr,  NetworkInterface *NInt)
{
	interfaces.push_back(NInt);
	IntMap.insert(std::pair<unsigned int, NetworkInterface*>(neighboraddr, NInt));
}


void Node :: AddNeighbor(Node *N, double delay, double datarate )
{
	NetworkInterface * NInter1 = new NetworkInterface;
	NetworkInterface * NInter2 = new NetworkInterface;
	NetworkLink *Link1 = new NetworkLink(delay, datarate);
	NetworkLink *Link2 = new NetworkLink(delay, datarate);

    NMap.insert(std::pair<unsigned int, Node*>(N->getAddress(),N));

	N->NMap.insert(std::pair<unsigned int, Node*>(this->getAddress(),this));
	
	NInter1->AssociateNode(this);
	NInter1->AddP2PLink(Link1);
	Link1->SetPeer(NInter2);
	AddInterface(N->getAddress(),NInter1);

	N->AddInterface(this->getAddress(),NInter2);
	NInter2->AssociateNode(N);
	
	NInter2->AddP2PLink(Link2);
	Link2->SetPeer(NInter1);	
}


void Node :: Send(int count,int dest)
{
	NetworkInterface *NIntr;
	Packet * pckt = new Packet;
	pckt->count = count;
	pckt->source = this->address;
	pckt->destination = dest;

	unsigned int hop_addr;
	hop_addr = nextHopRoutes[dest];
	NIntr = IntMap[hop_addr];
	NIntr->Send(pckt);
	
}


void Node :: Receive(Packet *pckt )
{
	if(pckt->destination == this->address)
	{
		cout << "Packet reached destination" << endl;
		for(int i = 0; i < applications.size(); i++)
		{	
			if(applications[i]->AppType == TRAFFIC_SYNC_APPLICATION)
			{
				PacketSyncApplication * App = (PacketSyncApplication *)applications[i];
				App->PacketReceive(pckt);
				break; 
			}
		}
	}
	else
	{
		NetworkInterface * NIntr;
			unsigned int hop_addr;
			hop_addr = nextHopRoutes[pckt->destination];
			NIntr = IntMap[hop_addr];
		
		NIntr->Send(pckt);		
	}
	
}


void Node::addRoute(unsigned int destN, unsigned int NInterface)
{
    if (nextHopRoutes.find(destN) == nextHopRoutes.end())
    {    
		nextHopRoutes.insert(pair<int,int>(destN,NInterface));
		printf("Addroute condition true\n");
    }
}


void Node::ComputeRoutes()
{
	int numberOfNodes = Simulator::Node_list.size();
	
	if(NMap.size() ==1)
	{
		unsigned int neighborAddress = (NMap.begin()->first);
		Simulator * sim = Simulator::instance;

		std::vector<Node*>::iterator iter = sim->Node_list.begin();
		std::vector<Node*>::iterator iterEnd = sim->Node_list.end();

		while(iter != iterEnd)
		{
			unsigned int nodeAddress = (*iter)->getAddress();
			if(nodeAddress!= address )
			{
				nextHopRoutes.insert(std::pair<int, int>(nodeAddress, neighborAddress));		
			}
			iter++;
		}
	}
	else
	{
		bfs();
	}
}


typedef std::pair<Node*,Node*> bfsQueuePair_t;

void Node::bfs()
{
	std::deque<bfsQueuePair_t> bfsQueue;
	
	bfsQueue.push_back(bfsQueuePair_t(this, this));


	while(!bfsQueue.empty())
	{
		Node * nodeTemp = bfsQueue.front().first;
		Node *inserter = bfsQueue.front().second;
        bfsQueue.pop_front();
		bool needToAdd = false;

		if(nodeTemp == this)
		{
			needToAdd = true;
		}
		else if(nextHopRoutes.find(nodeTemp->getAddress()) == nextHopRoutes.end())
		{
			nextHopRoutes.insert(std::pair<unsigned int, unsigned int>(nodeTemp->getAddress(), inserter->getAddress()));
			needToAdd = true;
		}

		if(needToAdd == true)
		{
			std::map<unsigned int, Node*>::const_iterator iter = (nodeTemp->NMap).begin();
			std::map<unsigned int, Node*>::const_iterator iterEnd = (nodeTemp->NMap).end();

			while(iter != iterEnd)
			{
				Node *foo = (*iter).second;
				if(foo == this)
				{
					iter++;
					continue;
				}
				else if(nextHopRoutes.find(foo->getAddress()) != nextHopRoutes.end())
				{
					iter++;
					continue;
				}
				else
				{
					if(nodeTemp == this)
					{
						inserter = foo;
					}
					bfsQueue.push_back(bfsQueuePair_t(foo, inserter));
					iter++;
				}

			}



		}


	}


}
