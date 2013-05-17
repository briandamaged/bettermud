// MUD Programming
// Ron Penton
// (C)2003
// Item.cpp - This file contains the item entity type
// 
// 


#include "Item.h"
#include "../accessors/Accessors.h"

namespace BetterMUD
{


// ============================================================================
//  Item Template Class
// ============================================================================
void ItemTemplate::Load( std::istream& p_stream )
{
    // load all base values first
    std::string temp;
    p_stream >> temp >> std::ws; std::getline( p_stream, m_name );
    p_stream >> temp >> std::ws; std::getline( p_stream, m_description );
    p_stream >> temp >> m_isquantity;
    p_stream >> temp >> m_quantity;

    // load attributes
    m_attributes.Load( p_stream );

    // now load the logics:
    p_stream >> temp;       // chew up the "[LOGICS]" tag
    while( BasicLib::extract( p_stream, temp ) != "[/LOGICS]" )
        m_logics.push_back( temp );
}




std::string Item::Name()
{
    using BasicLib::SearchAndReplace;
    using BasicLib::tostring;

    if( m_isquantity )
        return SearchAndReplace( m_name, "<#>", tostring( m_quantity ) );
    else
        return m_name;
}


// ============================================================================
//  Item Instance Class
// ============================================================================
Item::Item()
{
    m_isquantity = false;
    m_quantity = 1;
}

void Item::LoadTemplate( const ItemTemplate& p_template )
{
    m_templateid = p_template.ID();
    m_name = p_template.Name();
    m_description = p_template.Description();
    m_isquantity = p_template.m_isquantity;
    m_quantity = p_template.m_quantity;
    m_attributes = p_template.m_attributes;

    ItemTemplate::names::const_iterator itr = p_template.m_logics.begin();
    while( itr != p_template.m_logics.end() )
    {
        AddLogic( *itr );
        ++itr;
    }
}



void Item::Load( std::istream& p_stream )
{
    // "remove" it from the game for a moment.
    Remove();

    // load all base values first
    std::string temp;
    p_stream >> temp >> std::ws; std::getline( p_stream, m_name );
    p_stream >> temp >> std::ws; std::getline( p_stream, m_description );
    p_stream >> temp >> m_room;
    p_stream >> temp >> m_region;
    p_stream >> temp >> m_isquantity;
    p_stream >> temp >> m_quantity;

    // load data specific to instances
    p_stream >> temp >> m_templateid;

    // load attributes
    m_attributes.Load( p_stream );

    // load my logic module
    m_logic.Load( p_stream, m_id );

    Add();
}

void Item::Save( std::ostream& p_stream )
{
    p_stream << "[NAME]                  " << m_name << "\n";
    p_stream << "[DESCRIPTION]           " << m_description << "\n";
    p_stream << "[ROOM]                  " << m_room << "\n";
    p_stream << "[REGION]                " << m_region << "\n";
    p_stream << "[ISQUANTITY]            " << m_isquantity << "\n";
    p_stream << "[QUANTITY]              " << m_quantity << "\n";
    p_stream << "[TEMPLATEID]            " << m_templateid << "\n";

    // save my attributes to disk
    m_attributes.Save( p_stream );

    // save my logic
    m_logic.Save( p_stream );
}


// functions to add and remove a character "from the game"
void Item::Add()
{
    // when regions are 0, that means the item is on a character
    if( m_region == 0 )
    {
        character c( m_room );
        c.AddItem( m_id );
    }
    else
    {
        region reg( m_region );
        reg.AddItem( m_id );

        room r( m_room );
        r.AddItem( m_id );
    }
}

void Item::Remove()
{
    // just return if the room is 0, that means the item hasn't been loaded yet
    if( m_room == 0 )
        return;


    // when regions are 0, that means the item is on a character
    if( m_region == 0 )
    {
        character c( m_room );
        c.DelItem( m_id );
    }
    else
    {
        region reg( m_region );
        reg.DelItem( m_id );

        room r( m_room );
        r.DelItem( m_id );
    }
}


}   // end namespace BetterMUD

