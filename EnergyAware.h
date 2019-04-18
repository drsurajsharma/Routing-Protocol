#include "VirtualRouting.h"
#include "EnergyAwareMsg_m.h"
#include "EnergyAwareControl_m.h"
#include "VirtualMobilityManager.h"
#include "ResourceManager.h"
#include "VirtualApplication.h"

#define NO_LEVEL  -110
#define NO_SINK   -120

using namespace std;

enum PratikMapTimers
{
	SEND_NEIGHBOR_PACKET=1,
	ROUTE_REQUEST_PACKET=2,
	FORWARD_ROUTE_REQUEST_PACKET=3,
	SOURCE_DATA_PACKET=4,
	FORWARD_DATA_PACKT=5,
	PRINT_N_TABLE=6,
	
	SET_SLEEP_STATE=7,
	
	
};
struct addinfo
{
	int ans;
};

class EnergyAware:public VirtualRouting
{
	int reqpkt;
	int des;
	int flag;
	int ctr;
	int s;
	int r;
	int temps;
	int packetsPerNode;
	int totalSNodes;
	int ps;
	int nak;
	string ar;
	string pr;
	string dst;
	string sc;
	int pri;
	int packetSize;
	int rReqPac;
	int currentSourceID;
	double packetSpacing;
	int packetsSent;
	double txInterval_perNode;
	double txInterval_total;
	vector<neighbor> neighborTable;
	int currentSinkID;
	int tmpLevel;
	int currentLevel;
	double tmpx;
	double tmpy;
	double tmpeng;
	double mindis;
	double seconddis;
	int primary;
	int alternate;
	int tmpType;
	int tmpPrimary;
	int tmpAlternate;
	int type;
	bool isSink;
	bool isSource;
	int src;
	int pindex;
	int aindex;
	string sr;
	int dcount;
	int tmpSinkID;
	double initialEnergy;
	int prm;
	int al;
	VirtualMobilityManager *mobilityModule;
	ResourceManager *resMgrModule;
		

 protected:
	//void toNetworkLayer(cMessage *);
	void findPrimary();
	void findNeighbor();
	void calculateDistance();
	void sendNeighbor();
	void sendRouteRequestPacket(int);
	void findAlternate();
	void setStateSleep();
	void sendDataPacket(int);
	void startup();
	void fromApplicationLayer(cPacket *, const char *);
	void fromMacLayer(cPacket *, int, double, double);
	void timerFiredCallback(int);
	void processBufferedPacket();
	void finishSpecific();
};
