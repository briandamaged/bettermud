// MUD Programming
// Ron Penton
// (C)2003
// TelnetLogon.cpp - This class is the telnet logon handler for BetterMUD.
// 
// 

#include <iostream>

#include "BasicLib/BasicLib.h"
#include "../databases/AccountDatabase.h"
#include "TelnetMenu.h"
#include "TelnetLogon.h"


namespace BetterMUD
{

// ------------------------------------------------------------------------
//  This handles incomming commands. Anything passed into this function
//  is assumed to be a complete command from a client.
// ------------------------------------------------------------------------
void TelnetLogon::Handle( string p_data )
{
    entityid id;

    if( m_errors == 5 )
    {
        m_connection->Protocol().SendString( 
            *m_connection, 
            "<#FF0000>Too many incorrect responses, closing connection...\r\n" );
        m_connection->Close();
        return;
    }


    if( m_state == ENTERNAME )  // has not entered name yet
    {
        if( BasicLib::LowerCase( p_data ) == "new" )
        {
            // get the new account message
            std::ifstream f( "data/logon/newaccount.data", std::ios::binary );
            std::string str;
            std::getline( f, str, '\0' );

            // switch to the new state and tell the connection.
            m_state = ENTERNEWNAME;
            m_connection->Protocol().SendString( *m_connection, SocketLib::clearscreen + str );
        }
        else
        {
            id = AccountDB.findname( p_data );

            if( id == 0 )
            {
                // name does not exist
                m_errors++;
                m_connection->Protocol().SendString( *m_connection,
                    "<#FF0000>Sorry, the account \"<#FFFFFF>" + p_data +
                    "<#FF0000>\" does not exist.\r\n" + 
                    "Please enter your name, or \"new\" if you are new: <#FFFFFF>" );
            }
            else
            {
                // name exists, go to password entrance.
                m_state = ENTERPASS;

                m_account = id;
                Account& a = AccountDB.get( id );

                if( a.Banned() )
                {
                    m_connection->Protocol().SendString( *m_connection,
                        "<#FF0000>SORRY! You are BANNED!" );
                    m_connection->Close();
                    m_state = ENTERDEAD;
                    return;
                }

                m_name = a.Name();
                m_pass = a.Password();
                
                m_connection->Protocol().SendString( *m_connection,
                    "<#00FF00>Welcome, <#FFFFFF>" + m_name +
                    "\r\n<#00FF00>Please enter your password: <#FFFFFF>" );
            }
        }

        return;
    }

    if( m_state == ENTERNEWNAME )
    {
        // check if the name is taken:
        id = AccountDB.findname( p_data );
        if( id != 0 )
        {
            m_errors++;
            m_connection->Protocol().SendString( *m_connection,
                "<#FF0000>Sorry, the account name \"<#FFFFFF>" + p_data + 
                "<#FF0000>\" has already been taken.\r\n" + 
                "<#FFFF00>Please enter another name: <#FFFFFF>" );
        }
        else
        {
            if( !AccountDB.AcceptibleName( p_data ) )
            {
                m_errors++;
                m_connection->Protocol().SendString( *m_connection,
                    "<#FF0000>Sorry, the account name \"<#FFFFFF>" + p_data +
                    "<#FF0000>\" is unacceptible.\r\n" +
                    "<#FFFF00>Please enter your desired name: <#FFFFFF>" );
            }
            else
            {
                m_state = ENTERNEWPASS;
                m_name = p_data;
                m_connection->Protocol().SendString( *m_connection,
                    "<#00FF00>Please enter your desired password: <#FFFFFF>" );
            }
        }

        return;
    }

    if( m_state == ENTERNEWPASS )
    {
        // make sure there's no whitespace.
        if( p_data.find_first_of( BasicLib::WHITESPACE ) != string::npos )
        {
            m_errors++;
            m_connection->Protocol().SendString( *m_connection,
                    "<#FF0000>INVALID PASSWORD!\r\n"
                    "<#00FF00>Please enter your desired password: <#FFFFFF>" );
            return;
        }

        m_connection->Protocol().SendString( *m_connection,
                "<#00FF00>Thank you! You are now entering the realm...\r\n" );

        // create and get the new account.
        id = AccountDB.Create( m_name, p_data );
        m_account = id;
        Account& newaccount = AccountDB.get( id );

        // make the player the administrator if he's the first to log in.
        if( AccountDB.size() == 0 )
            newaccount.SetAccessLevel( Admin );

        // enter the game menu
        GotoMenu();

        return;
    }

    if( m_state == ENTERPASS )
    {
        if( m_pass == p_data )
        {
            m_connection->Protocol().SendString( *m_connection,
                    "<#00FF00>Thank you! You are now entering the realm...\r\n" );
            
            // enter the game
            GotoMenu();
        }
        else
        {
            m_errors++;
            m_connection->Protocol().SendString( *m_connection,
                    "<#FF0000>INVALID PASSWORD!\r\n" 
                    "<#FFFF00>Please enter your password: <#FFFFFF>" );
        }

        return;
    }
}


// ------------------------------------------------------------------------
//  This notifies the handler that there is a new connection
// ------------------------------------------------------------------------
void TelnetLogon::Enter()
{
    std::cout << "Connection established\n";
    // load the logon message
    std::ifstream f( "data/logon/logon.data", std::ios::binary );
    std::string str;
    std::getline( f, str, '\0' );

    m_connection->Protocol().SendString( *m_connection, str );
}

// ------------------------------------------------------------------------
//  Takes the connection to the menu state.
// ------------------------------------------------------------------------
void TelnetLogon::GotoMenu()
{
    // go to the main menu of the game.

    Connection<BetterTelnet>* c = m_connection;
    entityid id = m_account;
    
    c->RemoveHandler();
    c->AddHandler( new TelnetMenu( *c, id ) );
}


}   // end namespace BetterMUD

