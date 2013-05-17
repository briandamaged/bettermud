// MUD Programming
// Ron Penton
// (C)2003
// Portal.cpp - This file contains the portal entity type
// 
// 


#include "Portal.h"
#include "../accessors/Accessors.h"

namespace BetterMUD
{

void portalentry::Load( std::istream& p_stream )
{
    std::string temp;
    p_stream >> temp >> startroom;
    p_stream >> temp >> std::ws; std::getline( p_stream, directionname );
    p_stream >> temp >> destinationroom;
}

void portalentry::Save( std::ostream& p_stream )
{
    p_stream << "    [STARTROOM]             " << startroom << "\n";
    p_stream << "    [DIRECTION]             " << directionname << "\n";
    p_stream << "    [DESTROOM]              " << destinationroom << "\n";
}
    
void Portal::Load( std::istream& p_stream )
{
    // find every room that this portal is in at the moment and remove it
    Remove();

    std::string temp;
    p_stream >> temp >> m_region;
    p_stream >> temp >> std::ws; std::getline( p_stream, m_name );
    p_stream >> temp >> std::ws; std::getline( p_stream, m_description );


    // now load all the portals
    m_portals.clear();
    while( BasicLib::extract( p_stream, temp ) != "[/ENTRIES]" )
    {
        portalentry e;
        e.Load( p_stream );
        p_stream >> temp;   // chew up "[/ENTRY]"
        m_portals.push_back( e );
    }

    // load attributes
    m_attributes.Load( p_stream );

    // load my logic module
    m_logic.Load( p_stream, m_id );

    // now insert the portal into every room that it's supposed to be in
    Add();

}


void Portal::Save( std::ostream& p_stream )
{
    p_stream << "[REGION]                " << m_region << "\n";
    p_stream << "[NAME]                  " << m_name << "\n";
    p_stream << "[DESCRIPTION]           " << m_description << "\n";

    // write out the entries
    portals::iterator itr = m_portals.begin();
    while( itr != m_portals.end() )
    {
        p_stream << "[ENTRY]\n";
        itr->Save( p_stream );
        p_stream << "[/ENTRY]\n";
        ++itr;
    }
    p_stream << "[/ENTRIES]\n";

    // save my attributes to disk
    m_attributes.Save( p_stream );

    // save my logic
    m_logic.Save( p_stream );
}



// this removes itself from all the rooms it is in.
void Portal::Remove()
{
    // remove the portal from its region
    if( m_region != 0 )
    {
        region reg( m_region );
        reg.DelPortal( m_id );
    }

    // remove portal from every room its in
    portals::iterator itr = m_portals.begin();
    while( itr != m_portals.end() )
    {
        room r( itr->startroom );
        r.DelPortal(  m_id );
        ++itr;
    }
}

// this adds itself to every room that it is in.
void Portal::Add()
{
    // add the portal to its region
    if( m_region != 0 )
    {
        region reg( m_region );
        reg.AddPortal( m_id );
    }

    // add each entry point to each room now
    portals::iterator itr = m_portals.begin();
    while( itr != m_portals.end() )
    {
        room r( itr->startroom );
        r.AddPortal( m_id );
        ++itr;
    }
}




}   // end namespace BetterMUD


