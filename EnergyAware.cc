#include "EnergyAware.h"

Define_Module(EnergyAware);

void EnergyAware::startup()
{
	packetSpacing = (double)par("packetSpacing") / 1000.0;
	//trace()<<"packetSpacing = "<<packetSpacing;
	packetsPerNode = par("packetsPerNode");
	packetSize = par("packetSize");
	reqpkt = 0;
	s=0;
	temps = -1;
	al=0;
	prm=0;
	r=0;
	ctr = 0;
	flag = 0;
	des = 0;
	//trace()<<((rand() % 10000) / 10000.0);
	
	 
	
	cModule *appModule = getParentModule()->getParentModule()->getSubmodule("Application");
	mobilityModule = check_and_cast <VirtualMobilityManager*>(getParentModule()->getParentModule()->getSubmodule("MobilityManager")); 
	resMgrModule = check_and_cast <ResourceManager*>(getParentModule()->getParentModule()->getSubmodule("ResourceManager")); 
	
	if (appModule->hasPar("isSink"))
		isSink = appModule->par("isSink");
	else
		opp_error("\nMultiPathRings routing has to be used with an application that defines the parameter isSink");

	if(isSink)
	{	
		type=1;
		currentSinkID=self;
		currentLevel=tmpLevel=0;
	}
	else
	{
		type=0;
		currentLevel=tmpLevel=NO_LEVEL;
	}
		dcount = 0;
	packetsSent=0;
	rReqPac=0;
	totalSNodes=getParentModule()->getParentModule()->getParentModule()->par("numNodes");
	// int random_integer = rand()%totalSNodes;
	//trace() << random_integer;
	//trace()<< self <<"has " << mobilityModule->getLocation().x<<" "<<mobilityModule->getLocation().y;
	isSource=appModule->par("isSource");
	if(isSource)
	{
		currentSourceID=self;
		type =1;
	}
	else
		currentSourceID=NO_LEVEL;

	initialEnergy=resMgrModule->par("initialEnergy");	
	
	neighborTable.clear();
	nak =0;
	
	tmpType=tmpPrimary=tmpAlternate=primary=alternate=NO_LEVEL;

	txInterval_perNode = packetsPerNode * packetSpacing;
	txInterval_total = (txInterval_perNode * totalSNodes);
	double startTxTime = txInterval_perNode * self;
	
	//trace()<<"startTxTime = "<<startTxTime;
	
	//setTimer(SEND_NEIGHBOR_PACKET,startTxTime);
	setTimer(SEND_NEIGHBOR_PACKET,0);
	if(isSink){
		setTimer(ROUTE_REQUEST_PACKET,10+((rand() % 10000) / 10000.0)+10);
	}
	//setTimer(ROUTE_REQUEST_PACKET,50+((rand() % 10000) / 10000.0));
	//setTimer(SOURCE_DATA_PACKET,110);
	
	//setTimer(SET_SLEEP_STATE,75+((rand() % 10000) / 10000.0));	
	//setTimer(SOURCE_DATA_PACKET,150);
	//if(isSink)
	//	sendNeighbor();
	//setTimer(PRINT_N_TABLE,500+self);
}

/*void EnergyAware::sendNeighbor()
{
	if(packetsSent>packetsPerNode)
		{
			setTimer(ROUTE_REQUEST_PACKET,packetSpacing*100);
			//trace()<<self<<" has reached here at time ="<<getTimer(SEND_NEIGHBOR_PACKET);			
			//break;
			
		}
		trace()<<"hello i m here";
		
		EnergyAwareMessage *neighborPkt =new EnergyAwareMessage("EnergyAware Neighbor Discovery packet", NETWORK_LAYER_PACKET);
		neighborPkt->setEnergyAwarePacketKind(ENERGYAWARE_NEIGHBOR_PACKET);
	
		neighborPkt->setSource(SELF_NETWORK_ADDRESS);
		neighborPkt->setDestination(BROADCAST_NETWORK_ADDRESS);
	
		neighborPkt->setX(mobilityModule->getLocation().x);
		neighborPkt->setY(mobilityModule->getLocation().y);
		packetsSent++;	

		setTimer(SEND_NEIGHBOR_PACKET,packetSpacing*10);
		toMacLayer(neighborPkt, BROADCAST_MAC_ADDRESS);
}*/

