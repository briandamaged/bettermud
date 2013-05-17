// MUD Programming
// Ron Penton
// (C)2003
// Connection.h - This file contains the header for the Connection class,
//                which is an advanced version of a data socket.
//                Connections have functions for data flow management and
//                buffering. To properly use the buffering features,
//                the socket must be set to non-blocking mode.


#ifndef CONNECTION_H
#define CONNECTION_H

#include <stack>
#include "BasicLib/BasicLib.h"
#include "SocketLibTypes.h"
#include "ConnectionManager.h"
#include "SocketLibSocket.h"

namespace SocketLib
{

// This is the default buffer size of the connection class
const static int BUFFERSIZE = 1024;
const static int TIMECHUNK = 16;

template< class protocol >
class Connection : public DataSocket
{

public:
    // ------------------------------------------------------------------------
    // Constructors. One constructs a normal connection, and the other accepts
    // a DataSocket to use as a "template" for the connection
    // ------------------------------------------------------------------------
    Connection();
    Connection( DataSocket& p_socket );

protected:
    void Initialize();


public:

    // ------------------------------------------------------------------------
    // This gets the amount of time that has passed, in seconds, since the
    // last time data was successfully sent, if there is data still queued,
    // or 0 if there is no data queued. This allows the server to check for
    // deadlocked clients (ie: a client crashed and is not receiving data).
    // ------------------------------------------------------------------------
    BasicLib::sint64 GetLastSendTime() const;
    
    // ------------------------------------------------------------------------
    // Gets the amount of time in seconds since data was last received.
    // ------------------------------------------------------------------------
    inline BasicLib::sint64 GetLastReceiveTime() const
    {
        return m_lastReceiveTime;
    }


    // ------------------------------------------------------------------------
    // This "closes" the connection. This just sets a boolean telling the
    // connection that it should be closed when the connection manager
    // gets to it.
    // ------------------------------------------------------------------------
    inline void Close()     { m_closed = true; }

    // ------------------------------------------------------------------------
    // This physically closes the underlying socket.
    // ------------------------------------------------------------------------
    inline void CloseSocket() 
    { 
        DataSocket::Close(); 

        // tell the top handler (if it exists) that the connection has left
        // that state
        ClearHandlers();
    }

    // ------------------------------------------------------------------------
    // This puts data into the sending queue.
    // ------------------------------------------------------------------------
    void BufferData( const char* p_buffer, int p_size );

    // ------------------------------------------------------------------------
    // This sends the contents of the send buffer
    // ------------------------------------------------------------------------
    void SendBuffer();

    // ------------------------------------------------------------------------
    // This receives a buffer of data, and sends it off to the protocol to be
    // translated.
    // ------------------------------------------------------------------------
    void Receive();


    // ------------------------------------------------------------------------
    // This gets the receiving datarate for the socket, in bytes per
    // second, calculated over the previous interval
    // ------------------------------------------------------------------------
    inline int GetDataRate() const
    {
        return m_lastdatarate;
    }

    // ------------------------------------------------------------------------
    // This gets the current receiving datarate for the socket, in bytes per
    // second.
    // ------------------------------------------------------------------------
    inline int GetCurrentDataRate() const
    {
        return m_datarate / TIMECHUNK;
    }

    // ------------------------------------------------------------------------
    // Gets the amount of bytes within the sending buffer.
    // ------------------------------------------------------------------------
    inline int GetBufferedBytes() const
    {
        return (int)m_sendbuffer.size();
    }

    inline BasicLib::sint64 GetCreationTime() const
    {
        return m_creationtime;
    }

    inline protocol& Protocol()         { return m_protocol; }
    inline bool Closed()                { return m_closed; }

    inline void SwitchHandler( typename protocol::handler* p_handler )
    {
        if( Handler() )
        {
            Handler()->Leave();     // leave the current state if it exists
            delete Handler();       // delete state
            m_handlerstack.pop();   // pop the pointer off
        }

        m_handlerstack.push( p_handler );
        p_handler->Enter();     // enter the new state
    }

    inline void AddHandler( typename protocol::handler* p_handler )
    {
        if( Handler() )
            Handler()->Leave(); // leave the current state if it exists
        m_handlerstack.push( p_handler );
        p_handler->Enter();     // enter the new state
    }

    inline void RemoveHandler()
    {
        Handler()->Leave();     // leave current state
        delete Handler();       // delete state
        m_handlerstack.pop();   // pop the pointer off
        if( Handler() )         // if old state exists, 
            Handler()->Enter(); // tell it connection has re-entered
    }


    inline typename protocol::handler* Handler()
    {
        if( m_handlerstack.size() == 0 )
            return 0;
        return m_handlerstack.top();
    }


    void ClearHandlers()
    {
        // leave the current handler
        if( Handler() )  
            Handler()->Leave();

        // delete all the handlers on the stack
        while( Handler() )
        {
            delete Handler();
            m_handlerstack.pop();
        }
    }



protected:


