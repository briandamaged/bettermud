// MUD Programming
// Ron Penton
// (C)2003
// CommandDatabase.cpp - This file contains the command entity database
// 
// 



#include "../Exception.h"
#include "CommandDatabase.h"
#include "../scripts/CPPCommands.h"

namespace BetterMUD
{

// declare the static instance of the database container
CommandDatabase CommandDB;



Command* CommandDatabase::generate( const std::string& p_str, entityid p_character )
{
    if( p_str == "quit" )
        return new CPPCommandQuit( p_character );
    else if( p_str == "go" )
        return new CPPCommandGo( p_character );
    else if( p_str == "chat" )
        return new CPPCommandChat( p_character );
    else if( p_str == "say" )
        return new CPPCommandSay( p_character );
    else if( p_str == "kick" )
        return new CPPCommandKick( p_character );
    else if( p_str == "quiet" )
        return new CPPCommandQuiet( p_character );
    else if( p_str == "shutdown" )
        return new CPPCommandShutdown( p_character );
    else if( p_str == "look" )
        return new CPPCommandLook( p_character );
    else if( p_str == "commands" )
        return new CPPCommandCommands( p_character );
    else if( p_str == "reloadscript" )
        return new CPPCommandReloadScript( p_character );
    else
    {
        try
        {
            // try to load a python script
            PythonInstance* command = SpawnNew( p_str );
            return new PythonCommand( p_character, command );
        }
        catch( ... )
        {
            PyErr_Print();
            // no script found
        }
    }
    
    throw Exception( "Unknown Command Script" );
}



}   // end namespace BetterMUD

