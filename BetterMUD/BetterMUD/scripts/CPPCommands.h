// MUD Programming
// Ron Penton
// (C)2003
// CPPCommands.h - This file contains the standard C++-implemented game commands
// 
// 


#ifndef BETTERMUDCPPCOMMANDS_H
#define BETTERMUDCPPCOMMANDS_H

#include "../Game.h"
#include "CPPCommand.h"
#include "../databases/CommandDatabase.h"
#include "python/PythonScript.h"


namespace BetterMUD
{


// -----------------------------------------------------------------------
//  Tells a user to quit.
// -----------------------------------------------------------------------
class CPPCommandQuit : public CPPCommand
{
public:
    CPPCommandQuit( entityid p_character )
    : CPPCommand(
        p_character,
        "quit",
        "\"quit\"",
        "This removes your character from the game and takes you back to the Game Menu." ) {}

    void Execute( const std::string& p_parameters )
    {
        m_character.DoAction( Action( "leave" ) );
    }
};  // end class CPPCommandQuit

// -----------------------------------------------------------------------
//  Tells a user to chat.
// -----------------------------------------------------------------------
class CPPCommandChat : public CPPCommand
{
public:
    CPPCommandChat( entityid p_character )
    : CPPCommand(
        p_character,
        "chat",
        "\"chat <message>\"",
        "This sends a message to every player who is currently logged into the game." ) {}

    void Execute( const std::string& p_parameters )
    {
        if( p_parameters.size() == 0 )
        {
            m_character.DoAction( "error", 0, 0, 0, 0, "Usage: " + Usage() );
            return;
        }
        g_game.AddActionAbsolute( 0, "chat", m_character.ID(), 0, 0, 0, p_parameters );
    }
};  // end class CPPCommandChat

// -----------------------------------------------------------------------
//  Tells a user to chat.
// -----------------------------------------------------------------------
class CPPCommandSay : public CPPCommand
{
public:
    CPPCommandSay( entityid p_character )
    : CPPCommand(
        p_character,
        "say",
        "\"say <message>\"",
        "This sends a message to every character in the same room as you." ) {}

    void Execute( const std::string& p_parameters )
    {
        if( p_parameters.size() == 0 )
        {
            m_character.DoAction( "error", 0, 0, 0, 0, "Usage: " + Usage() );
            return;
        }
        g_game.AddActionAbsolute( 0, "attemptsay", m_character.ID(), 0, 0, 0, p_parameters );        
    }
};  // end class CPPCommandChat


class CPPCommandKick : public CPPCommand
{
public:
    CPPCommandKick( entityid p_character )
    : CPPCommand(
        p_character,
        "kick",
        "\"kick <user>\"",
        "This kicks a user from the realm." ) {}

    void Execute( const std::string& p_parameters )
    {
        if( p_parameters.size() == 0 )
        {
            m_character.DoAction( "error", 0, 0, 0, 0, "Usage: " + Usage() );
            return;
        }

        // find a matching player
        Game::players::iterator itr =
            match<character>( 
                g_game.PlayersBegin(),
                g_game.PlayersEnd(),
                p_parameters );

        if( itr == g_game.PlayersEnd() )
        {
            m_character.DoAction( "error", 0, 0, 0, 0, "Cannot find user " + p_parameters );
            return;
        }

        character c( *itr );
        g_game.AddActionAbsolute( 0, "announce", 0, 0, 0, 0, c.Name() + " has been kicked" );
        c.DoAction( "hangup" );
    }
};  // end class CPPCommandKick



// -----------------------------------------------------------------------
//  sets a players quiet-mode
// -----------------------------------------------------------------------
class CPPCommandQuiet : public CPPCommand
{
public:
    CPPCommandQuiet( entityid p_character )
    : CPPCommand(
        p_character,
        "quiet",
        "\"quiet <on|off>\"",
        "Sets your quiet mode. When not quiet, unrecognized commands will be said as room-speech." ) {}

    void Execute( const std::string& p_parameters )
    {
        if( p_parameters == "on" )
        {
            m_character.SetQuiet( true );
            m_character.DoAction( "announce", 0, 0, 0, 0, "You are now in QUIET mode" );
        }
        else if( p_parameters == "off" )
        {
            m_character.SetQuiet( false );
            m_character.DoAction( "announce", 0, 0, 0, 0, "You are now in LOUD mode" );
        }
        else
        {
            m_character.DoAction( "error", 0, 0, 0, 0, "Usage: " + Usage() );
        }
    }
};  // end class CPPCommandQuiet


// -----------------------------------------------------------------------
//  makes a system announcement
// -----------------------------------------------------------------------
class CPPCommandShutdown : public CPPCommand
{
public:
    CPPCommandShutdown( entityid p_character )
    : CPPCommand(
        p_character,
        "shutdown",
        "\"shutdown\"",
        "Shuts down the MUD" ) {}

