enum energyAwareControlDef 
{
	MPRINGS_NOT_CONNECTED = 1;
	MPRINGS_CONNECTED_TO_TREE = 2;
	MPRINGS_TREE_LEVEL_UPDATED = 3;
}

message EnergyAwareRoutingControlMessage 
{
	int multipathRingsRoutingControlMessageKind enum (energyAwareControlDef);
	int sinkID;
	int level;
}
