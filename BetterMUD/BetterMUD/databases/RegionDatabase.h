// MUD Programming
// Ron Penton
// (C)2003
// RegionDatabase.h - This file contains the region entity database
// 
// 


#ifndef BETTERMUDREGIONDATABASE_H
#define BETTERMUDREGIONDATABASE_H

#include "Databases.h"
#include "../entities/Region.h"


namespace BetterMUD
{


class RegionDatabase : public VectorDatabase<Region>
{
public:
    void LoadAll();
    void LoadRegion( const std::string& p_name );
    void SaveRegion( entityid p_region );
    void SaveAll();

    
};

extern RegionDatabase RegionDB;
}   // end namespace BetterMUD


#endif