    // This is the protocol object that will manage data when it is received.
    protocol m_protocol;

    // This stack manages the current data handler. When data is received,
    // it is sent off to the protocol policy object, which in turn sends it
    // to the handler on the top of this stack.
    std::stack< typename protocol::handler* > m_handlerstack;

    // This buffer stores all the data to be sent at a later time.
    std::string m_sendbuffer;

    // This is the amount of data received during the current chunk of time
    int m_datarate;

    // This is the amount of data that was received during the last chunk of
    // time
    int m_lastdatarate;

    // This represents the last time data was successfully received on the
    // connection, in seconds.
    BasicLib::sint64 m_lastReceiveTime;

    // The last time data was successfully sent.
    BasicLib::sint64 m_lastSendTime;

    // the time at which the connection was created; in seconds
    BasicLib::sint64 m_creationtime;

    // This boolean is used to determine if the send time should be checked 
    // when the GetLastSendTime function is invoked. When false, it is safe to 
    // assume that even if there is data in the queue, there have been no 
    // problems sending it thus far.
    bool m_checksendtime;

    char m_buffer[BUFFERSIZE];

    // determines whether or not the connection has been closed.
    bool m_closed;
};





// ------------------------------------------------------------------------
// Constructors. One constructs a normal connection, and the other accepts
// a DataSocket to use as a "template" for the connection
// ------------------------------------------------------------------------
template< class protocol >
Connection<protocol>::Connection()
{
    Initialize();
}

template< class protocol >
Connection<protocol>::Connection( DataSocket& p_socket )
    : DataSocket( p_socket )
{
    Initialize();
}


template< class protocol >
void Connection<protocol>::Initialize()
{
    m_datarate = 0;
    m_lastdatarate = 0;
    m_lastReceiveTime = 0;
    m_lastSendTime = 0;
    m_checksendtime = false;
    m_creationtime = BasicLib::GetTimeMS();
    m_closed = false;
}

// ------------------------------------------------------------------------
// This gets the amount of time that has passed, in seconds, since the
// last time data was successfully sent, if there is data still queued,
// or 0 if there is no data queued. This allows the server to check for
// deadlocked clients (ie: a client crashed and is not receiving data).
// ------------------------------------------------------------------------
template< class protocol >
BasicLib::sint64 Connection<protocol>::GetLastSendTime() const
{
    if( m_checksendtime )
    {
        return BasicLib::GetTimeS() - m_lastSendTime;
    }

    return 0;
}


// ------------------------------------------------------------------------
// This puts data into the sending queue.
// ------------------------------------------------------------------------
template< class protocol >
void Connection<protocol>::BufferData( const char* p_buffer, int p_size )
{
    m_sendbuffer.append( p_buffer, p_size );
}

// ------------------------------------------------------------------------
// This sends the contents of the send buffer
// ------------------------------------------------------------------------
template< class protocol >
void Connection<protocol>::SendBuffer()
{
    if( m_sendbuffer.size() > 0 )
    {
        // send the data, and erase as much as was sent from the buffer.
        int sent = Send( m_sendbuffer.data(), (int)m_sendbuffer.size() );
        m_sendbuffer.erase( 0, sent );

        if( sent > 0 )
        {
            // since data was sent successfully, reset the send time.
            m_lastSendTime = BasicLib::GetTimeS();
            m_checksendtime = false;
        }
        else
        {
            // no data was sent, so mark down that the sending time
            // needs to be checked, to see if the socket is entering
            // client deadlock
            if( !m_checksendtime )
            {
                // if execution gets here, that means that this connection
                // has previously not had any problems sending data, so
                // mark down the time that the sending problem started.
                // note that it may have started earlier, but since we didn't
                // start sending data earlier, there really is no way to know
                // for sure when it started.
                m_checksendtime = true;
                m_lastSendTime = BasicLib::GetTimeS();

            }
        }   // end no-data-sent check

    }   // end buffersize check
}

// ------------------------------------------------------------------------
// This receives a buffer of data and returns the number of bytes
// received. A return value of 0 is valid.
// ------------------------------------------------------------------------
template< class protocol >
void Connection<protocol>::Receive()
{
    // receive the data
    int bytes = DataSocket::Receive( m_buffer, BUFFERSIZE );

    // get the current time
    BasicLib::sint64 t = BasicLib::GetTimeS();

    // check to see if we've reached the next X seconds of time (see Chapter 5)
    // and if so, clear the datarate.
    if( (m_lastReceiveTime / TIMECHUNK) != (t / TIMECHUNK) )
    {
        m_lastdatarate = m_datarate / TIMECHUNK;
        m_datarate = 0;
        m_lastReceiveTime = t;
    }

    m_datarate += bytes;

    // tell the protocol policy object about the received data.
    m_protocol.Translate( *this, m_buffer, bytes );
}


}   // end namespace socketlib


#endif
