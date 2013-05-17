// MUD Programming
// Ron Penton
// (C)2003
// SocketLibSocket.h - This file contains the definitions for the three
// socket classes: Basic, Data, and Listening.


#ifndef SOCKETLIBSOCKET_H
#define SOCKETLIBSOCKET_H

// ========================================================================
//  Include Files
// ========================================================================
#include "BasicLib/BasicLib.h"
#include "SocketLibTypes.h"
#include "SocketLibErrors.h"


namespace SocketLib
{

    // ========================================================================
    // Class:       Socket
    // Purpose:     A very basic socket base class that will give the user
    //              the ability to get port and IP information, but not much
    //              else. 
    // ========================================================================
    class Socket
    {
    public:
        // ====================================================================
        // Function:    GetSock
        // Purpose:     this function returns the internal API socket 
        //              representation. Used by classes and functions that need
        //              to interface directly with the BSD Sockets or Winsock
        //              libraries.
        // ====================================================================
        inline sock GetSock() const
        {
            return m_sock;
        }


        // ====================================================================
        // Function:    GetLocalPort
        // Purpose:     gets the local port of the socket
        // ====================================================================
        inline port GetLocalPort() const
        {
            return ntohs( m_localinfo.sin_port );
        }

        // ====================================================================
        // Function:    GetLocalAddress
        // Purpose:     gets the local address of the socket
        // ====================================================================
        inline ipaddress GetLocalAddress() const
        {
            return m_localinfo.sin_addr.s_addr;
        }

        // ====================================================================
        // Function:    Close
        // Purpose:     closes the socket.
        // ====================================================================
        void Close();

        // ====================================================================
        // Function:    SetBlocking
        // Purpose:     sets whether the socket is blocking or not.
        // ====================================================================
        void SetBlocking( bool p_blockmode );

  

    protected:
        // ====================================================================
        // Function:    Socket
        // Purpose:     hidden constructor, meant to prevent people from
        //              instantiating this class. You should be using direct
        //              implementations of this class instead, such as 
        //              ListeningSocket and DataSocket.
        // ====================================================================
        Socket( sock p_socket = -1 );


        sock m_sock;                    // this is the underlying representation
                                        // of the actual socket.

        struct sockaddr_in m_localinfo; // structure containing information
                                        // about the local connection

        bool m_isblocking;              // this tells whether the socket is
                                        // blocking or not.
    };




    // ========================================================================
    // Class:       DataSocket
    // Purpose:     A variation of the BasicSocket base class that handles
    //              TCP/IP data connections.
    // ========================================================================
    class DataSocket : public Socket
    {
    public:
        // ====================================================================
        // Function:    DataSocket
        // Purpose:     Constructs the data socket with optional values
        // ====================================================================
        DataSocket( sock p_socket = -1 );

        // ====================================================================
        // Function:    GetRemoteAddress
        // Purpose:     get the IP address of the remote host.
        // ====================================================================
        inline ipaddress GetRemoteAddress() const
        {
            return m_remoteinfo.sin_addr.s_addr;
        }


        // ====================================================================
        // Function:    GetRemotePort
        // Purpose:     gets the remote port of the socket
        // ====================================================================
        inline port GetRemotePort() const
        {
            return ntohs( m_remoteinfo.sin_port );
        }


        // ====================================================================
        // Function:    IsConnected
        // Purpose:     Determines if the socket is connected or not.
        // ====================================================================
        inline bool IsConnected() const
        {
            return m_connected;
        }


        // ====================================================================
        // Function:    Connect
        // Purpose:     Connects this socket to another socket. This will fail
        //              if the socket is already connected, or the server
        //              rejects the connection.
        // ====================================================================
        void Connect( ipaddress p_addr, port p_port );

        // ====================================================================
        // Function:    Send
        // Purpose:     Attempts to send data, and returns the number of
        //              of bytes sent
        // ====================================================================
        int Send( const char* p_buffer, int p_size );

        // ====================================================================
        // Function:    Receive
        // Purpose:     Attempts to receive data from a socket, and returns the
        //              amount of data received.
        // ====================================================================
        int Receive( char* p_buffer, int p_size );

        // ====================================================================
        // Function:    Close
        // Purpose:     closes the socket.
        // ====================================================================
        void Close();

    protected:

        bool m_connected;               // is the socket connected?

        struct sockaddr_in m_remoteinfo;// structure containing information
        // about the remote connection

    };



    // ========================================================================
    // Class:       ListeningSocket
    // Purpose:     A variation of the BasicSocket base class that handles
    //              incomming TCP/IP connection requests.
    // ========================================================================
    class ListeningSocket : public Socket
    {
    public:

        // ====================================================================
        // Function:    ListeningSocket
        // Purpose:     Constructor. Constructs the socket with initial values
        // ====================================================================
        ListeningSocket();

        // ====================================================================
        // Function:    Listen
        // Purpose:     this function will tell the socket to listen on a 
        //              certain port 
        // p_port:      This is the port that the socket will listen on.
        // ====================================================================
        void Listen( port p_port );

        // ====================================================================
        // Function:    Accept
        // Purpose:     This is a blocking function that will accept an 
        //              incomming connection and return a data socket with info
        //              about the new connection.
        // ====================================================================
        DataSocket Accept();

        // ====================================================================
        // Function:    IsListening
        // Purpose:     Determines if the socket is listening or not.
        // ====================================================================
        inline bool IsListening() const
        {
            return m_listening;
        }


        // ====================================================================
        // Function:    Close
        // Purpose:     closes the socket.
        // ====================================================================
        void Close();

    protected:
        bool m_listening;               // is the socket listening?

    };


}   // end namespace SocketLib


#endif