void EnergyAware::setStateSleep()
{
	//trace()<<"hahaha";
	//toNetworkLayer(createRadioCommand(SET_STATE, SLEEP));
	send(createRadioCommand(SET_STATE, SLEEP), "toMacModule");
}


void EnergyAware::calculateDistance()
{
	//trace()<<self<<" has reached calculate distance";
	for(int i=0;i<(int)neighborTable.size();i++)
	{
		neighborTable[i].distance=sqrt(pow((100-neighborTable[i].locX),2)+pow((100-neighborTable[i].locY),2));
		//trace()<<self <<"neighbor  "<<neighborTable[i].nodeID<<" "<<neighborTable[i].distance;
	}
}





void EnergyAware::findPrimary()
{
	if(prm ==0){
	//trace()<<self<<" has reached find primary";
	mindis=neighborTable[0].distance;
	primary=neighborTable[0].nodeID;
	
		
	for(int i=1;i<(int)neighborTable.size();i++)
	{
		
		if(neighborTable[i].distance<mindis)
		{ 
			mindis=neighborTable[i].distance;
			primary= neighborTable[i].nodeID;
			pindex=i;
			
			
		}
		
	}
	prm++;
	}
	//trace()<<self<<" has mindis="<<mindis<<" with neighbornode = and primary ="<<primary;
	sendRouteRequestPacket(primary);
	
}


void EnergyAware::findAlternate()
{

	if(al == 0){
//trace()<<self<<" has reached find alternate";
	if(pindex==0)
	{
		seconddis=neighborTable[1].distance;
		alternate= neighborTable[1].nodeID;
		aindex=1;
	}
	else
	{
		seconddis=neighborTable[0].distance;
		alternate= neighborTable[0].nodeID;
		aindex=0;
	}
	//trace()<<self<<" has alternate = "<<alternate;

	for(int i=0;i<(int)neighborTable.size();i++)
	{
		
		if(neighborTable[i].distance< seconddis && pindex !=i)
		{ 
			seconddis=neighborTable[i].distance;
			alternate= neighborTable[i].nodeID;
			aindex=i;
		
		}
	}
	al++;
	}
	//trace()<<self<<" has mindis="<<seconddis<<" with neighbornode = and alternate ="<<alternate;
	sendRouteRequestPacket(alternate);
	
}


void EnergyAware::sendRouteRequestPacket(int destination)
{
		stringstream out;
		out<<destination;
		string dst = out.str();
		int c=0;
		
		//trace()<<self<<" has reached here with destination ="<<destination;
		//while(c++<10){
		
		EnergyAwareMessage *routeRequestpkt=new EnergyAwareMessage("EnergyAware Route Request Packet",NETWORK_LAYER_PACKET);
		
		routeRequestpkt->setEnergyAwarePacketKind(ENERGYAWARE_ROUTE_REQUEST_PACKET);
		routeRequestpkt->setSource(SELF_NETWORK_ADDRESS);
		//routeRequestpkt->setDestination(BROADCAST_NETWORK_ADDRESS);
		routeRequestpkt->setDestination(dst.c_str());
		routeRequestpkt->setPrimary(primary);
		
		routeRequestpkt->setAlternate(alternate);
		routeRequestpkt->setType(type);
		
		routeRequestpkt->setSinkID(currentSinkID);
		routeRequestpkt->setLevel(currentLevel);
		
		//setTimer(FORWARD_ROUTE_REQUEST_PACKET,packetSpacing*10);
		//toMacLayer(routeRequestpkt,BROADCAST_MAC_ADDRESS);
		toMacLayer(routeRequestpkt,destination);
		//}
		

}

