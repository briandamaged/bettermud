// MUD Programming
// Ron Penton
// (C)2003
// LogicDatabase.cpp - This file contains the logic database
// 
// 



#include "../Exception.h"
#include "LogicDatabase.h"
#include "../scripts/python/PythonLogic.h"

namespace BetterMUD
{

// declare the global instance of the logic database
LogicDatabase LogicDB;

Logic* LogicDatabase::generate( const std::string& p_str, entityid p_id )
{
    PythonLogic* l = 0;
    try
    {
        // try to load a python script
        PythonInstance* logic = SpawnNew( p_str );
        l = new PythonLogic( logic );
        l->Init( p_id );
        return l;
    }
    catch( ... )
    {
        PyErr_Print();
        if( l )
            delete l;
    }
   
    throw Exception( "Error when creating python Logic Script: " + p_str );
}



}   // end namespace BetterMUD

