//
// Generated file, do not edit! Created by opp_msgc 4.2 from src/node/communication/routing/energyAware/EnergyAwareMsg.msg.
//

#ifndef _ENERGYAWAREMSG_M_H_
#define _ENERGYAWAREMSG_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0402
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include "RoutingPacket_m.h"
// }}



/**
 * Enum generated from <tt>src/node/communication/routing/energyAware/EnergyAwareMsg.msg</tt> by opp_msgc.
 * <pre>
 * enum energyAwarePacketDef {
 * 	ENERGYAWARE_NEIGHBOR_PACKET=1;
 * 	ENERGYAWARE_DATA_PACKET=2;
 * 	ENERGYAWARE_ROUTE_REQUEST_PACKET=3;
 * 	ENERGYAWARE_NAK_PACKET=4;
 * }
 * </pre>
 */
enum energyAwarePacketDef {
    ENERGYAWARE_NEIGHBOR_PACKET = 1,
    ENERGYAWARE_DATA_PACKET = 2,
    ENERGYAWARE_ROUTE_REQUEST_PACKET = 3,
    ENERGYAWARE_NAK_PACKET = 4
};

/**
 * Struct generated from src/node/communication/routing/energyAware/EnergyAwareMsg.msg by opp_msgc.
 */
struct neighbor
{
    neighbor();
    int nodeID;
    double locX;
    double locY;
    double energy;
    double distance;
    int nType;
    double rssi;
    int src;
};

void doPacking(cCommBuffer *b, neighbor& a);
void doUnpacking(cCommBuffer *b, neighbor& a);

/**
 * Class generated from <tt>src/node/communication/routing/energyAware/EnergyAwareMsg.msg</tt> by opp_msgc.
 * <pre>
 * packet EnergyAwareMessage extends RoutingPacket
 * {
 * 	int EnergyAwarePacketKind enum (energyAwarePacketDef);	
 * 	neighbor neighborTable[];
 * 	int s;
 * 	double x;
 * 	double y;
 * 	double eng;
 * 	int primary;
 * 	int alternate;
 * 	int type;
 * 	int sinkID;
 * 	int level;	
 * 	int pID;
 * 	int currentSource;
 * };
 * </pre>
 */
class EnergyAwareMessage : public ::RoutingPacket
{
  protected:
    int EnergyAwarePacketKind_var;
    neighbor *neighborTable_var; // array ptr
    unsigned int neighborTable_arraysize;
    int s_var;
    double x_var;
    double y_var;
    double eng_var;
    int primary_var;
    int alternate_var;
    int type_var;
    int sinkID_var;
    int level_var;
    int pID_var;
    int currentSource_var;

  private:
    void copy(const EnergyAwareMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const EnergyAwareMessage&);

  public:
    EnergyAwareMessage(const char *name=NULL, int kind=0);
    EnergyAwareMessage(const EnergyAwareMessage& other);
    virtual ~EnergyAwareMessage();
    EnergyAwareMessage& operator=(const EnergyAwareMessage& other);
    virtual EnergyAwareMessage *dup() const {return new EnergyAwareMessage(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getEnergyAwarePacketKind() const;
    virtual void setEnergyAwarePacketKind(int EnergyAwarePacketKind);
    virtual void setNeighborTableArraySize(unsigned int size);
    virtual unsigned int getNeighborTableArraySize() const;
    virtual neighbor& getNeighborTable(unsigned int k);
    virtual const neighbor& getNeighborTable(unsigned int k) const {return const_cast<EnergyAwareMessage*>(this)->getNeighborTable(k);}
    virtual void setNeighborTable(unsigned int k, const neighbor& neighborTable);
    virtual int getS() const;
    virtual void setS(int s);
    virtual double getX() const;
    virtual void setX(double x);
    virtual double getY() const;
    virtual void setY(double y);
    virtual double getEng() const;
    virtual void setEng(double eng);
    virtual int getPrimary() const;
    virtual void setPrimary(int primary);
    virtual int getAlternate() const;
    virtual void setAlternate(int alternate);
    virtual int getType() const;
    virtual void setType(int type);
    virtual int getSinkID() const;
    virtual void setSinkID(int sinkID);
    virtual int getLevel() const;
    virtual void setLevel(int level);
    virtual int getPID() const;
    virtual void setPID(int pID);
    virtual int getCurrentSource() const;
    virtual void setCurrentSource(int currentSource);
};

inline void doPacking(cCommBuffer *b, EnergyAwareMessage& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, EnergyAwareMessage& obj) {obj.parsimUnpack(b);}


#endif // _ENERGYAWAREMSG_M_H_
