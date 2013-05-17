// MUD Programming
// Ron Penton
// (C)2003
// RegionAccessor.h - This file contains the region accessor class
// 
// 


#ifndef BETTERMUDREGIONACCESSOR_H
#define BETTERMUDREGIONACCESSOR_H

#include <set>
#include <list>
#include "../entities/Entity.h"
#include "../scripts/Logic.h"
#include "AccessorMacros.h"

namespace BetterMUD
{

// forward declaration
class Region;

// Accessor
class region
{
public:

    ENTITYHEADERS( region );
    HASITEMSHEADERS;
    HASCHARACTERSHEADERS;
    HASROOMSHEADERS;
    HASPORTALSHEADERS;
    HASDATABANKHEADERS;
    HASLOGICHEADERS;

protected:
    Region* m_region;
};

}   // end namespace BetterMUD


#endif
