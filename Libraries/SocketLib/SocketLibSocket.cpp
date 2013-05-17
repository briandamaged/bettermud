// MUD Programming
// Ron Penton
// (C)2003
// SocketLibSocket.cpp - This file contains the definitions for the three
// socket classes: Basic, Data, and Listening.


#include <string.h>

#include "SocketLibSocket.h"

namespace SocketLib
{

    // ====================================================================
    // Function:    Close
    // Purpose:     closes the socket.
    // ====================================================================
    void Socket::Close()
    {

        // WinSock uses "closesocket" instead of "close", since it treats
        // sockets as completely separate objects to files, whereas unix
        // treats files and sockets exactly the same.
    #ifdef WIN32
        closesocket( m_sock );
    #else
        close( m_sock );
    #endif

        // invalidate the socket
        m_sock = -1;
    }

    // ====================================================================
    // Function:    SetBlocking
    // Purpose:     sets whether the socket is blocking or not.
    // ====================================================================
    void Socket::SetBlocking( bool p_blockmode )
    {
        int err;

        #ifdef WIN32
            unsigned long mode = !p_blockmode;
            err = ioctlsocket( m_sock, FIONBIO, &mode );
        #else
            // get the flags
            int flags = fcntl( m_sock, F_GETFL, 0 );

            // set or clear the non-blocking flag
            if( p_blockmode == false )
            {
                flags |= O_NONBLOCK;
            }
            else
            {
                flags &= ~O_NONBLOCK;
            }
            err = fcntl( m_sock, F_SETFL, flags );
        #endif

        if( err == -1 )
        {
            throw( Exception( GetError() ) );
        }

        m_isblocking = p_blockmode;
    }


    // ====================================================================
    // Function:    BasicSocket
    // Purpose:     hidden constructor, meant to prevent people from
    //              instantiating this class. You should be using direct
    //              implementations of this class instead, such as 
    //              ListeningSocket and DataSocket.
    // ====================================================================
    Socket::Socket( sock p_socket )
    : m_sock( p_socket )
    {
        if( p_socket != -1 )
        {
            socklen_t s = sizeof(m_localinfo);
            getsockname( p_socket, (sockaddr*)(&m_localinfo), &s );
        }

        // the socket is blocking by default
        m_isblocking = true;
    }



    // ====================================================================
    // Function:    DataSocket
    // Purpose:     Constructs the data socket with optional values
    // ====================================================================
    DataSocket::DataSocket( sock p_socket )
    : Socket( p_socket ),
    m_connected( false )
    {
        if( p_socket != -1 )
        {
            socklen_t s = sizeof(m_remoteinfo);
            getpeername( p_socket, (sockaddr*)(&m_remoteinfo), &s );
            m_connected = true;
        }
    }


    // ====================================================================
    // Function:    Connect
    // Purpose:     Connects this socket to another socket. This will fail
    //              if the socket is already connected, or the server
    //              rejects the connection.
    // ====================================================================
    void DataSocket::Connect( ipaddress p_addr, port p_port )
    {
        int err;

        // if the socket is already connected...
        if( m_connected == true )
        {
            throw Exception( EAlreadyConnected );
        }

        // first try to obtain a socket descriptor from the OS, if
        // there isn't already one.
        if( m_sock == -1 )
        {
            m_sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

            // throw an exception if the socket could not be created
            if( m_sock == -1 )
            {
                throw Exception( GetError() );
            }
        }

        // set up the socket address structure
        m_remoteinfo.sin_family = AF_INET;
        m_remoteinfo.sin_port = htons( p_port );
        m_remoteinfo.sin_addr.s_addr = p_addr;
        memset( &(m_remoteinfo.sin_zero), 0, 8 );

        // now the socket is created, so connect it.
        socklen_t s = sizeof(struct sockaddr);
        err = connect( m_sock, (struct sockaddr*)(&m_remoteinfo), s );
        if( err == -1 )
        {
            throw Exception( GetError() );
        }

        m_connected = true;

        // to get the local port, you need to do a little more work
        err = getsockname( m_sock, (struct sockaddr*)(&m_localinfo), &s );
        if( err != 0 )
        {
            throw Exception( GetError() );
        }
    }

