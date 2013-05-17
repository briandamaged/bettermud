// MUD Programming
// Ron Penton
// (C)2003
// TelnetGame.cpp - This class is the telnet game handler for BetterMUD.
// 
// 

#include "TelnetGame.h"
#include "TelnetReporter.h"
#include "../Game.h"

namespace BetterMUD
{

// ------------------------------------------------------------------------
//  This handles incomming commands. Anything passed into this function
//  is assumed to be a complete command from a client.
// ------------------------------------------------------------------------
void TelnetGame::Handle( string p_data )
{
    g_game.DoAction( "command", m_character.ID(), 0, 0, 0, p_data );
}

void TelnetGame::Enter()
{
    // hang up the existing character if it's already logged in.
    if( m_character.IsLoggedIn() )
    {
        m_connection->Protocol().SendString( 
            *m_connection, 
            "<#FF0000>Hanging up existing connection...\r\n" );
        m_character.DoAction( Action( "hangup" ) );
    }

    m_character.AddExistingLogic( new TelnetReporter( m_character.ID(), m_connection ) );

    // show the news
    g_game.DoAction( "command", m_character.ID(), 0, 0, 0, "/news" );

    // log in the player
    g_game.DoAction( "enterrealm", m_character.ID() );
}


void TelnetGame::Leave()
{
    g_game.DoAction( "leaverealm", m_character.ID() );
}


}   // end namespace BetterMUD

