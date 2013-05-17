// MUD Programming
// Ron Penton
// (C)2003
// ItemDatabase.cpp - This file contains the item entity database
// 
// 



#include "../Exception.h"
#include "ItemDatabase.h"

namespace BetterMUD
{

// declare the static instance of the database container
ItemDatabase ItemDB;




void ItemDatabase::LoadTemplates()
{
    // load all the templates
    m_templates.LoadDirectory( "data/templates/items/" );
}

void ItemDatabase::LoadTemplates( const std::string& p_file )
{
    m_templates.LoadFile( "data/templates/items/" + p_file );
}




}   // end namespace BetterMUD

