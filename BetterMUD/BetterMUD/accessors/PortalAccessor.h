// MUD Programming
// Ron Penton
// (C)2003
// PortalAccessor.h - This file contains the portal accessor class
// 
// 


#ifndef BETTERMUDPORTALACCESSOR_H
#define BETTERMUDPORTALACCESSOR_H

#include <set>
#include <list>
#include "../entities/Entity.h"
#include "../scripts/Logic.h"
#include "AccessorMacros.h"

namespace BetterMUD
{

// forward declaration
class Portal;

// Accessor
class portal
{
public:
    typedef std::list<portalentry> portals;


    ENTITYHEADERS( portal );
    HASREGIONHEADERS;
    HASDATABANKHEADERS;
    HASLOGICHEADERS;


    // iterator functions:
    void BeginPath();
    entityid CurrentStart();
    std::string CurrentDirection();
    entityid CurrentEnd();
    void NextPath();
    bool IsValidPath();

    // These functions seek the iterator to the exit that matches a specific
    // starting or ending point
    void SeekStartRoom( entityid p_room );
    void SeekEndRoom( entityid p_room );

protected:
    Portal* m_portal;
    
    portals::iterator m_portalitr;
};

}   // end namespace BetterMUD


#endif
