//
// Generated file, do not edit! Created by opp_msgc 4.2 from src/node/communication/routing/energyAware/EnergyAwareMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "EnergyAwareMsg_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("energyAwarePacketDef");
    if (!e) enums.getInstance()->add(e = new cEnum("energyAwarePacketDef"));
    e->insert(ENERGYAWARE_NEIGHBOR_PACKET, "ENERGYAWARE_NEIGHBOR_PACKET");
    e->insert(ENERGYAWARE_DATA_PACKET, "ENERGYAWARE_DATA_PACKET");
    e->insert(ENERGYAWARE_ROUTE_REQUEST_PACKET, "ENERGYAWARE_ROUTE_REQUEST_PACKET");
    e->insert(ENERGYAWARE_NAK_PACKET, "ENERGYAWARE_NAK_PACKET");
);

neighbor::neighbor()
{
    nodeID = 0;
    locX = 0;
    locY = 0;
    energy = 0;
    distance = 0;
    nType = 0;
    rssi = 0;
    src = 0;
}

void doPacking(cCommBuffer *b, neighbor& a)
{
    doPacking(b,a.nodeID);
    doPacking(b,a.locX);
    doPacking(b,a.locY);
    doPacking(b,a.energy);
    doPacking(b,a.distance);
    doPacking(b,a.nType);
    doPacking(b,a.rssi);
    doPacking(b,a.src);
}

void doUnpacking(cCommBuffer *b, neighbor& a)
{
    doUnpacking(b,a.nodeID);
    doUnpacking(b,a.locX);
    doUnpacking(b,a.locY);
    doUnpacking(b,a.energy);
    doUnpacking(b,a.distance);
    doUnpacking(b,a.nType);
    doUnpacking(b,a.rssi);
    doUnpacking(b,a.src);
}

class neighborDescriptor : public cClassDescriptor
{
  public:
    neighborDescriptor();
    virtual ~neighborDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(neighborDescriptor);

neighborDescriptor::neighborDescriptor() : cClassDescriptor("neighbor", "")
{
}

neighborDescriptor::~neighborDescriptor()
{
}

bool neighborDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<neighbor *>(obj)!=NULL;
}

const char *neighborDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int neighborDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
}

unsigned int neighborDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *neighborDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "nodeID",
        "locX",
        "locY",
        "energy",
        "distance",
        "nType",
        "rssi",
        "src",
    };
    return (field>=0 && field<8) ? fieldNames[field] : NULL;
}

int neighborDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeID")==0) return base+0;
    if (fieldName[0]=='l' && strcmp(fieldName, "locX")==0) return base+1;
    if (fieldName[0]=='l' && strcmp(fieldName, "locY")==0) return base+2;
    if (fieldName[0]=='e' && strcmp(fieldName, "energy")==0) return base+3;
    if (fieldName[0]=='d' && strcmp(fieldName, "distance")==0) return base+4;
    if (fieldName[0]=='n' && strcmp(fieldName, "nType")==0) return base+5;
    if (fieldName[0]=='r' && strcmp(fieldName, "rssi")==0) return base+6;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+7;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *neighborDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "double",
        "double",
        "double",
        "double",
        "int",
        "double",
        "int",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : NULL;
}

const char *neighborDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int neighborDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    neighbor *pp = (neighbor *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string neighborDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    neighbor *pp = (neighbor *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->nodeID);
        case 1: return double2string(pp->locX);
        case 2: return double2string(pp->locY);
        case 3: return double2string(pp->energy);
        case 4: return double2string(pp->distance);
        case 5: return long2string(pp->nType);
        case 6: return double2string(pp->rssi);
        case 7: return long2string(pp->src);
        default: return "";
    }
}

bool neighborDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    neighbor *pp = (neighbor *)object; (void)pp;
    switch (field) {
        case 0: pp->nodeID = string2long(value); return true;
        case 1: pp->locX = string2double(value); return true;
        case 2: pp->locY = string2double(value); return true;
        case 3: pp->energy = string2double(value); return true;
        case 4: pp->distance = string2double(value); return true;
        case 5: pp->nType = string2long(value); return true;
        case 6: pp->rssi = string2double(value); return true;
        case 7: pp->src = string2long(value); return true;
        default: return false;
    }
}

