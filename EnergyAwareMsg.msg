cplusplus {{
#include "RoutingPacket_m.h"
}}

enum energyAwarePacketDef {
	ENERGYAWARE_NEIGHBOR_PACKET=1;
	ENERGYAWARE_DATA_PACKET=2;
	ENERGYAWARE_ROUTE_REQUEST_PACKET=3;
	ENERGYAWARE_NAK_PACKET=4;
}


class RoutingPacket;
struct neighbor
{
	//string s;	
	int nodeID;
	double locX;
	double locY;
	double energy;
	double distance;
	int nType;
	double rssi;
	int src;
	
};

packet EnergyAwareMessage extends RoutingPacket
{
	int EnergyAwarePacketKind enum (energyAwarePacketDef);	
	neighbor neighborTable[];
	int s;
	double x;
	double y;
	double eng;
	int primary;
	int alternate;
	int type;
	int sinkID;
	int level;	
	int pID;
	int currentSource;
};

