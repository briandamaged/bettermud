// MUD Programming
// Ron Penton
// (C)2003
// TelnetReporter.cpp - This file contains the telnet reporter class, which
//                      reports BetterMUD events to a telnet connection
// 
// 



#include "TelnetReporter.h"
#include "../accessors/Accessors.h"
#include "../Game.h"

using namespace SocketLib;

namespace BetterMUD
{


int TelnetReporter::DoAction( const Action& p_action )
{
    // someone entered a room
    if( p_action.actiontype == "enterroom" )
    {
        EnterRoom( p_action.data1, p_action.data2 );
    }


    // someone left a room
    else if( p_action.actiontype == "leaveroom" )
    {
        LeaveRoom( p_action.data1, p_action.data2 );
    }


    // someone said something
    else if( p_action.actiontype == "say" )
    {
        character c( p_action.data1 );
        SendString( 
            "<$yellow>" + c.Name() + 
            " says: <$reset>" + p_action.stringdata );
    }


    // you see a room
    else if( p_action.actiontype == "seeroom" )
    {
        SeeRoom( p_action.data1 );
    }


    // you see a room name
    else if( p_action.actiontype == "seeroomname" )
    {
        SeeRoomName( p_action.data1 );
    }


    // you see a room descrioption
    else if( p_action.actiontype == "seeroomdescription" )
    {
        SeeRoomDesc( p_action.data1 );
    }


    // you see a room's exits
    else if( p_action.actiontype == "seeroomexits" )
    {
        SeeRoomExits( p_action.data1 );
    }


    // you see a room's characters
    else if( p_action.actiontype == "seeroomcharacters" )
    {
        SeeRoomCharacters( p_action.data1 );
    }


    // you see a room's items
    else if( p_action.actiontype == "seeroomitems" )
    {
        SeeRoomItems( p_action.data1 );
    }


    // you left the game
    else if( p_action.actiontype == "leave" )
    {
        m_conn->RemoveHandler();
    }


    // you hung up
    else if( p_action.actiontype == "hangup" )
    {
        m_conn->Close();
        m_conn->ClearHandlers();
    }


    // you got an error
    else if( p_action.actiontype == "error" )
    {
        SendString( "<$bold><$red>" + p_action.stringdata );
    }


    // you saw an announcement
    else if( p_action.actiontype == "announce" )
    {
        SendString( "<$bold><$cyan>" + p_action.stringdata );
    }


    // you saw something
    else if( p_action.actiontype == "vision" )
    {
        SendString( "<$bold><$green>" + p_action.stringdata );
    }


    // you heard someone chatting
    else if( p_action.actiontype == "chat" )
    {
        character c( p_action.data1 );
        SendString( 
            "<$bold><$magenta>" + c.Name() + 
            " chats: <$reset>" + p_action.stringdata );
    }



    // someone whispered to you
    else if( p_action.actiontype == "whisper" )
    {
        character c( p_action.data1 );
        SendString( 
            "<$bold><$yellow>" + c.Name() + 
            " whispers to you: <$reset>" + p_action.stringdata );
    }



    // someone entered the realm
    else if( p_action.actiontype == "enterrealm" )
    {
        character c( p_action.data1 );
        SendString( 
            "<$bold><$white>" + c.Name() + " enters the realm." );
    }


    // someone left the realm
    else if( p_action.actiontype == "leaverealm" )
    {
        character c( p_action.data1 );
        SendString( 
            "<$bold><$white>" + c.Name() + " leaves the realm." );
    }


    // some poor sap died
    else if( p_action.actiontype == "die" )
    {
        Died( p_action.data1 );
    }

    // someone gave an item to someone else
    else if( p_action.actiontype == "giveitem" )
    {
        GaveItem( p_action.data1, p_action.data2, p_action.data3 );
    }


    // someone dropped an item
    else if( p_action.actiontype == "dropitem" )
    {
        DropItem( p_action.data1, p_action.data2 );
    }

    // someone picked up an item
    else if( p_action.actiontype == "getitem" )
    {
        GetItem( p_action.data1, p_action.data2 );
    }


    return 0;
}


void TelnetReporter::SeeRoom( entityid p_id )
{
    character c( m_id );

    SeeRoomName( p_id );
    if( c.Verbose() == true )
        SeeRoomDesc( p_id );
    SeeRoomExits( p_id );
    SeeRoomCharacters( p_id );
    SeeRoomItems( p_id );
}

void TelnetReporter::SeeRoomName( entityid p_id )
{
    room r( p_id );
    SendString( "<#FFFFFF>" + r.Name() );
}

void TelnetReporter::SeeRoomDesc( entityid p_id )
{
    room r( p_id );
    SendString( "<$reset>" + r.Description() );
}

void TelnetReporter::SeeRoomExits( entityid p_id )
{
    room r( p_id );
    if( r.Portals() == 0 )
        return;
 
    std::string str = "<#FF00FF>Exits: <$reset>";

    r.BeginPortal();
    while( r.IsValidPortal() )
    {
        // seek the portal object's iterator to the desired portal entry
        portal p( r.CurrentPortal() );
        p.SeekStartRoom( p_id );
        
        // write out the portal direction and name
        str += p.CurrentDirection();
        str += " - ";
        str += p.Name();
        str += "<#FF00FF>, <$reset>";
        r.NextPortal();
    }

    str.erase( str.size() - 19, 19 );
    SendString( str );

}

void TelnetReporter::SeeRoomCharacters( entityid p_id )
{
    room r( p_id );
    if( r.Characters() == 0 )
        return;

    std::string str = "<#FFFF00>People: <$reset>";
    r.BeginCharacter();
    while( r.IsValidCharacter() )
    {
        character c( r.CurrentCharacter() );
        str += c.Name();
        str += "<#FFFF00>, <$reset>";
        r.NextCharacter();
    }

    str.erase( str.size() - 19, 19 );
    SendString( str );
}


void TelnetReporter::SeeRoomItems( entityid p_id )
{
    room r( p_id );
    if( r.Items() == 0 )
        return;

    std::string str = "<#00FF00>Items: <$reset>";
    r.BeginItem();
    while( r.IsValidItem() )
    {
        item i( r.CurrentItem() );
        str += i.Name();
        str += "<#00FF00>, <$reset>";
        r.NextItem();
    }

    str.erase( str.size() - 19, 19 );
    SendString( str );
}

void TelnetReporter::EnterRoom( entityid p_character, entityid p_portal )
{
    character c( p_character );
    if( p_character == m_id )
    {
        SeeRoom( c.Room() );
        return;
    }
    
    if( p_portal == 0 )
    {
        SendString( "<$bold><$white>" + c.Name() + " appears from nowhere!" );
        return;
    }

    portal p( p_portal );
    SendString( "<$bold><$white>" + c.Name() + " enters from the " +
                p.Name() + "." );
    
}

void TelnetReporter::LeaveRoom( entityid p_character, entityid p_portal )
{
    character c( p_character );
    if( p_character == m_id )
    {
        if( p_portal == 0 )
        {
            SendString( "<$bold><$white>You disappear!" );
            return;
        }
        
        portal e( p_portal );
        SendString( "<$bold><$white>You enter the " + e.Name() );
        return;

    }
    
    if( p_portal == 0 )
    {
        SendString( "<$bold><$white>" + c.Name() + " disappears!" );
        return;
    }

    portal p( p_portal );
    SendString( "<$bold><$white>" + c.Name() + " enters the " +
                p.Name() + "." );
}


void TelnetReporter::Died( entityid p_character )
{
    std::string str = "<$bold><$red>";
    character c( p_character );

    if( c.ID() != m_id )
    {
        str += c.Name();
        str += " HAS DIED!!!";
    }
    else
    {
        str += "YOU HAVE DIED!!!";
    }
    SendString( str );
}


void TelnetReporter::GetItem( entityid p_character, entityid p_item )
{
    std::string str = "<$bold><$yellow>";
    if( p_character == m_id )
    {
        str += "You pick up ";
    }
    else
    {
        character c( p_character );
        str += c.Name();
        str += " picks up ";
    }
    item i( p_item );
    str += i.Name();
    SendString( str );
}


void TelnetReporter::DropItem( entityid p_character, entityid p_item )
{
    std::string str = "<$bold><$yellow>";
    if( p_character == m_id )
    {
        str += "You drop ";
    }
    else
    {
        character c( p_character );
        str += c.Name();
        str += " drops ";
    }
    item i( p_item );
    str += i.Name();
    SendString( str );
}




void TelnetReporter::GaveItem( 
    entityid p_giver, 
    entityid p_receiver, 
    entityid p_item )
{
    std::string str = "<$bold><$yellow>";
    if( p_giver == m_id )
    {
        str += "You give ";
    }
    else
    {
        character g( p_giver );
        str += g.Name();
        str += " gives ";
    }

    item i( p_item );
    str += i.Name();
    str += " to ";

    if( p_receiver == m_id )
    {
        str += "you.";
    }
    else
    {
        character r( p_receiver );
        str += r.Name();
        str += ".";
    }

    SendString( str );
}



void TelnetReporter::SendString( const std::string& p_string )
{
    m_conn->Protocol().SendString( *m_conn, p_string + "<$reset>\r\n" );
}


}   // end namespace BetterMUD