const char *neighborDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<8) ? fieldStructNames[field] : NULL;
}

void *neighborDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    neighbor *pp = (neighbor *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(EnergyAwareMessage);

EnergyAwareMessage::EnergyAwareMessage(const char *name, int kind) : RoutingPacket(name,kind)
{
    this->EnergyAwarePacketKind_var = 0;
    neighborTable_arraysize = 0;
    this->neighborTable_var = 0;
    this->s_var = 0;
    this->x_var = 0;
    this->y_var = 0;
    this->eng_var = 0;
    this->primary_var = 0;
    this->alternate_var = 0;
    this->type_var = 0;
    this->sinkID_var = 0;
    this->level_var = 0;
    this->pID_var = 0;
    this->currentSource_var = 0;
}

EnergyAwareMessage::EnergyAwareMessage(const EnergyAwareMessage& other) : RoutingPacket(other)
{
    neighborTable_arraysize = 0;
    this->neighborTable_var = 0;
    copy(other);
}

EnergyAwareMessage::~EnergyAwareMessage()
{
    delete [] neighborTable_var;
}

EnergyAwareMessage& EnergyAwareMessage::operator=(const EnergyAwareMessage& other)
{
    if (this==&other) return *this;
    RoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void EnergyAwareMessage::copy(const EnergyAwareMessage& other)
{
    this->EnergyAwarePacketKind_var = other.EnergyAwarePacketKind_var;
    delete [] this->neighborTable_var;
    this->neighborTable_var = (other.neighborTable_arraysize==0) ? NULL : new neighbor[other.neighborTable_arraysize];
    neighborTable_arraysize = other.neighborTable_arraysize;
    for (unsigned int i=0; i<neighborTable_arraysize; i++)
        this->neighborTable_var[i] = other.neighborTable_var[i];
    this->s_var = other.s_var;
    this->x_var = other.x_var;
    this->y_var = other.y_var;
    this->eng_var = other.eng_var;
    this->primary_var = other.primary_var;
    this->alternate_var = other.alternate_var;
    this->type_var = other.type_var;
    this->sinkID_var = other.sinkID_var;
    this->level_var = other.level_var;
    this->pID_var = other.pID_var;
    this->currentSource_var = other.currentSource_var;
}

void EnergyAwareMessage::parsimPack(cCommBuffer *b)
{
    RoutingPacket::parsimPack(b);
    doPacking(b,this->EnergyAwarePacketKind_var);
    b->pack(neighborTable_arraysize);
    doPacking(b,this->neighborTable_var,neighborTable_arraysize);
    doPacking(b,this->s_var);
    doPacking(b,this->x_var);
    doPacking(b,this->y_var);
    doPacking(b,this->eng_var);
    doPacking(b,this->primary_var);
    doPacking(b,this->alternate_var);
    doPacking(b,this->type_var);
    doPacking(b,this->sinkID_var);
    doPacking(b,this->level_var);
    doPacking(b,this->pID_var);
    doPacking(b,this->currentSource_var);
}

void EnergyAwareMessage::parsimUnpack(cCommBuffer *b)
{
    RoutingPacket::parsimUnpack(b);
    doUnpacking(b,this->EnergyAwarePacketKind_var);
    delete [] this->neighborTable_var;
    b->unpack(neighborTable_arraysize);
    if (neighborTable_arraysize==0) {
        this->neighborTable_var = 0;
    } else {
        this->neighborTable_var = new neighbor[neighborTable_arraysize];
        doUnpacking(b,this->neighborTable_var,neighborTable_arraysize);
    }
    doUnpacking(b,this->s_var);
    doUnpacking(b,this->x_var);
    doUnpacking(b,this->y_var);
    doUnpacking(b,this->eng_var);
    doUnpacking(b,this->primary_var);
    doUnpacking(b,this->alternate_var);
    doUnpacking(b,this->type_var);
    doUnpacking(b,this->sinkID_var);
    doUnpacking(b,this->level_var);
    doUnpacking(b,this->pID_var);
    doUnpacking(b,this->currentSource_var);
}

int EnergyAwareMessage::getEnergyAwarePacketKind() const
{
    return EnergyAwarePacketKind_var;
}

void EnergyAwareMessage::setEnergyAwarePacketKind(int EnergyAwarePacketKind)
{
    this->EnergyAwarePacketKind_var = EnergyAwarePacketKind;
}

void EnergyAwareMessage::setNeighborTableArraySize(unsigned int size)
{
    neighbor *neighborTable_var2 = (size==0) ? NULL : new neighbor[size];
    unsigned int sz = neighborTable_arraysize < size ? neighborTable_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        neighborTable_var2[i] = this->neighborTable_var[i];
    neighborTable_arraysize = size;
    delete [] this->neighborTable_var;
    this->neighborTable_var = neighborTable_var2;
}

unsigned int EnergyAwareMessage::getNeighborTableArraySize() const
{
    return neighborTable_arraysize;
}

neighbor& EnergyAwareMessage::getNeighborTable(unsigned int k)
{
    if (k>=neighborTable_arraysize) throw cRuntimeError("Array of size %d indexed by %d", neighborTable_arraysize, k);
    return neighborTable_var[k];
}

void EnergyAwareMessage::setNeighborTable(unsigned int k, const neighbor& neighborTable)
{
    if (k>=neighborTable_arraysize) throw cRuntimeError("Array of size %d indexed by %d", neighborTable_arraysize, k);
    this->neighborTable_var[k] = neighborTable;
}

int EnergyAwareMessage::getS() const
{
    return s_var;
}

void EnergyAwareMessage::setS(int s)
{
    this->s_var = s;
}

double EnergyAwareMessage::getX() const
{
    return x_var;
}

void EnergyAwareMessage::setX(double x)
{
    this->x_var = x;
}

double EnergyAwareMessage::getY() const
{
    return y_var;
}

void EnergyAwareMessage::setY(double y)
{
    this->y_var = y;
}

double EnergyAwareMessage::getEng() const
{
    return eng_var;
}

void EnergyAwareMessage::setEng(double eng)
{
    this->eng_var = eng;
}

int EnergyAwareMessage::getPrimary() const
{
    return primary_var;
}

void EnergyAwareMessage::setPrimary(int primary)
{
    this->primary_var = primary;
}

int EnergyAwareMessage::getAlternate() const
{
    return alternate_var;
}

void EnergyAwareMessage::setAlternate(int alternate)
{
    this->alternate_var = alternate;
}

int EnergyAwareMessage::getType() const
{
    return type_var;
}

void EnergyAwareMessage::setType(int type)
{
    this->type_var = type;
}

int EnergyAwareMessage::getSinkID() const
{
    return sinkID_var;
}

void EnergyAwareMessage::setSinkID(int sinkID)
{
    this->sinkID_var = sinkID;
}

int EnergyAwareMessage::getLevel() const
{
    return level_var;
}

void EnergyAwareMessage::setLevel(int level)
{
    this->level_var = level;
}

int EnergyAwareMessage::getPID() const
{
    return pID_var;
}

void EnergyAwareMessage::setPID(int pID)
{
    this->pID_var = pID;
}

int EnergyAwareMessage::getCurrentSource() const
{
    return currentSource_var;
}

void EnergyAwareMessage::setCurrentSource(int currentSource)
{
    this->currentSource_var = currentSource;
}

class EnergyAwareMessageDescriptor : public cClassDescriptor
{
  public:
    EnergyAwareMessageDescriptor();
    virtual ~EnergyAwareMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(EnergyAwareMessageDescriptor);

EnergyAwareMessageDescriptor::EnergyAwareMessageDescriptor() : cClassDescriptor("EnergyAwareMessage", "RoutingPacket")
{
}

EnergyAwareMessageDescriptor::~EnergyAwareMessageDescriptor()
{
}

bool EnergyAwareMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<EnergyAwareMessage *>(obj)!=NULL;
}

const char *EnergyAwareMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int EnergyAwareMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 13+basedesc->getFieldCount(object) : 13;
}

unsigned int EnergyAwareMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<13) ? fieldTypeFlags[field] : 0;
}

