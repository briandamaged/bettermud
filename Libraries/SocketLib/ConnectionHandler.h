// MUD Programming
// Ron Penton
// (C)2003
// ConnectionHandler.h - This is a generic interface class designed to handle
//                       data from a connection policy class.


#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include "SocketLibTypes.h"
#include "Connection.h"


namespace SocketLib
{

template<typename protocol, typename command>
class ConnectionHandler
{

public:

    typedef Connection<protocol> conn;

    // ------------------------------------------------------------------------
    //  Constructor, records pointer to the connection.
    // ------------------------------------------------------------------------
    ConnectionHandler( conn& p_conn ) : m_connection( &p_conn ) {}
    virtual ~ConnectionHandler() {};

    // ------------------------------------------------------------------------
    //  This handles incomming commands. Anything passed into this function
    //  is assumed to be a complete command from a client.
    // ------------------------------------------------------------------------
    virtual void Handle( command p_data ) = 0;

    // ------------------------------------------------------------------------
    //  This notifies the handler that a connection is entering the state
    // ------------------------------------------------------------------------
    virtual void Enter() = 0;

    // ------------------------------------------------------------------------
    //  This notifies the handler that a connection is leaving the state.
    // ------------------------------------------------------------------------
    virtual void Leave() = 0;

    // ------------------------------------------------------------------------
    //  This notifies the handler that a connection has unexpectedly hung up.
    // ------------------------------------------------------------------------
    virtual void Hungup() = 0;

    // ------------------------------------------------------------------------
    //  This notifies the handler that a connection is being kicked due to 
    //  flooding the server.
    // ------------------------------------------------------------------------
    virtual void Flooded() = 0;

protected:
    conn* m_connection;

};


}   // end namespace SocketLib
#endif
