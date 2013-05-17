// MUD Programming
// Ron Penton
// (C)2003
// RoomAccessor.h - This file contains the room accessor class
// 
// 


#ifndef BETTERMUDROOMACCESSOR_H
#define BETTERMUDROOMACCESSOR_H

#include <set>
#include <list>
#include "../entities/Entity.h"


namespace BetterMUD
{

// forward declaration
class Room;

// Accessor
class room
{
public:

    ENTITYHEADERS( room );
    HASREGIONHEADERS;
    HASITEMSHEADERS;
    HASCHARACTERSHEADERS;
    HASPORTALSHEADERS;
    HASDATABANKHEADERS;
    HASLOGICHEADERS;

protected:
    Room* m_room;
   
};

}   // end namespace BetterMUD


#endif