void EnergyAware::findNeighbor()
{
	
	//int des,flag = 0;
	if(ctr == 0){
	
	for(int i=0;i<(int)neighborTable.size();i++)
	{
				
		if(neighborTable[i].nType==1)
		{
			//trace()<<"self1="<<self<< " neighbor node= "<<neighborTable[i].nodeID;
			flag=1;
			ctr++;
			des = neighborTable[i].nodeID;
			
			//dataPkt->setPID(neighborTable[i].nodeID);
			//out<<neighborTable[i].nodeID;
			 //dst = out.str();

			//dataPkt->setDestination(dst.c_str());
			 
			break;
		}
	}
	
	if(flag == 0)
	{
		for(int i=0;i<(int)neighborTable.size();i++)
		{
			if(neighborTable[i].nType==2)
			{
				//trace()<<"self2="<<self<< " neighbor node= "<<neighborTable[i].nodeID;
				flag=1;
				ctr++;
				des = neighborTable[i].nodeID;
				//dataPkt->setPID(neighborTable[i].nodeID);
				//out<<neighborTable[i].nodeID;
				 //dst = out.str();
	
				//dataPkt->setDestination(dst.c_str());
				//destination = neighborTable[i].nodeID;

				break;
			}
		}
	}
	
	if(flag == 0)
	{	trace()<<"Error no path to sink.....";
	}
	else
		sendDataPacket(des);
	}
	else
		sendDataPacket(des);
	
	//else if(ctr >0){
		//sendDataPacket(destination);}
	//else
		//trace()<<"Error no path to sink.....";
		//toMacLayer(dataPkt,destination);
}

void EnergyAware::sendDataPacket(int destination)
{
	//trace()<<"hello I have reached here";
		stringstream out;
		string dst;
		out<<destination;
		dst = out.str();
	
		
	//trace()<<self<<"has reached senddatapacket";
	dcount = 0;
	while(dcount<=1){
	EnergyAwareMessage *dataPkt=new EnergyAwareMessage("EnergyAware Data Packet",NETWORK_LAYER_PACKET);
	dataPkt->setEnergyAwarePacketKind(ENERGYAWARE_DATA_PACKET);
	dataPkt->setSource(SELF_NETWORK_ADDRESS);
	dataPkt->setPID(destination);
	dataPkt->setS(s);
	//dataPkt->setDestination(BROADCAST_NETWORK_ADDRESS);
	dataPkt->setDestination(dst.c_str());
	dataPkt->setCurrentSource(currentSourceID);
	dcount++;
	if(s == 1)
		trace()<<"pratik started sendng data";
	toMacLayer(dataPkt,destination);
	}


	
	/*for(int i=0;i<(int)neighborTable.size();i++)
	{
				
		if(neighborTable[i].nType==1)
		{
			//trace()<<"self1="<<self<< " neighbor node= "<<neighborTable[i].nodeID;
			flag=1;
			ctr++;
			dataPkt->setPID(neighborTable[i].nodeID);
			out<<neighborTable[i].nodeID;
			 dst = out.str();

			dataPkt->setDestination(dst.c_str());
			destination = neighborTable[i].nodeID; 
			break;
		}
	}
	if(flag == 0)
	{
		for(int i=0;i<(int)neighborTable.size();i++)
		{
			if(neighborTable[i].nType==2)
			{
				//trace()<<"self2="<<self<< " neighbor node= "<<neighborTable[i].nodeID;
				flag=1;
				ctr++;
				//dataPkt->setPID(neighborTable[i].nodeID);
				out<<neighborTable[i].nodeID;
				 dst = out.str();
	
				dataPkt->setDestination(dst.c_str());
				destination = neighborTable[i].nodeID;

				break;
			}
		}
	}
	if(flag == 0)
		trace()<<"Error no path to sink.....";
	else
		toMacLayer(dataPkt,destination);
		//toMacLayer(dataPkt,destination);
	dcount++;
	//setTimer(FORWARD_DATA_PACKT,5);
	}*/
	

	/*else if(flag==0)
	{
		out<<src;
		dst=out.str();		

		EnergyAwareMessage *nakPkt =new EnergyAwareMessage("EnergyAware negitive ack packet", NETWORK_LAYER_PACKET);
		nakPkt->setEnergyAwarePacketKind(ENERGYAWARE_NAK_PACKET);
	
		nakPkt->setSource(SELF_NETWORK_ADDRESS);
		
		nakPkt->setDestination(dst.c_str());
	
		//nakPkt->setX(mobilityModule->getLocation().x);
		//nakPkt->setY(mobilityModule->getLocation().y);
		//packetsSent++;	

		//setTimer(SEND_NEIGHBOR_PACKET,packetSpacing);
		toMacLayer(nakPkt, BROADCAST_MAC_ADDRESS);
		//trace()<<"hello "<<self<<" has reached here";
		//sendNeighbor();
		trace()<<"Error no path to sink!!!!!!";
		//return;
	}
	//trace()<<self<<"has reached senddatapacket";
	//dcount++;*/
		
}



