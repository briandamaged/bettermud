// MUD Programming
// Ron Penton
// (C)2003
// LogicDatabase.h - This file contains the logic database
// 
// 


#ifndef BETTERMUDLOGICDATABASE_H
#define BETTERMUDLOGICDATABASE_H

#include "../scripts/Logic.h"
#include "../scripts/python/PythonScript.h"

namespace BetterMUD
{

class LogicDatabase : public PythonDatabase
{
public:

    LogicDatabase() : PythonDatabase( "data/logics/" ) {}

    Logic* generate( const std::string& p_str, entityid p_id );
};


extern LogicDatabase LogicDB;
}   // end namespace BetterMUD


#endif
