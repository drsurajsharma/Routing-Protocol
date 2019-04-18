package node.communication.routing.energyAware;

simple EnergyAware like node.communication.routing.iRouting
{
parameters:
	
	bool collectTraceInfo = default (true);
	int maxNetFrameSize = default (0);					// bytes, 0 means no limit
	int netBufferSize = default (32);					// number of messages
	int netDataFrameOverhead = default (14);			// bytes

	
	int packetSpacing = default (100);	// in ms
	int packetsPerNode = default (25);
	int packetSize = default (32);	// in bytes

	bool isSink = default (false);
	bool isSource = default(false);
gates:
 	output toCommunicationModule;
	output toMacModule;
	input fromCommunicationModule;
	input fromMacModule;
	input fromCommModuleResourceMgr;
}




