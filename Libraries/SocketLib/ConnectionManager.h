// MUD Programming
// Ron Penton
// (C)2003
// ConnectionManager.h - The class that will manage connections.

#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <list>
#include <iostream>

#include "ThreadLib/ThreadLib.h"
#include "SocketLibTypes.h"
#include "SocketLibErrors.h"
#include "SocketSet.h"
#include "Connection.h"



namespace SocketLib
{

// Forward Declarations
template<typename protocol>
class Connection;



// ============================================================================
// Description: This connection manager class will manage connections, 
// all identified with an ID. 
// ============================================================================
template<typename protocol, typename defaulthandler>
class ConnectionManager
{

    typedef          std::list< Connection<protocol> >           clist;
    typedef typename std::list< Connection<protocol> >::iterator clistitr;

public:
    // ------------------------------------------------------------------------
    // This creates a connection manager using a maximum datarate, buffer size,
    // and a send timeout limit.
    // ------------------------------------------------------------------------
    ConnectionManager( int p_maxdatarate = 1024,    // 1 kbyte/second
                       int p_sentimeout = 60,       // 60 seconds
                       int p_maxbuffered = 8192 );  // 8 kbytes

    // ------------------------------------------------------------------------
    //  Destructs the manager, closing every connection contained within.
    // ------------------------------------------------------------------------
    ~ConnectionManager();


    // ------------------------------------------------------------------------
    //  This notifies the manager that there is a new connection available
    // ------------------------------------------------------------------------
    void NewConnection( DataSocket& p_socket );


    // ------------------------------------------------------------------------
    //  This returns the number of connections that can be added to the manager
    // ------------------------------------------------------------------------
    inline int AvailableConnections() const
    {
        return MAX - (int)m_connections.size();
    }

    // ------------------------------------------------------------------------
    //  This returns the number of connections within the manager
    // ------------------------------------------------------------------------
    inline int TotalConnections() const
    {
        return (int)m_connections.size();
    }

    // ------------------------------------------------------------------------
    //  Goes through all the connections in the close-queue, and closes them.
    // ------------------------------------------------------------------------
    void CloseConnections();


    // ------------------------------------------------------------------------
    // Description: This listens for incomming data
    // ------------------------------------------------------------------------
    void Listen();

    // ------------------------------------------------------------------------
    // Description: This goes through all the connections and sends all
    //              buffered data.
    // ------------------------------------------------------------------------
    void Send();

    // ------------------------------------------------------------------------
    // This function performs the three actions of the manager class, listening
    // sending, and closing.
    // ------------------------------------------------------------------------
    inline void Manage()
    {
        Listen();
        Send();
        CloseConnections();
    }

protected:
    // ------------------------------------------------------------------------
    //  This closes a connection within the connection manager; it is assumed
    //  that this is an external call- nothing needs to be notified about 
    //  the connection being closed.
    // ------------------------------------------------------------------------
    void Close( clistitr p_itr );



protected:

    // a list of all the connections within the manager
    clist m_connections;

    // This is the max allowable receiving datarate of the manager, in bytes per
    // second.
    int m_maxdatarate;

    // This is the amount of time in seconds that the manager allows for a socket to
    // successfully send data before it is forcibly closed.
    int m_sendtimeout;

    // This is the maximum number of bytes that are allowed to be buffered by
    // a connection before it is forcibly closed (only determined after a send)
    int m_maxbuffered;

