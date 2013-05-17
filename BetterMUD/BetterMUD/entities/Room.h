// MUD Programming
// Ron Penton
// (C)2003
// Room.h - This file contains the room entity type
// 
// 


#ifndef BETTERMUDROOM_H
#define BETTERMUDROOM_H

#include <string>
#include "BasicLib/BasicLib.h"
#include "Entity.h"
#include "LogicEntity.h"
#include "DataEntity.h"

namespace BetterMUD
{

class Room : 
    public LogicEntity,
    public DataEntity,
    public HasRegion,
    public HasCharacters,
    public HasItems,
    public HasPortals
{
public:

    // disk access functions
    void Save( std::ostream& p_stream );
    void Load( std::istream& p_stream );

    void Add();
    void Remove();

protected:

};  // end class Room

}   // end namespace BetterMUD


#endif
