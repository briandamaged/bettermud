// MUD Programming
// Ron Penton
// (C)2003
// RoomDatabase.h - This file contains the room entity database
// 
// 


#ifndef BETTERMUDROOMDATABASE_H
#define BETTERMUDROOMDATABASE_H

#include "Databases.h"
#include "../entities/Room.h"

namespace BetterMUD
{


class RoomDatabase : public VectorDatabase<Room>
{
public:
};

extern RoomDatabase RoomDB;

}   // end namespace BetterMUD


#endif
