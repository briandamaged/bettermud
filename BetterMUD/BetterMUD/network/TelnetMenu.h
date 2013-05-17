// MUD Programming
// Ron Penton
// (C)2003
// TelnetMenu.h - This class is the telnet menu handler for BetterMUD.
// 
// 

#ifndef BETTERMUDTELNETMENU_H
#define BETTERMUDTELNETMENU_H

#include "SocketLib/SocketLib.h"
#include "../entities/Entity.h"
#include "../entities/Account.h"
#include "../databases/AccountDatabase.h"
#include "../scripts/python/PythonScript.h"
#include "BetterTelnet.h"
#include <string>

using SocketLib::Telnet;
using SocketLib::Connection;
using std::string;

namespace BetterMUD
{



class TelnetMenu : public BetterTelnet::handler
{
    // typedef the class because MSVC6 isn't smart enough to construct
    // a "BetterTelnet::handler" object, yet it will construct a typedef just
    // fine.  *boggle*
    typedef BetterTelnet::handler thandler;
public:

    // ------------------------------------------------------------------------
    //  Construct the handler with a reference to the connection so that it can
    //  be used later on. Handlers are initialized only once, and cannot change
    //  connections. A flaw in MSVC6 neccessitated the typedeffing of
    //  BetterTelnet::handler to thandler in order to call the base constructor.
    // ------------------------------------------------------------------------
    TelnetMenu( Connection<BetterTelnet>& p_conn, entityid p_account )
        : thandler( p_conn ),
          m_account( AccountDB.get( p_account ) )
    { }


    // ------------------------------------------------------------------------
    //  Handler Functions
    // ------------------------------------------------------------------------
    void Handle( string p_data );
    void Enter() { PrintMenu(); };
    void Leave() {};
    void Hungup() {};
    void Flooded() {};

    void PrintMenu();

protected:
    Account& m_account;         // account 

};  // end class TelnetMenu




// ============================================================================
// HELP MENU
// ============================================================================
class TelnetMenuHelp : public BetterTelnet::handler
{
    // typedef the class because MSVC6 isn't smart enough to construct
    // a "BetterTelnet::handler" object, yet it will construct a typedef just
    // fine.  *boggle*
    typedef BetterTelnet::handler thandler;
public:

    TelnetMenuHelp( Connection<BetterTelnet>& p_conn, entityid p_account )
        : thandler( p_conn ),
          m_account( AccountDB.get( p_account ) ) {}

    void Handle( string p_data )    { m_connection->RemoveHandler(); }
    void Enter() { PrintHelp(); }
    void Leave() {}
    void Hungup() {}
    void Flooded() {}

    void PrintHelp();

protected:
    Account& m_account;         // account

};  // end class TelnetMenuHelp




// ============================================================================
// NEW CHARACTER MENU
// ============================================================================
class TelnetMenuNew : public BetterTelnet::handler
{
    // typedef the class because MSVC6 isn't smart enough to construct
    // a "BetterTelnet::handler" object, yet it will construct a typedef just
    // fine.  *boggle*
    typedef BetterTelnet::handler thandler;
public:

    TelnetMenuNew( Connection<BetterTelnet>& p_conn, entityid p_account )
        : thandler( p_conn ),
          m_account( AccountDB.get( p_account ) ) 
    {
        // clear the ID
        m_char = 0;

        m_creationmod.Load( "data.logon.logon" );
        m_creationmod.Reload( LEAVEEXISTING );
    }

    void Handle( string p_data );
    void Enter() { PrintRaces(); }
    void Leave() {}
    void Hungup() {}
    void Flooded() {}

    void PrintRaces();

protected:
    Account& m_account;         // account
    entityid m_char;            // id of new character
    PythonModule m_creationmod; // python module governing the creation process

};  // end class TelnetMenuNew


// ============================================================================
// DELETE CHARACTER MENU
// ============================================================================
class TelnetMenuDelete : public BetterTelnet::handler
{
    // typedef the class because MSVC6 isn't smart enough to construct
    // a "BetterTelnet::handler" object, yet it will construct a typedef just
    // fine.  *boggle*
    typedef BetterTelnet::handler thandler;
    typedef std::list<entityid> races;
public:

    TelnetMenuDelete( Connection<BetterTelnet>& p_conn, entityid p_account )
        : thandler( p_conn ),
          m_account( AccountDB.get( p_account ) ) 
    {
        // clear the ID
        m_char = 0;
    }

    void Handle( string p_data );
    void Enter() { PrintCharacters(); }
    void Leave() {}
    void Hungup() {}
    void Flooded() {}

    void PrintCharacters();

protected:
    Account& m_account;         // account
    entityid m_char;            // id of new character

};  // end class TelnetMenuDelete


// ============================================================================
// DELETE CHARACTER MENU
// ============================================================================
class TelnetMenuEnter : public BetterTelnet::handler
{
    // typedef the class because MSVC6 isn't smart enough to construct
    // a "BetterTelnet::handler" object, yet it will construct a typedef just
    // fine.  *boggle*
    typedef BetterTelnet::handler thandler;
    typedef std::list<entityid> races;
public:

    TelnetMenuEnter( Connection<BetterTelnet>& p_conn, entityid p_account )
        : thandler( p_conn ),
          m_account( AccountDB.get( p_account ) ) {}

    void Handle( string p_data );
    void Enter() { PrintCharacters(); }
    void Leave() {}
    void Hungup() {}
    void Flooded() {}

    void PrintCharacters();

protected:
    Account& m_account;         // account

};  // end class TelnetMenuDelete







}   // end namespace BetterMUD

#endif