void EnergyAware::timerFiredCallback(int index)
{
	switch(index)
	{
		
		case SEND_NEIGHBOR_PACKET:
		{
			//trace()<<"hello "<<self<<" is here";
		
		if(packetsSent==5)
		{
			/*trace()<<self<<" has reached here at time ="<<getTimer(SEND_NEIGHBOR_PACKET);
			setTimer(ROUTE_REQUEST_PACKET,packetSpacing*100);*/
				
						
			break;
			
		}
		
		EnergyAwareMessage *neighborPkt =new EnergyAwareMessage("EnergyAware Neighbor Discovery packet", NETWORK_LAYER_PACKET);
		neighborPkt->setEnergyAwarePacketKind(ENERGYAWARE_NEIGHBOR_PACKET);
	
		neighborPkt->setSource(SELF_NETWORK_ADDRESS);
		neighborPkt->setDestination(BROADCAST_NETWORK_ADDRESS);
	
		neighborPkt->setX(mobilityModule->getLocation().x);
		neighborPkt->setY(mobilityModule->getLocation().y);
		packetsSent++;	

		setTimer(SEND_NEIGHBOR_PACKET,packetSpacing +((rand() % 10000) / 10000.0));
		toMacLayer(neighborPkt, BROADCAST_MAC_ADDRESS);
		//trace()<<"hello "<<self<<" has reached here";
		//sendNeighbor();
		break;
		}
		
		

		case ROUTE_REQUEST_PACKET:
		{
		
			if(isSink)
			{
				if(reqpkt==5)
				{
					//cancelTimer(ROUTE_REQUEST_PACKET);
					//setStateSleep();
					break;
				}
				cancelTimer(SEND_NEIGHBOR_PACKET);				
				trace()<<"sink = "<<self <<"has reached here";
				calculateDistance();			
				findPrimary();
				findAlternate();
				reqpkt++;
				
				//sendRouteRequestPacket();
				//setTimer(FORWARD_ROUTE_REQUEST_PACKET,packetSpacing*10);
				
			}
			break;

		}
		

		case FORWARD_ROUTE_REQUEST_PACKET:
		{
			if(isSource)
			{
				setTimer(SOURCE_DATA_PACKET,packetSpacing*100+(((rand()) % 10000) / 10000.0));
				break;
			}	
			//trace()<<self<<" haha "<<currentLevel<<" and ntype = "<<type;
			
				if(reqpkt==5)
				{
					//cancelTimer(ROUTE_REQUEST_PACKET);
					//cancelTimer(FORWARD_ROUTE_REQUEST_PACKET);
					//setStateSleep();
					break;}
				//trace()<<"Sink has "<<resMgrModule->getRemainingEnergy();
				calculateDistance();
			if(type == 1)
			{
				findPrimary();
				findAlternate();
				reqpkt++;
			}
			else if(type == 2)
			{
				findPrimary();
				reqpkt++;
			}
			//else
			//setTimer(FORWARD_ROUTE_REQUEST_PACKET,packetSpacing*20);
			//sendRouteRequestPacket();
			
			break;		
		}
		
		case SOURCE_DATA_PACKET:
		{
			if(isSource)
			{
				//trace()<<self<<" has reached here sendDataPacket()";
				s++;
				//trace()<<"Sink has "<<resMgrModule->getRemainingEnergy();
				findNeighbor();
				//sendDataPacket();
				
			}
			setTimer(SOURCE_DATA_PACKET,1+(((rand()) % 10000) / 10000.0));
			break;
		}
		/*case FORWARD_DATA_PACKT:
		{
			if(pri == self && !isSink){
			//trace()<<self<<" has reached here";
			findNeighbor();
			}
			//sendDataPacket();}
			//trace()<<"Sink has "<<resMgrModule->getRemainingEnergy();
			break;
		}*/
				

		case PRINT_N_TABLE:
		{
			//trace()<<self<<" has "<<type<<" and level="<<currentLevel ;
			trace()<<self<<" "<<mobilityModule->getLocation().x<<" "<<mobilityModule->getLocation().y;
			//trace()<<"currentSinkID = "<<currentSinkID;
			trace()<<"packetssent="<<packetsSent;
		

			for(int i=0;i<(int)neighborTable.size();i++)
			 {
				trace()<<"neighborTable["<<i<<"].locX"<<neighborTable[i].locX;
				trace()<<"neighborTable["<<i<<"].locY"<<neighborTable[i].locY;				
				trace()<<"neighborTable["<<i<<"].nodeID"<<neighborTable[i].nodeID;
				//trace()<<"neighborTable["<<i<<"].rssi"<<neighborTable[i].rssi;
				trace()<<"neighborTable["<<i<<"].nType"<<neighborTable[i].nType;
			}
		break;
		}
		

		case SET_SLEEP_STATE: 
		{
			cancelTimer(ROUTE_REQUEST_PACKET);
			cancelTimer(FORWARD_ROUTE_REQUEST_PACKET);
			if(type!=1)
			{
				//trace()<<"hello";				
				setStateSleep();
			}
			break;
		}
			
	}
	
}



