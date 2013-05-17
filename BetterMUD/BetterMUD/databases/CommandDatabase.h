// MUD Programming
// Ron Penton
// (C)2003
// CommandDatabase.h - This file contains the command entity database
// 
// 


#ifndef BETTERMUDCOMMANDDATABASE_H
#define BETTERMUDCOMMANDDATABASE_H

#include "Databases.h"
#include "../entities/Attributes.h"
#include "../scripts/Command.h"
#include "../scripts/CPPCommand.h"
#include "../scripts/python/PythonCommand.h"


namespace BetterMUD
{

class CommandDatabase : public PythonDatabase
{
public:

    CommandDatabase() : PythonDatabase( "data/commands/" ) {}
    Command* generate( const std::string& p_str, entityid p_character );
};

extern CommandDatabase CommandDB;

}   // end namespace BetterMUD


#endif