const char *EnergyAwareMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "EnergyAwarePacketKind",
        "neighborTable",
        "s",
        "x",
        "y",
        "eng",
        "primary",
        "alternate",
        "type",
        "sinkID",
        "level",
        "pID",
        "currentSource",
    };
    return (field>=0 && field<13) ? fieldNames[field] : NULL;
}

int EnergyAwareMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='E' && strcmp(fieldName, "EnergyAwarePacketKind")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "neighborTable")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "s")==0) return base+2;
    if (fieldName[0]=='x' && strcmp(fieldName, "x")==0) return base+3;
    if (fieldName[0]=='y' && strcmp(fieldName, "y")==0) return base+4;
    if (fieldName[0]=='e' && strcmp(fieldName, "eng")==0) return base+5;
    if (fieldName[0]=='p' && strcmp(fieldName, "primary")==0) return base+6;
    if (fieldName[0]=='a' && strcmp(fieldName, "alternate")==0) return base+7;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+8;
    if (fieldName[0]=='s' && strcmp(fieldName, "sinkID")==0) return base+9;
    if (fieldName[0]=='l' && strcmp(fieldName, "level")==0) return base+10;
    if (fieldName[0]=='p' && strcmp(fieldName, "pID")==0) return base+11;
    if (fieldName[0]=='c' && strcmp(fieldName, "currentSource")==0) return base+12;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *EnergyAwareMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "neighbor",
        "int",
        "double",
        "double",
        "double",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<13) ? fieldTypeStrings[field] : NULL;
}