void EnergyAware::fromApplicationLayer(cPacket * pkt, const char *destination)
{
	string dst(destination);
	
}


void EnergyAware::fromMacLayer(cPacket * pkt, int macAddress, double rssi, double lqi)
{
	EnergyAwareMessage *rcvPacket = dynamic_cast <EnergyAwareMessage*>(pkt);
	src=atoi(rcvPacket->getSource());
	//sr=rcvPacket->getSource();
	//src=atoi(sr);
	
	
	tmpx=rcvPacket->getX();
	tmpy=rcvPacket->getY();
	switch(rcvPacket->getEnergyAwarePacketKind())
	{
		case ENERGYAWARE_NEIGHBOR_PACKET:{
						//trace()<<self<<" has received the neighbor packet from "<<src<<" and rssi ="<<rssi;	
						int i=0,pos=-1;
						int tableSize=(int)neighborTable.size();
  
						for(i=0;i<tableSize;i++)
							if(neighborTable[i].nodeID==src)
								pos=i;
		
						if(pos==-1)
						{
							neighbor neighborRec;
							neighborRec.nodeID=src;
							neighborRec.locX=tmpx;
							neighborRec.locY=tmpy;
							neighborRec.rssi=rssi;
							neighborTable.push_back(neighborRec);
							break;
						}
						break;
					 }
		case ENERGYAWARE_ROUTE_REQUEST_PACKET:
		{
			
			//tmpSinkID=rcvPacket->getSinkID();			
			//currentSinkID=rcvPacket->getSinkID();
			tmpType=rcvPacket->getType();
			tmpLevel=rcvPacket->getLevel();

			tmpPrimary=rcvPacket->getPrimary();
			tmpAlternate=rcvPacket->getAlternate();
		//trace()<<self<<" received the route request from"<< src<<" and tmpPrimary ="<<tmpPrimary<<" and tmpAlternate ="<<tmpAlternate;
			
			
			//if(tmpLevel==NO_LEVEL || tmpLevel>rcvPacket->getLevel())
			if(tmpLevel!=NO_LEVEL &&(currentLevel == NO_LEVEL || tmpLevel < currentLevel))
			{
				
				//tmpLevel = rcvPacket->getLevel();
				tmpSinkID=rcvPacket->getSinkID();	
				
				if(tmpType==1)
				{			
					
					//if(self==tmpPrimary && tmpLevel != NO_LEVEL )
					if(self == tmpPrimary)
					{
						//trace()<<self<<" is primary and has route request from "<<src<<" and tmpType ="<<tmpType;
						//trace()<<self<<" has route request from "<<src<<" and tmpType = 1";
						
						type=1;
						if(currentLevel == NO_LEVEL)
							currentLevel=tmpLevel+1;							
						else if(tmpLevel<currentLevel)
							currentLevel=tmpLevel+1;
						currentSinkID=rcvPacket->getSinkID();
						//trace()<<self<<" has reached here with source =" <<src<<"and current level="<<currentLevel<< "and type ="<<type;
					}
								
					//if(self==tmpAlternate  && tmpLevel != NO_LEVEL )
					if(self == tmpAlternate)
					{
						//trace()<<self<<" is alternate and has route request from "<<src<<" and tmpType ="<<tmpType;
						if(type!=1)
							type=2;
						if(currentLevel == NO_LEVEL)
							currentLevel=tmpLevel+1;							
						else if(tmpLevel<currentLevel)
							currentLevel=tmpLevel+1;
						//trace()<<self<<" is alternate has reached here with source =" <<src<<"and current level="<<currentLevel;
					}
				}
				else if(tmpType==2)
				{
					if(self==tmpPrimary && type!=1)
					{
						//trace()<<self<<" has route request from "<<src<<" and tmpType ="<<tmpType;
						type=2;
						if(currentLevel == NO_LEVEL)
							currentLevel=tmpLevel+1;							
						else if(tmpLevel<currentLevel)
							currentLevel=tmpLevel+1;
						currentSinkID=rcvPacket->getSinkID();
					}
				}
				for(int i=0;i<(int)neighborTable.size();i++)
				{
					if(src==neighborTable[i].nodeID && currentLevel > tmpLevel )
					{
						
						neighborTable[i].nType=tmpType;	
						//trace()<<self<<" has reached the neighbor table with nodeid ="<<neighborTable[i].nodeID<<" and nType ="<<neighborTable[i].nType;
						
						break;
					}
				}
				/*if(type == 1)
				{
					calculateDistance();
					findPrimary();
					findAlternate();
				}
				else if(type == 2)
				{
					calculateDistance();
					findPrimary();
				}*/			
			}
	setTimer(FORWARD_ROUTE_REQUEST_PACKET,packetSpacing+((rand() % 10000) / 10000.0));
	break;
						
	}
	


	case ENERGYAWARE_DATA_PACKET:
	{
		//string dst(rcvPacket->getDestination());
		//string sc(rcvPacket->getSource());
		
		//trace()<<"s ="<< rcvPacket->getS()<<" and temps ="<< temps<<" and self ="<<self;		
		pri=rcvPacket->getPID();
		s=rcvPacket->getS();
		if(pri==self)
		{ 
				if(resMgrModule->getRemainingEnergy()<1)
					trace()<<"Network down";
			
				if(isSink && temps < rcvPacket->getS() )
				{
					//trace()<<"rcvPacket->getS() = "<<rcvPacket->getS() ;
					temps = rcvPacket->getS();
					r++;
					if( r== 1)
						trace()<<"received the 1st packet";
					//trace()<<" i am sink and src ="<<src;
				}
				//trace()<<self<<" received the data packet from "<< src;
				//trace()<<"pri ="<<pri;
				if(!isSink)
					findNeighbor();
				//setTimer(FORWARD_DATA_PACKT,packetSpacing*10);
				//break;
				
				
		}
		//else
			//setTimer(FORWARD_DATA_PACKT,packetSpacing*10);
			break;
			
	
	}
	/*case ENERGYAWARE_NAK_PACKET:
	{
		nak=1;
		sendDataPacket();
		break;
		
	}*/
	}
}






void EnergyAware::finishSpecific()
{
	if(isSink || isSource)
	trace()<<"Total sent by source = "<<s<<" and total received by sink is = "<<r;
}

