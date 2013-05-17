// MUD Programming
// Ron Penton
// (C)2003
// Character.cpp - This file contains the character entity type
// 
// 


#include "Character.h"
#include "../databases/CommandDatabase.h"
#include "../databases/AccountDatabase.h"
#include "../databases/ItemDatabase.h"
#include "../Game.h"

namespace BetterMUD
{

// ============================================================================
//  Character Template Class
// ============================================================================
void CharacterTemplate::Load( std::istream& p_stream )
{
    // load all base values first
    std::string temp;
    p_stream >> temp >> std::ws; std::getline( p_stream, m_name );
    p_stream >> temp >> std::ws; std::getline( p_stream, m_description );

    // load attributes
    m_attributes.Load( p_stream );

    // now load the commands:
    p_stream >> temp;       // chew up the "[COMMANDS]" tag
    while( BasicLib::extract( p_stream, temp ) != "[/COMMANDS]" )
        m_commands.push_back( temp );

    // now load the logics:
    p_stream >> temp;       // chew up the "[LOGICS]" tag
    while( BasicLib::extract( p_stream, temp ) != "[/LOGICS]" )
        m_logics.push_back( temp );
}


// ============================================================================
//  Character Instance Class
// ============================================================================
Character::Character()
{
    m_account = 0;
    m_loggedin = false;
    m_quiet = false;
    m_verbose = true;
}

Character::~Character()
{
    // delete all the players commands
    commands::iterator itr = m_commands.begin();
    while( itr != m_commands.end() )
    {
        delete *itr;
        *itr = 0;
        ++itr;
    }
}




void Character::LoadTemplate( const CharacterTemplate& p_template )
{
    m_templateid = p_template.ID();
    m_name = p_template.Name();
    m_description = p_template.Description();
    m_attributes = p_template.m_attributes;

    CharacterTemplate::names::const_iterator itr = p_template.m_commands.begin();
    while( itr != p_template.m_commands.end() )
    {
        AddCommand( *itr );
        ++itr;
    }

    itr = p_template.m_logics.begin();
    while( itr != p_template.m_logics.end() )
    {
        AddLogic( *itr );
        ++itr;
    }
}


void Character::Load( std::istream& p_stream )
{
    // remove the character from the game first, but not if it's a player
    // who is logged out
    if( !IsPlayer() || IsLoggedIn() )
        Remove();

    // load all base values first
    std::string temp;
    p_stream >> temp >> std::ws; std::getline( p_stream, m_name );
    p_stream >> temp >> std::ws; std::getline( p_stream, m_description );
    p_stream >> temp >> m_room;
    p_stream >> temp >> m_region;

    // load data specific to instances
    p_stream >> temp >> m_templateid;
    p_stream >> temp >> m_account;
    p_stream >> temp >> m_quiet;
    p_stream >> temp >> m_verbose;

    // load attributes
    m_attributes.Load( p_stream );


    // load commands
    p_stream >> temp;       // chew up the "[COMMANDS]"
    while( BasicLib::extract( p_stream, temp ) != "[/COMMANDS]" )
    {
        if( AddCommand( temp ) )
        {
            // command was added successfully, continue loading data
            commands::reverse_iterator itr = m_commands.rbegin();
            (*itr)->Load( p_stream );
        }
        else
        {
            throw Exception( "Cannot load command: " + temp );
        }
    }

    // load my logic module
    m_logic.Load( p_stream, m_id );


    
    p_stream >> temp;           // chew up "[ITEMS]
    while( BasicLib::extract( p_stream, temp ) != "[/ITEMS]" )
    {
        ItemDB.LoadEntity( p_stream );
        p_stream >> temp;       // chew up each "[/ITEM]" tag
    }

    // now add the character back into the game
    if( !IsPlayer() || IsLoggedIn() )
        Add();
}


void Character::Save( std::ostream& p_stream )
{
    p_stream << "[NAME]                  " << m_name << "\n";
    p_stream << "[DESCRIPTION]           " << m_description << "\n";
    p_stream << "[ROOM]                  " << m_room << "\n";
    p_stream << "[REGION]                " << m_region << "\n";

    p_stream << "[TEMPLATEID]            " << m_templateid << "\n";
    p_stream << "[ACCOUNT]               " << m_account << "\n";
    p_stream << "[QUIETMODE]             " << m_quiet << "\n";
    p_stream << "[VERBOSEMODE]           " << m_verbose << "\n";

    // save my attributes to disk
    m_attributes.Save( p_stream );


    // save my commands
    p_stream << "[COMMANDS]\n";
    commands::iterator commanditr = m_commands.begin();
    while( commanditr != m_commands.end() )
    {
        p_stream << (*commanditr)->Name() << "\n";
        (*commanditr)->Save( p_stream );
        ++commanditr;
    }
    p_stream << "[/COMMANDS]\n";

    // save my logic
    m_logic.Save( p_stream );


    // save my items
    p_stream << "\n\n[ITEMS]\n";
    items::iterator itr = m_items.begin();
    while( itr != m_items.end() )
    {
        p_stream << "[ITEM]\n";
        Item& e = ItemDB.get( *itr );
        ItemDB.SaveEntity( p_stream, e );
        p_stream << "[/ITEM]\n";
        ++itr;
    }
    p_stream << "[/ITEMS]\n";

}


Character::commands::iterator Character::FindCommand( const std::string& p_name )
{
    // perform full matches
    stringmatchfull matchfull( p_name );
    commands::iterator itr = m_commands.begin();
    while( itr != m_commands.end() )
    {
        if( matchfull( (*itr)->Name() ) )
            return itr;
        ++itr;
    }

    // perform partial matches
    stringmatchpart matchpart( p_name );
    itr = m_commands.begin();
    while( itr != m_commands.end() )
    {
        if( matchpart( (*itr)->Name() ) )
            return itr;
        ++itr;
    }

    return itr;
}



bool Character::HasCommand( const std::string& p_command )
{
    commands::iterator itr = m_commands.begin();
    while( itr != m_commands.end() )
    {
        try
        {
            if( (*itr)->Name() == p_command )
                return true;
        }
        catch( ... ) {}     // just catch script errors
        ++itr;
    }
    return false;
}

bool Character::AddCommand( const std::string& p_command )
{
    if( HasCommand( p_command ) )
        return false;


    try
    {
        m_commands.push_back( CommandDB.generate( p_command, m_id ) );
        return true;
    }
    catch( ... ) {}     // just catch errors
    return false;
}


bool Character::DelCommand( const std::string& p_command )
{
    try
    {
        commands::iterator itr = m_commands.begin();
        while( itr != m_commands.end() )
        {
            if( (*itr)->Name() == p_command )
            {
                delete (*itr);
                m_commands.erase( itr );
                return true;
            }
            ++itr;
        }
    }
    catch( ... ) {}     // just catch errors
    return false;
}



void Character::Add()
{
    region reg( m_region );
    reg.AddCharacter( m_id );

    room r( m_room );
    r.AddCharacter( m_id );
}


void Character::Remove()
{
    if( m_region != 0 && m_room != 0 )
    {
        region reg( m_region );
        reg.DelCharacter( m_id );

        room r( m_room );
        r.DelCharacter( m_id );
    }
}


}   // end namespace BetterMUD