const char *EnergyAwareMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "energyAwarePacketDef";
            return NULL;
        default: return NULL;
    }
}

int EnergyAwareMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    EnergyAwareMessage *pp = (EnergyAwareMessage *)object; (void)pp;
    switch (field) {
        case 1: return pp->getNeighborTableArraySize();
        default: return 0;
    }
}

std::string EnergyAwareMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    EnergyAwareMessage *pp = (EnergyAwareMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getEnergyAwarePacketKind());
        case 1: {std::stringstream out; out << pp->getNeighborTable(i); return out.str();}
        case 2: return long2string(pp->getS());
        case 3: return double2string(pp->getX());
        case 4: return double2string(pp->getY());
        case 5: return double2string(pp->getEng());
        case 6: return long2string(pp->getPrimary());
        case 7: return long2string(pp->getAlternate());
        case 8: return long2string(pp->getType());
        case 9: return long2string(pp->getSinkID());
        case 10: return long2string(pp->getLevel());
        case 11: return long2string(pp->getPID());
        case 12: return long2string(pp->getCurrentSource());
        default: return "";
    }
}

bool EnergyAwareMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    EnergyAwareMessage *pp = (EnergyAwareMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setEnergyAwarePacketKind(string2long(value)); return true;
        case 2: pp->setS(string2long(value)); return true;
        case 3: pp->setX(string2double(value)); return true;
        case 4: pp->setY(string2double(value)); return true;
        case 5: pp->setEng(string2double(value)); return true;
        case 6: pp->setPrimary(string2long(value)); return true;
        case 7: pp->setAlternate(string2long(value)); return true;
        case 8: pp->setType(string2long(value)); return true;
        case 9: pp->setSinkID(string2long(value)); return true;
        case 10: pp->setLevel(string2long(value)); return true;
        case 11: pp->setPID(string2long(value)); return true;
        case 12: pp->setCurrentSource(string2long(value)); return true;
        default: return false;
    }
}

const char *EnergyAwareMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        "neighbor",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<13) ? fieldStructNames[field] : NULL;
}

void *EnergyAwareMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    EnergyAwareMessage *pp = (EnergyAwareMessage *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getNeighborTable(i)); break;
        default: return NULL;
    }
}


