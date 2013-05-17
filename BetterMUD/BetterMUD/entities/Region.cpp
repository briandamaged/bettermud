// MUD Programming
// Ron Penton
// (C)2003
// Region.cpp - This file contains the region entity type,
//              regions contain collections of rooms.
// 
// 


#include "Region.h"

namespace BetterMUD
{


void Region::Load( std::istream& p_stream )
{
    std::string temp;
    p_stream >> temp >> std::ws; std::getline( p_stream, m_name );
    p_stream >> temp >> std::ws; std::getline( p_stream, m_description );


    // load attributes
    m_attributes.Load( p_stream );

    // load my logic module
    m_logic.Load( p_stream, m_id );
}


void Region::Save( std::ostream& p_stream )
{
    p_stream << "[NAME]                  " << m_name << "\n";
    p_stream << "[DESCRIPTION]           " << m_description << "\n";

    // save my attributes to disk
    m_attributes.Save( p_stream );

    // save my logic
    m_logic.Save( p_stream );

}



}   // end namespace BetterMUD


