// MUD Programming
// Ron Penton
// (C)2003
// RoomAccessor.cpp - This file contains the room accessor class
// 
// 


#include "PortalAccessor.h"
#include "../databases/PortalDatabase.h"

namespace BetterMUD
{


ENTITYIMPLEMENTATIONS( portal, m_portal, PortalDB );
HASREGIONIMPLEMENTATIONS( portal, m_portal );
HASDATABANKIMPLEMENTATIONS( portal, m_portal );
HASLOGICIMPLEMENTATIONS( portal, m_portal );


// iterator functions:
void portal::BeginPath()                            { m_portalitr = m_portal->PortalsBegin(); }
entityid portal::CurrentStart()                     { return m_portalitr->startroom; }
std::string portal::CurrentDirection()              { return m_portalitr->directionname; }
entityid portal::CurrentEnd()                       { return m_portalitr->destinationroom; }
void portal::NextPath()                             { ++m_portalitr; }
bool portal::IsValidPath()                          { return m_portalitr != m_portal->PortalsEnd(); }


// These functions seek the iterator to the exit that matches a specific
// starting or ending point
void portal::SeekStartRoom( entityid p_room )
{
    BeginPath();
    while( IsValidPath() )
    {
        // exit out when you find a match
        if( CurrentStart() == p_room )
            return;
        NextPath();
    }
}

void portal::SeekEndRoom( entityid p_room )
{
    BeginPath();
    while( IsValidPath() )
    {
        // exit out when you find a match
        if( CurrentEnd() == p_room )
            return;
        NextPath();
    }
}




}   // end namespace BetterMUD
