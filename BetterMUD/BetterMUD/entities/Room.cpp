// MUD Programming
// Ron Penton
// (C)2003
// Room.cpp - This file contains the room entity type
// 
// 


#include "Room.h"
#include "Attributes.h"
#include "../accessors/Accessors.h"

namespace BetterMUD
{


void Room::Load( std::istream& p_stream )
{
    // if room is somewhere, then remove it first
    Remove();

    std::string temp;
    p_stream >> temp >> m_region;
    p_stream >> temp >> std::ws; std::getline( p_stream, m_name );
    p_stream >> temp >> std::ws; std::getline( p_stream, m_description );

    // load attributes
    m_attributes.Load( p_stream );

    // load my logic module
    m_logic.Load( p_stream, m_id );


    Add();
}
    
void Room::Save( std::ostream& p_stream )
{
    p_stream << "[REGION]                " << m_region << "\n";
    p_stream << "[NAME]                  " << m_name << "\n";
    p_stream << "[DESCRIPTION]           " << m_description << "\n";

    // save my attributes to disk
    m_attributes.Save( p_stream );

    // save my logic
    m_logic.Save( p_stream );
}


void Room::Add()
{
    // add the room to its region:
    if( m_region != 0 && m_id != 0 )
    {
        region r( m_region );
        r.AddRoom( m_id );
    }
}

void Room::Remove()
{
    // remove the room from its region
    if( m_region != 0 && m_id != 0 )
    {
        region r( m_region );
        r.DelRoom( m_id );
    }
}

}   // end namespace BetterMUD


