// MUD Programming
// Ron Penton
// (C)2003
// RegionAccessor.cpp - This file contains the region accessor class
// 
// 




#include "RegionAccessor.h"
#include "../databases/RegionDatabase.h"
#include "PortalAccessor.h"
#include "ItemAccessor.h"
#include "CharacterAccessor.h"
#include "RoomAccessor.h"

namespace BetterMUD
{

ENTITYIMPLEMENTATIONS( region, m_region, RegionDB );
HASITEMSIMPLEMENTATIONS( region, m_region );
HASCHARACTERSIMPLEMENTATIONS( region, m_region );
HASROOMSIMPLEMENTATIONS( region, m_region );
HASPORTALSIMPLEMENTATIONS( region, m_region );
HASLOGICIMPLEMENTATIONS( region, m_region );
HASDATABANKIMPLEMENTATIONS( region, m_region );


}   // end namespace BetterMUD
