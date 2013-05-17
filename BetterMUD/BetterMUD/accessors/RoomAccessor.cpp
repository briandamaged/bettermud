// MUD Programming
// Ron Penton
// (C)2003
// RoomAccessor.cpp - This file contains the room accessor class
// 
// 


#include "../databases/RoomDatabase.h"
#include "../accessors/Accessors.h"

namespace BetterMUD
{


ENTITYIMPLEMENTATIONS( room, m_room, RoomDB );
HASREGIONIMPLEMENTATIONS( room, m_room );
HASITEMSIMPLEMENTATIONS( room, m_room );
HASCHARACTERSIMPLEMENTATIONS( room, m_room );
HASPORTALSIMPLEMENTATIONS( room, m_room );
HASLOGICIMPLEMENTATIONS( room, m_room );
HASDATABANKIMPLEMENTATIONS( room, m_room );

}   // end namespace BetterMUD