    void Execute( const std::string& p_parameters )
    {
        if( p_parameters.size() != 0 )
            g_game.DoAction( "announce", 0, 0, 0, 0, "The Server is shutting down: " + p_parameters );
        else
            g_game.DoAction( "announce", 0, 0, 0, 0, "The Server is shutting down" );
        g_game.ShutDown();
    }
};  // end class CPPCommandShutdown



// -----------------------------------------------------------------------
//  makes a system announcement
// -----------------------------------------------------------------------
class CPPCommandLook : public CPPCommand
{
public:
    CPPCommandLook( entityid p_character )
    : CPPCommand(
        p_character,
        "look",
        "\"look <|object>\"",
        "Looks at the room (default), or at an optional object within the room" ) {}

    void Execute( const std::string& p_parameters )
    {
        m_character.DoAction( "seeroom", m_character.Room() );
    }
};  // end class CPPCommandLook


// -----------------------------------------------------------------------
//  attempts to enter a portal
// -----------------------------------------------------------------------
class CPPCommandGo : public CPPCommand
{
public:
    CPPCommandGo( entityid p_character )
    : CPPCommand(
        p_character,
        "go",
        "\"go <exit>\"",
        "Tries to move your character into a portal" ) {}

    void Execute( const std::string& p_parameters )
    {
        if( p_parameters.size() == 0 )
        {
            m_character.DoAction( "error", 0, 0, 0, 0, "Usage: " + Usage() );
            return;
        }

        room r( m_character.Room() );
        r.SeekPortal( p_parameters );
        if( !r.IsValidPortal() )
        {
            m_character.DoAction( "error", 0, 0, 0, 0, "You don't see that exit here!" );
            return;
        }

        g_game.AddActionAbsolute( 0, "attemptenterportal", m_character.ID(), r.CurrentPortal() );
    }
};  // end class CPPCommandGo


// -----------------------------------------------------------------------
//  Lists your commands
// -----------------------------------------------------------------------
class CPPCommandCommands : public CPPCommand
{
public:
    CPPCommandCommands( entityid p_character )
    : CPPCommand(
        p_character,
        "commands",
        "\"commands\"",
        "Lists your commands" ) {}

    void Execute( const std::string& p_parameters )
    {
        m_character.DoAction( "announce", 0, 0, 0, 0, 
            "<#FFFFFF>-------------------------------------------------------------------------------" );
        m_character.DoAction( "announce", 0, 0, 0, 0, 
            "<#FFFFFF> Command                          | Usage" );
        m_character.DoAction( "announce", 0, 0, 0, 0, 
            "<#FFFFFF>-------------------------------------------------------------------------------" );

        m_character.BeginCommands();
        while( m_character.IsValidCommand() )
        {
            m_character.DoAction( "announce", 0, 0, 0, 0, 
                "<$reset> " + 
                BasicLib::tostring( m_character.CurrentCommand(), 33 ) + 
                "| " +
                m_character.CurrentCommandUsage() );
            m_character.NextCommand();
        }
    }
};  // end class CPPCommandCommands


// -----------------------------------------------------------------------
//  Lists your commands
// -----------------------------------------------------------------------
class CPPCommandReloadScript : public CPPCommand
{
public:
    CPPCommandReloadScript( entityid p_character )
    : CPPCommand(
        p_character,
        "reloadscript",
        "\"reloadscript <type> <file> <keepall|keepdata>\"",
        "Reloads a script" ) {}

    void Execute( const std::string& p_parameters )
    {
        std::string type = BasicLib::ParseWord( p_parameters, 0 );
        std::string file = "data.commands." + BasicLib::ParseWord( p_parameters, 1 );
        std::string flag = BasicLib::ParseWord( p_parameters, 2 );

        SCRIPTRELOADMODE flagtype;
        if( flag == "keepall" )         flagtype = LEAVEEXISTING;
        else if( flag == "keepdata" )   flagtype = RELOADFUNCTIONS;
        else 
        {
            m_character.DoAction( "error", 0, 0, 0, 0, "Usage: " + Usage() );
            return;
        }


        if( type == "commands" )
        {
            CommandDB.Reload( file, flagtype );
            m_character.DoAction( "announce", 0, 0, 0, 0, "Character Script " + file + " reloaded!" );
            return;
        }

        m_character.DoAction( "error", 0, 0, 0, 0, "Invalid Script Type" );

    }
};  // end class CPPCommandGo




}   // end namespace BetterMUD


#endif
