// MUD Programming
// Ron Penton
// (C)2003
// TelnetGame.h - This class is the telnet game handler for BetterMUD.
// 
// 

#ifndef BETTERMUDTELNETGAME_H
#define BETTERMUDTELNETGAME_H

#include <string>
#include "SocketLib/SocketLib.h"
#include "../entities/Account.h"
#include "../accessors/Accessors.h"
#include "../databases/AccountDatabase.h"

#include "BetterTelnet.h"

using SocketLib::Connection;
using std::string;

namespace BetterMUD
{


class TelnetGame : public BetterTelnet::handler
{
    // typedef the class because MSVC6 isn't smart enough to construct
    // a "BetterTelnet::handler" object, yet it will construct a typedef just
    // fine.  *boggle*
    typedef BetterTelnet::handler thandler;
public:

    TelnetGame( Connection<BetterTelnet>& p_conn, 
                entityid p_account,
                entityid p_character )
        : thandler( p_conn ),
          m_account( AccountDB.get( p_account ) ),
          m_character( p_character )
    {}


    // ------------------------------------------------------------------------
    //  Handler Functions
    // ------------------------------------------------------------------------
    void Handle( string p_data );
    void Enter();
    void Leave();
    void Hungup() {};
    void Flooded() {};



protected:
    Account& m_account;
    character m_character;


};  // end class TelnetLogon



}   // end namespace BetterMUD

#endif
