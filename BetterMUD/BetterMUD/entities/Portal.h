// MUD Programming
// Ron Penton
// (C)2003
// Portal.h - This file contains the portal entity type
// 
// 


#ifndef BETTERMUDPORTAL_H
#define BETTERMUDPORTAL_H

#include <string>
#include <list>
#include "BasicLib/BasicLib.h"
#include "Room.h"
#include "Entity.h"
#include "LogicEntity.h"

namespace BetterMUD
{


class Portal : 
    public LogicEntity,
    public DataEntity,
    public HasRegion
{
public:
    typedef std::list<portalentry> portals;

    // disk access functions
    void Load( std::istream& p_stream );
    void Save( std::ostream& p_stream );

    // add and remove this entity from the game
    void Remove();
    void Add();

    portals::iterator PortalsBegin()            { return m_portals.begin(); }
    portals::iterator PortalsEnd()              { return m_portals.end(); }

protected:

    portals m_portals;          // list of entries
   

};  // end class Portal


}   // end namespace BetterMUD


#endif
