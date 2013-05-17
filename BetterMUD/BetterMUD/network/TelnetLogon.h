// MUD Programming
// Ron Penton
// (C)2003
// TelnetLogon.h - This class is the telnet logon handler for BetterMUD.
// 
// 

#ifndef BETTERMUDTELNETLOGON_H
#define BETTERMUDTELNETLOGON_H

#include <string>
#include "SocketLib/SocketLib.h"
#include "../entities/Entity.h"
#include "BetterTelnet.h"

using SocketLib::Connection;
using std::string;

namespace BetterMUD
{


enum LogonState 
{
    ENTERNAME,              // enter your name, or "new"
    ENTERNEWNAME,           // new account, enter new name
    ENTERNEWPASS,           // new account, enter new password
    ENTERPASS,              // enter password
    ENTERDEAD               // dead state... to prevent banning workarounds
};


class TelnetLogon : public BetterTelnet::handler
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
    TelnetLogon( Connection<BetterTelnet>& p_conn )
        : thandler( p_conn )
    {
        m_state = ENTERNAME;
        m_errors = 0;
    }


    // ------------------------------------------------------------------------
    //  Handler Functions
    // ------------------------------------------------------------------------
    void Handle( string p_data );
    void Enter();
    void Leave() {};
    void Hungup() {};
    void Flooded() {};


    // ------------------------------------------------------------------------
    //  This tells a connection that there is no room for the connection and
    //  that it will be terminated.
    // ------------------------------------------------------------------------
    static void NoRoom( Connection<BetterTelnet>& p_connection )
    {
        static string msg = "Sorry, there is no more room on this server.\r\n";
        try
        {
            p_connection.Send( msg.c_str(), (int)msg.size() );
        }
        catch( SocketLib::Exception )
        {
            // do nothing here; probably an exploiter if sending that data
            // causes an exception.
        }
    }

    void GotoMenu();

protected:

    LogonState m_state;
    int m_errors;               // how many times has an invalid answer been
                                // entered?

    string m_name;              // name
    string m_pass;              // password
    entityid m_account;         // account id


};  // end class TelnetLogon



}   // end namespace BetterMUD

#endif