    // a set of sockets that will be polled for socket activity.
    SocketSet m_set;
};





// ------------------------------------------------------------------------
// This creates a connection manager using a maximum datarate, buffer size,
// and a send timeout limit.
// ------------------------------------------------------------------------
template<typename protocol, typename defaulthandler>
ConnectionManager<protocol, defaulthandler>::
ConnectionManager( int p_maxdatarate,    
                   int p_sentimeout,
                   int p_maxbuffered )
{
    m_maxdatarate = p_maxdatarate;
    m_sendtimeout = p_sentimeout;
    m_maxbuffered = p_maxbuffered;
}

// ------------------------------------------------------------------------
//  Destructs the manager, closing every connection contained within.
// ------------------------------------------------------------------------
template<typename protocol, typename defaulthandler>
ConnectionManager<protocol, defaulthandler>::~ConnectionManager()
{
    // close every socket in the manager
    clistitr itr;

    for( itr = m_connections.begin(); itr != m_connections.end(); ++itr )
        itr->CloseSocket();
}



// ------------------------------------------------------------------------
//  This notifies the manager that there is a new connection available
// ------------------------------------------------------------------------
template<typename protocol, typename defaulthandler>
void ConnectionManager<protocol, defaulthandler>::
NewConnection( DataSocket& p_socket )
{

    // turn the socket into a connection
    Connection<protocol> conn( p_socket );

    if( AvailableConnections() == 0 )
    {
        // tell the default protocol handler that there is no more room
        // for the connection within this manager.
        defaulthandler::NoRoom( conn );

        // It is assumed that the protocol handler has told the connection the 
        // appropriate message, so close the connection.
        conn.CloseSocket();
    }
    else
    {
        // add the connection
        m_connections.push_back( conn );

        // get a ref pointing to the connection
        Connection<protocol>& c = *m_connections.rbegin();

        // turn the connection into nonblocking mode
        c.SetBlocking( false );

        // add the connection to the socket set
        m_set.AddSocket( c );

        // give the connection its default handler
        c.AddHandler( new defaulthandler( c ) );

    }
}


// ------------------------------------------------------------------------
//  This physically closes a connection within the connection manager
// ------------------------------------------------------------------------
template<typename protocol, typename defaulthandler>
void ConnectionManager<protocol, defaulthandler>::Close( clistitr p_itr )
{
    // clear the socket descriptor from the socket set
    m_set.RemoveSocket( *p_itr );

    // physically close the connection
    p_itr->CloseSocket();

    // erase the connection from the list
    m_connections.erase( p_itr );
}





// ------------------------------------------------------------------------
// This determines if any sockets need to be listened on.
// ------------------------------------------------------------------------
template<typename protocol, typename defaulthandler>
void ConnectionManager<protocol, defaulthandler>::Listen()
{
    int socks = 0;
    if( TotalConnections() > 0 )
    {
        socks = m_set.Poll();
    }

    // detect if any sockets have action on them
    if( socks > 0 )
    {

        // two iterators; c means "current". This is done due to the 
        // awkward nature of iterating through a map with the 
        // ability to remove items
        clistitr itr = m_connections.begin();
        clistitr c;

        // loop through every connection
        while( itr != m_connections.end() )
        {
            // keep the current connection in "c", and move "itr" to 
            // the next item
            c = itr++;

            // check if there is any activity
            if( m_set.HasActivity( *c ) )
            {
                try
                {
                    // receive as much data as you can.
                    c->Receive();

                    // check to see if the connection is flooding.
                    if( c->GetCurrentDataRate() > m_maxdatarate )
                    {
                        // too much data was sent, tell the
                        // protocol handler
                        c->Close();
                        c->Handler()->Flooded();

                        // close the connection
                        Close( c );
                    }
                }

                // this block catches any fatal exceptions that
                // were thrown when receiving new data. The only
                // exceptions thrown are major errors, and the 
                // socket should immediately be closed. So,
                // the protocol handler is told that the connection
                // hung up, and the socket is closed.
                catch( ... )
                {
                    c->Close();
                    c->Handler()->Hungup();
                    Close( c );
                }

            }   // end activity check

        }   // end socket loop

    }   // end check for number of sockets returned by select()
}


// ------------------------------------------------------------------------
// Description: This goes through all the connections and sends all
//              buffered data.
// ------------------------------------------------------------------------
template<typename protocol, typename defaulthandler>
void ConnectionManager<protocol, defaulthandler>::Send()
{
    // uses the same method as previously shown; keeps two iterators
    // due to being able to remove items
    clistitr itr = m_connections.begin();
    clistitr c;

    // loop through every connection
    while( itr != m_connections.end() )
    {
        // move "itr" to the next connection, but keep "c" on the current
        // connection.
        c = itr++;

        // now try to send all buffered data on the socket.
        try
        {
            c->SendBuffer();

            // check to see if there are problems sending to the connection
            // these are usually caused by exploits or client crashes.
            if( c->GetBufferedBytes() > m_maxbuffered || 
                c->GetLastSendTime() > m_sendtimeout )
            {
                c->Close();
                c->Handler()->Hungup();
                Close( c );
            }
        }
        catch( ... )
        {
            c->Close();
            c->Handler()->Hungup();
            Close( c );
        }
    }   // end while-loop
}



// ------------------------------------------------------------------------
//  Goes through all the connections in the manager and checks if they
//  need to be closed.
// ------------------------------------------------------------------------
template<typename protocol, typename defaulthandler>
void ConnectionManager<protocol, defaulthandler>::CloseConnections()
{
    clistitr itr = m_connections.begin();
    clistitr c;

    while( itr != m_connections.end() )
    {
        // retain the value of the iterator in "c" while moving "itr" forward
        c = itr++;

        if( c->Closed() )
            Close( c );
    }
}


}   // end namespace SocketLib

#endif
