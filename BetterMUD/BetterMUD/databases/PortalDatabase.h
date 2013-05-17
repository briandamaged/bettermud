// MUD Programming
// Ron Penton
// (C)2003
// PortalDatabase.h - This file contains the portal entity database
// 
// 


#ifndef BETTERMUDPORTALDATABASE_H
#define BETTERMUDPORTALDATABASE_H

#include "Databases.h"
#include "../entities/Portal.h"

namespace BetterMUD
{


class PortalDatabase : public VectorDatabase<Portal>
{
public:
};

extern PortalDatabase PortalDB;
}   // end namespace BetterMUD


#endif