    // ====================================================================
    // Function:    Send
    // Purpose:     Attempts to send data, and returns the number of
    //              of bytes sent
    // ====================================================================
    int DataSocket::Send( const char* p_buffer, int p_size )
    {
        int err;

        // make sure the socket is connected first.
        if( m_connected == false )
        {
            throw Exception( ENotConnected );
        }

        // attempt to send the data
        err = send( m_sock, p_buffer, p_size, 0 );
        if( err == -1 )
        {
            Error e = GetError();
            if( e != EOperationWouldBlock )
            {
                throw Exception( e );
            }

            // if the socket is nonblocking, we don't want to send a terminal
            // error, so just set the number of bytes sent to 0, assuming
            // that the client will be able to handle that.
            err = 0;
        }

        // return the number of bytes successfully sent
        return err;
    }

    // ====================================================================
    // Function:    Receive
    // Purpose:     Attempts to recieve data from a socket, and returns the
    //              amount of data received.
    // ====================================================================
    int DataSocket::Receive( char* p_buffer, int p_size )
    {
        int err;

        // make sure the socket is connected first.
        if( m_connected == false )
        {
            throw Exception( ENotConnected );
        }

        // attempt to recieve the data
        err = recv( m_sock, p_buffer, p_size, 0 );
        if( err == 0 )
        {
            throw Exception( EConnectionClosed );
        }
        if( err == -1 )
        {
            throw Exception( GetError() );
        }

        // return the number of bytes successfully recieved
        return err;
    }

    // ====================================================================
    // Function:    Close
    // Purpose:     closes the socket.
    // ====================================================================
    void DataSocket::Close()
    {
        if( m_connected == true )
        {
            shutdown( m_sock, 2 );
        }

        // close the socket
        Socket::Close();

        m_connected = false;
    }

    // ====================================================================
    // Function:    ListeningSocket
    // Purpose:     Constructor. Constructs the socket with initial values
    // ====================================================================
    ListeningSocket::ListeningSocket()
    {
        m_listening = false;
    }

    // ====================================================================
    // Function:    Listen
    // Purpose:     this function will tell the socket to listen on a 
    //              certain port 
    // p_port:      This is the port that the socket will listen on.
    // ====================================================================
    void ListeningSocket::Listen( port p_port )
    {
        int err;

        // first try to obtain a socket descriptor from the OS, if
        // there isn't already one.
        if( m_sock == -1 )
        {
            m_sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

            // throw an exception if the socket could not be created
            if( m_sock == -1 )
            {
                throw Exception( GetError() );
            }
        }

        // set the SO_REUSEADDR option on the socket, so that it doesn't
        // hog the port after it closes.
        int reuse = 1;
        err = setsockopt( m_sock, SOL_SOCKET, SO_REUSEADDR, 
                          (char*)(&reuse), sizeof( reuse ) );
        if( err != 0 )
        {
            throw Exception( GetError() );
        }

        // set up the socket address structure
        m_localinfo.sin_family = AF_INET;
        m_localinfo.sin_port = htons( p_port );
        m_localinfo.sin_addr.s_addr = htonl( INADDR_ANY );
        memset( &(m_localinfo.sin_zero), 0, 8 );

        // bind the socket
        err = bind( m_sock, (struct sockaddr*)&m_localinfo, 
            sizeof(struct sockaddr));
        if( err == -1 )
        {
            throw Exception( GetError() );
        }

        // now listen on the socket. There is a very high chance that this will
        // be successful if it got to this point, but always check for errors
        // anyway. Set the queue to 8; a reasonable number.
        err = listen( m_sock, 8 );
        if( err == -1 )
        {
            throw Exception( GetError() );
        }

        m_listening = true;
    }


    // ====================================================================
    // Function:    Accept
    // Purpose:     This is a blocking function that will accept an 
    //              incomming connection and return a data socket with info
    //              about the new connection.
    // ====================================================================
    DataSocket ListeningSocket::Accept()
    {
        sock s;
        struct sockaddr_in socketaddress;

        // try to accept a connection
        socklen_t size = sizeof(struct sockaddr);
        s = accept( m_sock, (struct sockaddr*)&socketaddress, &size );
        if( s == -1 )
        {
            throw Exception( GetError() );
        }

        // return the newly created socket.
        return DataSocket( s );
    }


    // ====================================================================
    // Function:    Close
    // Purpose:     closes the socket.
    // ====================================================================
    void ListeningSocket::Close()
    {
        // close the socket
        Socket::Close();

        // invalidate the variables
        m_listening = false;
    }

}   // end namespace SocketLib
