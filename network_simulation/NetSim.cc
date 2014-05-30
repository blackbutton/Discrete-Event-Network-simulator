#include "Application.h"
#include "CommonDefs.h"
#include "DropTailQueue.h"
#include "Handler.h"
#include "NetworkInterface.h"
#include "NetworkLink.h"
#include "Node.h"
#include "OnOffApplication.h"
#include "Packet.h"
#include "PacketSyncApplication.h"
#include "Queue.h"
#include "Simulator.h"

#include <stdio.h>
#include <iostream>
#include <deque>

#define DELAY1 ((double)(0.001))
#define DELAY2 ((double)(0.01))
#define BW10 (10000000)
#define BW100 (100000000)
#define RHO ((double)0.9)

using namespace std;

EventList_t Simulator::evnt_list; 
Time_t Simulator::now =0; 
bool  Simulator::sim_stop = false;
 
vector<Node*> Simulator::Hosts;
vector<Node*> Simulator::Node_list;
 
Simulator *Simulator::instance; 
 
void ConstructTopology()
{
	unsigned int i;
	Node * N;
	for( i=0; i < 16; i++)
	{
		N = new Node(i, NODE_HOST);
		OnOffApplication *OnOff = new OnOffApplication((RHO *(double)BW10),0.5,0.5);
		PacketSyncApplication *PacApp = new PacketSyncApplication;
		OnOff->Start();
		OnOff->AttachToNode(N);
		PacApp->AttachToNode(N);		
		N->AddApplication(OnOff);	
		N->AddApplication(PacApp); 	
		
		Simulator::Node_list.push_back(N);
	}

	for(; i< 28;i++)
	{
		N = new Node(i, NODE_ROUTER);
		Simulator::Node_list.push_back(N);
	}

	Simulator::Node_list[0]->AddNeighbor(Simulator::Node_list[16],DELAY1,BW10);
	Simulator::Node_list[1]->AddNeighbor(Simulator::Node_list[16],DELAY1,BW10);
	
	Simulator::Node_list[2]->AddNeighbor(Simulator::Node_list[17],DELAY1,BW10);
	Simulator::Node_list[3]->AddNeighbor(Simulator::Node_list[17],DELAY1,BW10);

	Simulator::Node_list[4]->AddNeighbor(Simulator::Node_list[18],DELAY1,BW10);
	Simulator::Node_list[5]->AddNeighbor(Simulator::Node_list[18],DELAY1,BW10);

	Simulator::Node_list[6]->AddNeighbor(Simulator::Node_list[19],DELAY1,BW10);
	Simulator::Node_list[7]->AddNeighbor(Simulator::Node_list[19],DELAY1,BW10);

	Simulator::Node_list[8]->AddNeighbor(Simulator::Node_list[20],DELAY1,BW10);
	Simulator::Node_list[9]->AddNeighbor(Simulator::Node_list[20],DELAY1,BW10);

	Simulator::Node_list[10]->AddNeighbor(Simulator::Node_list[21],DELAY1,BW10);
	Simulator::Node_list[11]->AddNeighbor(Simulator::Node_list[21],DELAY1,BW10);

	Simulator::Node_list[12]->AddNeighbor(Simulator::Node_list[22],DELAY1,BW10);
	Simulator::Node_list[13]->AddNeighbor(Simulator::Node_list[22],DELAY1,BW10);

	Simulator::Node_list[14]->AddNeighbor(Simulator::Node_list[23],DELAY1,BW10);
	Simulator::Node_list[15]->AddNeighbor(Simulator::Node_list[23],DELAY1,BW10);

	Simulator::Node_list[16]->AddNeighbor(Simulator::Node_list[25],DELAY1,BW10);
	Simulator::Node_list[17]->AddNeighbor(Simulator::Node_list[25],DELAY1,BW10);

	Simulator::Node_list[18]->AddNeighbor(Simulator::Node_list[26],DELAY1,BW10);
	Simulator::Node_list[19]->AddNeighbor(Simulator::Node_list[26],DELAY1,BW10);

	Simulator::Node_list[20]->AddNeighbor(Simulator::Node_list[27],DELAY1,BW10);
	Simulator::Node_list[21]->AddNeighbor(Simulator::Node_list[27],DELAY1,BW10);

	Simulator::Node_list[22]->AddNeighbor(Simulator::Node_list[24],DELAY1,BW10);
	Simulator::Node_list[23]->AddNeighbor(Simulator::Node_list[24],DELAY1,BW10);

	Simulator::Node_list[24]->AddNeighbor(Simulator::Node_list[25],DELAY2,BW100);
	Simulator::Node_list[24]->AddNeighbor(Simulator::Node_list[26],DELAY2,BW100);
	Simulator::Node_list[24]->AddNeighbor(Simulator::Node_list[27],DELAY2,BW100);

	Simulator::Node_list[25]->AddNeighbor(Simulator::Node_list[26],DELAY2,BW100);
	Simulator::Node_list[25]->AddNeighbor(Simulator::Node_list[27],DELAY2,BW100);

	Simulator::Node_list[26]->AddNeighbor(Simulator::Node_list[27],DELAY2,BW100);

}
	
	
int main()
{
    
  Simulator simulator;
  ConstructTopology();  
  Time_t TimeEnd =(double) 100;
  Simulator::StopAt(TimeEnd);
  unsigned long long TotalSentPcktCnt =0;
  unsigned long long TotalRecvPcktCnt =0;

  for(int i =0; i < 28; i++)
	Simulator::Node_list[i]->ComputeRoutes();



  Simulator::Run();

  for(int i =0; i < 16; i++)
  {
	OnOffApplication *onofapp =(OnOffApplication*) (Simulator::Node_list[i]->getApplication())[0];
	PacketSyncApplication *packsync = (PacketSyncApplication*) (Simulator::Node_list[i]->getApplication())[1];
	TotalSentPcktCnt +=onofapp->SentPcktCnt;
	TotalRecvPcktCnt += packsync->totalPacketsReceived;	
  }

  cout<<"I have schedule to send "<<TotalSentPcktCnt<<"packets"<<endl;
  cout<<"I have received "<<TotalRecvPcktCnt<<"packets"<<endl;
  double efficiency=((double)TotalRecvPcktCnt/TotalSentPcktCnt)*100;
  cout<<"Efficiency"<<efficiency<<endl;
}
