// MUD Programming
// Ron Penton
// (C)2003
// TelnetMenu.cpp - This class is the telnet menu handler for BetterMUD.
// 
// 

#include "BasicLib/BasicLib.h"
#include "TelnetMenu.h"
#include "TelnetGame.h"
#include "../accessors/Accessors.h"
#include "../databases/AccountDatabase.h"
#include "../databases/CharacterDatabase.h"
#include "../databases/CommandDatabase.h"

namespace BetterMUD
{

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void TelnetMenu::Handle( string p_data )
{
    int option = BasicLib::totype<int>( p_data );
    switch( option )
    {
    case 0:
        m_connection->Close();
        break;
    case 1:
        m_connection->AddHandler( new TelnetMenuEnter( *m_connection, m_account.ID() ) );
        break;
    case 2:
        if( m_account.Characters() >= m_account.AllowedCharacters() )
        {
            m_connection->Protocol().SendString( 
                *m_connection, 
                "<#FF0000>Sorry, you are not allowed any more characters.\r\n" );
            return;
        }
        m_connection->AddHandler( new TelnetMenuNew( *m_connection, m_account.ID() ) );
        break;
    case 3:
        m_connection->AddHandler( new TelnetMenuDelete( *m_connection, m_account.ID() ) );
        break;
    case 4:
        m_connection->AddHandler( new TelnetMenuHelp( *m_connection, m_account.ID() ) );
        break;

    }

}


// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void TelnetMenu::PrintMenu()
{
    static std::string str = 
        SocketLib::clearscreen + 
        "<#FFFFFF>-------------------------------------------------------------------------------\r\n" +
        "<#FFFF00> BetterMUD v1.0 Main Menu\r\n" +
        "<#FFFFFF>-------------------------------------------------------------------------------\r\n" +
        " 0 - Quit\r\n" +
        " 1 - Enter the Game\r\n" +
        " 2 - Create a new Character\r\n" +
        " 3 - Delete an existing Character\r\n" +
        " 4 - View Help\r\n" +
        "-------------------------------------------------------------------------------\r\n" +
        "<#7F7F7F> Enter Choice: <#FFFFFF>";

    m_connection->Protocol().SendString( *m_connection, str );
}


// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void TelnetMenuHelp::PrintHelp()
{
    std::ifstream f( "data/logon/help.data", std::ios::binary );
    std::string str;
    std::getline( f, str, '\0' );

    m_connection->Protocol().SendString( 
        *m_connection, 
        SocketLib::clearscreen + str );
}




void TelnetMenuNew::Handle( string p_data )
{
    // if m_char != 0, then that means the user has selected a character
    // to create. Get a name.
    if( m_char != 0 )
    {
        if( !AccountDB.AcceptibleName( p_data ) )
        {
            m_connection->Protocol().SendString( 
                *m_connection, 
                "<#FF0000>Sorry, that name is not acceptible\r\n"
                "<#00FF00>Please enter your desired name: <#FFFFFF>" );
            return;
        }

        if( CharacterDB.findname( p_data ) != 0 )
        {
            m_connection->Protocol().SendString( 
                *m_connection, 
                "<#FF0000>Sorry, that name is already taken\r\n"
                "<#00FF00>Please enter your desired name: <#FFFFFF>" );
            return;
        }

        character c( m_char );
        c.SetName( p_data );
        m_connection->RemoveHandler();
        return;
    }

    // get the number the user typed.
    int option = BasicLib::totype<int>( p_data );
    
    // if 0, exit state
    if( option == 0 )
    {
        m_connection->RemoveHandler();
        return;
    }

    // even though we checked this earlier, it is *critical* that you check it
    // again, because the user may decide to be "clever", and log in twice.
    // If he's logged in twice (or even more!), he could easily create more
    // characters than he's allowed, since the check is done when the user 
    // enters this state.
    if( m_account.Characters() >= m_account.AllowedCharacters() )
    {
        m_connection->Protocol().SendString( 
            *m_connection, 
            "<#FF0000>Haha, nice try. You're not allowed any more characters!\r\n" );
        return;
    }

    //create the character
    m_char = EntityFromPy( m_creationmod.Call( "gettemplateid", EntityToPy( option ) ) );

    // check if it was valid
    if( m_char == 0 )
    {
        m_connection->Protocol().SendString( *m_connection, 
            "<#FF0000>Invalid option, please try again: <#FFFFFF>" );
        return;
    }

    m_char = CharacterDB.generate( m_char );
    character( m_char ).SetAccount( m_account.ID() );
    m_account.AddCharacter( m_char );

    // now perform the inital setup:
    m_creationmod.Call( "setup", EntityToPy( m_char ) );

    // ask for name
    m_connection->Protocol().SendString( *m_connection, 
        "<#00FF00>Please enter your desired name: <#FFFFFF>" );
}



// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void TelnetMenuNew::PrintRaces()
{
    std::string str = StringFromPy( m_creationmod.Call( "listchars" ) );
    m_connection->Protocol().SendString( *m_connection, str );
}




void TelnetMenuDelete::Handle( string p_data )
{
    // if m_char != 0, then that means the user has selected a character
    // to delete. Confirm that he typed "Y" or "y", and then baleet it.
    if( m_char != 0 )
    {
        if( p_data != "Y" && p_data != "y" )
        {
            m_connection->RemoveHandler();
            return;
        }

        // Baleet the character
        m_account.DelCharacter( m_char );
        m_connection->RemoveHandler();
        return;
    }

    // get the number the user typed.
    int option = BasicLib::totype<int>( p_data );
    
    // if 0, exit state
    if( option == 0 )
    {
        m_connection->RemoveHandler();
        return;
    }

    if( option > m_account.Characters() )
    {
        m_connection->Protocol().SendString( 
            *m_connection, 
            "<#FF0000>INVALID CHARACTER NUMBER\r\n"
            "<#FFFFFF>Enter Number of Character to delete: " );
        return;
    }

    // grab the ID of the character you want to delete.
    Account::characters::iterator itr = m_account.CharactersBegin();
    std::advance( itr, option - 1 );

    //create the character
    m_char = *itr;

    // ask for confirmation
    m_connection->Protocol().SendString( *m_connection, 
        "<#FF0000>Really Delete Character? (Y/N) " );
}


void TelnetMenuDelete::PrintCharacters()
{
    const static std::string str = 
        "<#7F7F7F>-------------------------------------------------------------------------------\r\n"
        "<#FFFF00> Your Characters\r\n"
        "<#7F7F7F>-------------------------------------------------------------------------------\r\n";

    std::string chars = " 0   - Go Back\r\n";
    //chars += m_account.PrintCharacters();
    chars += 
        "<#7F7F7F>-------------------------------------------------------------------------------\r\n"
        "Enter number of character to delete: ";

    m_connection->Protocol().SendString( *m_connection, str + chars );
}



void TelnetMenuEnter::Handle( string p_data )
{
    // get the number the user typed.
    int option = BasicLib::totype<int>( p_data );
    
    // if 0, exit state
    if( option == 0 )
    {
        m_connection->RemoveHandler();
        return;
    }

    if( option > m_account.Characters() )
    {
        m_connection->Protocol().SendString( 
            *m_connection, 
            "<#FF0000>INVALID CHARACTER NUMBER\r\n"
            "<#FFFFFF>Enter Number of Character to use: " );
        return;
    }

    // grab the ID of the character you want to use.
    Account::characters::iterator itr = m_account.CharactersBegin();
    std::advance( itr, option - 1 );

    // remove this handler and go to the game
    m_connection->SwitchHandler( new TelnetGame( *m_connection, m_account.ID(), *itr ) );
}


void TelnetMenuEnter::PrintCharacters()
{
    const static std::string str = 
        "<#7F7F7F>-------------------------------------------------------------------------------\r\n"
        "<#FFFF00> Your Characters\r\n"
        "<#7F7F7F>-------------------------------------------------------------------------------\r\n";

    std::string chars = " 0 - Go Back\r\n";
    
    int index = 1;
    Account::characters::iterator itr = m_account.CharactersBegin();
    while( itr != m_account.CharactersEnd() )
    {
        chars += " " + BasicLib::tostring( index ) + " - ";
        character c( *itr );
        chars += c.Name() + "\r\n";
        index++;
        ++itr;
    }
    chars += 
        "<#7F7F7F>-------------------------------------------------------------------------------\r\n"
        "Enter number of character to use: ";

    m_connection->Protocol().SendString( *m_connection, str + chars );
}



}   // end namespace BetterMUD

