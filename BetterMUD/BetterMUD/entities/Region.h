// MUD Programming
// Ron Penton
// (C)2003
// Region.h - This file contains the region entity type,
//            regions contain collections of rooms.
// 
// 


#ifndef BETTERMUDREGION_H
#define BETTERMUDREGION_H

#include <string>
#include "BasicLib/BasicLib.h"
#include "Entity.h"
#include "LogicEntity.h"
#include "Room.h"
#include "Portal.h"

namespace BetterMUD
{



class Region : 
    public LogicEntity,
    public DataEntity,
    public HasCharacters,
    public HasItems,
    public HasRooms,
    public HasPortals
{
public:

    // disk access functions
    void Save( std::ostream& p_stream );
    void Load( std::istream& p_stream );

    std::string& Diskname() { return m_diskname; }
    void SetDiskname( const std::string& p_name )  { m_diskname = p_name; }


protected:
    std::string m_diskname;

};  // end class Region

}   // end namespace BetterMUD


#endif
