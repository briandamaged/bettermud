// MUD Programming
// Ron Penton
// (C)2003
// CharacterDatabase.cpp - This file contains the character entity database
// 
// 



#include "../Exception.h"
#include "CharacterDatabase.h"

namespace BetterMUD
{

// declare the static instance of the database container
CharacterDatabase CharacterDB;



void CharacterDatabase::SavePlayers()
{
    static std::string dir = "data/players/";
    static std::string manifestname = dir + "manifest";
    std::ofstream manifest( manifestname.c_str(), std::ios::binary );

    // save all the players to disk
    instances::container::iterator itr = m_instances.begin();
    while( itr != m_instances.end() )
    {
        // only save players do disk in this function
        if( itr->second.IsPlayer() )
        {
            // create filename and load file
            std::string playerfilename = dir + itr->second.Name() + ".data";
            std::ofstream playerfile( playerfilename.c_str(), std::ios::binary );

            // save file to disk
            SaveEntity( playerfile, itr->second );

            // save players name to manifest
            manifest << itr->second.Name() << "\n";
        }
        ++itr;
    }
}

void CharacterDatabase::LoadPlayers()
{
    // load all the players
    m_instances.LoadDirectory( "data/players/" );
}

void CharacterDatabase::LoadTemplates()
{
    // load all the templates
    m_templates.LoadDirectory( "data/templates/characters/" );
}

void CharacterDatabase::LoadTemplates( const std::string& p_file )
{
    // load a single template file
    m_templates.LoadFile( "data/templates/characters/" + p_file );
}

void CharacterDatabase::LoadPlayer( const std::string& p_name )
{
    // load a player
    m_instances.LoadFile( "data/players/" + p_name );
}



entityid CharacterDatabase::FindPlayerFull( const std::string& p_name )
{
    stringmatchfull matchfull( p_name );
    instances::container::iterator itr = m_instances.begin();
    while( itr != m_instances.end() )
    {
        if( matchfull( itr->second.Name() ) )
            return itr->first;
        ++itr;
    }

    return 0;
}

entityid CharacterDatabase::FindPlayerPart( const std::string& p_name )
{
    entityid id = FindPlayerFull( p_name );

    if( id != 0 )
        return id;

    stringmatchpart matchpart( p_name );
    instances::container::iterator itr = m_instances.begin();
    while( itr != m_instances.end() )
    {
        if( matchpart( itr->second.Name() ) )
            return itr->first;
        ++itr;
    }

    return 0;
}



}   // end namespace BetterMUD

