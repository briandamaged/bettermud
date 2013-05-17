// MUD Programming
// Ron Penton
// (C)2003
// RegionDatabase.cpp - This file contains the region entity database
// 
// 



#include "RegionDatabase.h"
#include "RoomDatabase.h"
#include "PortalDatabase.h"
#include "CharacterDatabase.h"
#include "ItemDatabase.h"

namespace BetterMUD
{

// declare the global instance of the database
RegionDatabase RegionDB;

void RegionDatabase::LoadAll()
{
    static std::string dir = "data/regions/manifest";
    std::ifstream manifest( dir.c_str(), std::ios::binary );
    manifest >> std::ws;

    std::string regionname;
    while( manifest.good() )
    {
        manifest >> regionname;
        LoadRegion( regionname );
    }
}


void RegionDatabase::LoadRegion( const std::string& p_name )
{
    // load the region
    std::string dir = "data/regions/" + p_name + "/";
    std::string regionfilename = dir + "region.data";
    std::ifstream regionfile( regionfilename.c_str(), std::ios::binary );
    Region &reg = LoadEntity( regionfile );
    reg.SetDiskname( p_name );

    RoomDB.LoadFile( dir + "rooms" );
    PortalDB.LoadFile( dir + "portals" );
    CharacterDB.LoadFile( dir + "characters" );
    ItemDB.LoadFile( dir + "items" );
}


void RegionDatabase::SaveRegion( entityid p_region )
{
    Region& reg = get( p_region );
    std::string workingdir = "data/regions/" + reg.Diskname();

    // save the region
    std::string regionfilename = workingdir + "/region.data";
    std::ofstream regionfile( regionfilename.c_str(), std::ios::binary );
    SaveEntity( regionfile, reg );

    // save the region's rooms
    std::string roomsfilename = workingdir + "/rooms.data";
    std::ofstream roomsfile( roomsfilename.c_str(), std::ios::binary );
    Region::rooms::iterator ritr = reg.RoomsBegin();
    while( ritr != reg.RoomsEnd() )
    {
        Room& r = RoomDB.get( *ritr );
        RoomDB.SaveEntity( roomsfile, r );
        roomsfile << "\n";
        ++ritr;
    }

    // save the region's portals
    std::string portalsfilename = workingdir + "/portals.data";
    std::ofstream portalsfile( portalsfilename.c_str(), std::ios::binary );
    Region::portals::iterator pitr = reg.PortalsBegin();
    while( pitr != reg.PortalsEnd() )
    {
        Portal& p = PortalDB.get( *pitr );
        PortalDB.SaveEntity( portalsfile, p );
        portalsfile << "\n";
        ++pitr;
    }

    // save the region's characters
    std::string charactersfilename = workingdir + "/characters.data";
    std::ofstream charactersfile( charactersfilename.c_str(), std::ios::binary );
    Region::characters::iterator citr = reg.CharactersBegin();
    while( citr != reg.CharactersEnd() )
    {
        Character& c = CharacterDB.get( *citr );
        if( !c.IsPlayer() )
        {
            CharacterDB.SaveEntity( charactersfile, c );
            charactersfile << "\n";
        }
        ++citr;
    }


    // save the region's items
    std::string itemsfilename = workingdir + "/items.data";
    std::ofstream itemsfile( itemsfilename.c_str(), std::ios::binary );
    Region::items::iterator iitr = reg.ItemsBegin();
    while( iitr != reg.ItemsEnd() )
    {
        Item& i = ItemDB.get( *iitr );
        ItemDB.SaveEntity( itemsfile, i );
        itemsfile << "\n";
        ++iitr;
    }
}

void RegionDatabase::SaveAll()
{
    iterator itr = m_container.begin();
    while( itr != m_container.end() )
    {
        if( itr->ID() != 0 )
        {
            SaveRegion( itr->ID() );
        }
        ++itr;
    }

}



}   // end namespace BetterMUD

