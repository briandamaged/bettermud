// MUD Programming
// Ron Penton
// (C)2003
// BetterTelnet.h - This is the header for the BETTER telnet policy class; it 
//                  is similar to the old telnet policy, but it does automatic
//                  BetterMUD color conversions.
//
//

#ifndef BETTERTELNET_H
#define BETTERTELNET_H

#include <string>
#include "SocketLib/SocketLib.h"


namespace BetterMUD
{

class BetterTelnet
{

public:
    // ------------------------------------------------------------------------
    //  this is the handler type used for the telnet protocol
    // ------------------------------------------------------------------------
    typedef SocketLib::ConnectionHandler<BetterTelnet, std::string> handler;
    typedef SocketLib::Connection<BetterTelnet> connection;

    // ------------------------------------------------------------------------
    //  Translates raw byte data into telnet data, and may send it out to
    //  the connection's current protocol handler
    // ------------------------------------------------------------------------
    void Translate( connection& p_conn, char* p_buffer, int p_size );

    // ------------------------------------------------------------------------
    //  This sends a plain text string to the connection, doing any translations
    //  if neccessary.
    // ------------------------------------------------------------------------
    void SendString( connection& p_conn, const std::string& p_string );

    // ------------------------------------------------------------------------
    //  Constructs the telnet policy.
    // ------------------------------------------------------------------------
    inline BetterTelnet()
    {
        m_buffersize = 0;
    }

    inline int Buffered()   { return m_buffersize; }


    // color conversion functions:

    static std::string TranslateColors(             // this translates BetterMUD
        const std::string& p_str );                 // color strings into telnet colors.

    static void TranslateStringColor(
        std::string::size_type i,                   // start of color
        std::string::size_type j,                   // end of color
        std::string& p_str );                       // string

    static void TranslateNumberColor(
        std::string::size_type i,                   // start of color
        std::string::size_type j,                   // end of color
        std::string& p_str );                       // string


protected:

    // This is the buffer that will contain all the processed telnet data
    char m_buffer[SocketLib::BUFFERSIZE];
    int m_buffersize;
};


}   // end namespace BetterMUD

#endif
