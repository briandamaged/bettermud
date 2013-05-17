// MUD Programming
// Ron Penton
// (C)2003
// AccountDatabase.cpp - This file contains the account entity database
// 
// 



#include "AccountDatabase.h"
#include "../Game.h"

namespace BetterMUD
{

// declare the global instance of the account database
AccountDatabase AccountDB;


entityid AccountDatabase::Create( 
    const std::string& p_name,          // name
    const std::string& p_pass )         // password
{
    // find an open ID
    entityid id = FindOpenID();

    // get the account pointer
    Account& a = m_container[id];
    a.SetID( id );
    a.SetName( p_name );
    a.SetPass( p_pass );
    a.SetLoginTime( g_game.GetTime() );

    return id;
}


void AccountDatabase::Load()
{
    LoadDirectory( "data/accounts/" );
}


void AccountDatabase::Save()
{
    static std::string dir = "data/accounts/";
    static std::string manifestname = dir + "manifest";
    std::ofstream manifest( manifestname.c_str(), std::ios::binary );
    container::iterator itr = m_container.begin();

    while( itr != m_container.end() )
    {
        std::string accountfilename = dir + itr->second.Name() + ".data";
        std::ofstream accountfile( accountfilename.c_str(), std::ios::binary );
        SaveEntity( accountfile, itr->second );
        manifest << itr->second.Name() << "\n";
        ++itr;
    }
}



// ------------------------------------------------------------------------
//  This checks if a user name is acceptible.
// ------------------------------------------------------------------------
bool AccountDatabase::AcceptibleName( const std::string& p_name )
{
    static std::string inv = " \"'~!@#$%^&*+/\\[]{}<>()=.,?;:";

    // must not contain any invalid characters
    if(  p_name.find_first_of( inv ) != std::string::npos )
        return false;

    // must be less than 17 chars and more than 2
    if( p_name.size() > 16 || p_name.size() < 3 )
        return false;

    // must start with an alphabetical character
    if( !isalpha( p_name[0] ) )
        return false;

    if( p_name == "new" )
        return false;

    return true;
}


}   // end namespace BetterMUD

