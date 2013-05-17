// MUD Programming
// Ron Penton
// (C)2003
// TelnetReporter.h - This file contains the telnet reporter class, which
//                    reports BetterMUD events to a telnet connection
// 
// 


#ifndef BETTERMUDTELNETREPORTER_H
#define BETTERMUDTELNETREPORTER_H

#include "SocketLib/SocketLib.h"
#include "../scripts/Logic.h"
#include "BetterTelnet.h"
#include "../Exception.h"

using SocketLib::Connection;
using SocketLib::Telnet;

namespace BetterMUD
{

// ----------------------------------------------------------------------------
//  This is an abstract class that will act as an intermediary between char's
//  and their connections. Basically, it is told what actions the char has
//  "Sees"
// ----------------------------------------------------------------------------
class TelnetReporter : public Logic
{
public:
    TelnetReporter( 
        entityid p_id,                              // ID of character
        Connection<BetterTelnet>* p_conn )          // address of connection 
        : m_id( p_id ),
          m_conn( p_conn )    {}

    
    std::string Name() { return "telnetreporter"; }
    bool CanSave() { return false; }

    int DoAction( const Action& p_action );

protected:
    void SeeRoom( entityid p_id );
    void SeeRoomName( entityid p_id );
    void SeeRoomDesc( entityid p_id );
    void SeeRoomExits( entityid p_id );
    void SeeRoomCharacters( entityid p_id );
    void SeeRoomItems( entityid p_id );

    void EnterRoom( entityid p_character, entityid p_portal );
    void LeaveRoom( entityid p_character, entityid p_portal );
    void Died( entityid p_character );

    void GetItem( entityid p_character, entityid p_item );
    void DropItem( entityid p_character, entityid p_item );
    void GaveItem( entityid p_giver, entityid p_receiver, entityid p_item );

    // ------------------------------------------------------------------------
    //  Helper, sends a string to a connection.
    // ------------------------------------------------------------------------
    void SendString( const std::string& p_string );

protected:
    SocketLib::Connection<BetterTelnet>* m_conn;          // connection of the object
    entityid m_id;
};  // end class TelnetReporter


}   // end namespace BetterMUD


#endif
