// MUD Programming
// Ron Penton
// (C)2003
// Telnet.h - This is the header for the telnet policy class; it receives raw 
//            data from a connection and strips out or takes care of any 
//            command codes.


#ifndef TELNET_H
#define TELNET_H

#include <string>
#include "SocketLibTypes.h"
#include "Connection.h"
#include "ConnectionHandler.h"

namespace SocketLib
{
const std::string reset = "\x1B[0m";
const std::string bold = "\x1B[1m";
const std::string dim = "\x1B[2m";
const std::string under = "\x1B[4m";
const std::string reverse = "\x1B[7m";
const std::string hide = "\x1B[8m";

const std::string clearscreen = "\x1B[2J";
const std::string clearline = "\x1B[2K";

const std::string black = "\x1B[30m";
const std::string red = "\x1B[31m";
const std::string green = "\x1B[32m";
const std::string yellow = "\x1B[33m";
const std::string blue = "\x1B[34m";
const std::string magenta = "\x1B[35m";
const std::string cyan = "\x1B[36m";
const std::string white = "\x1B[37m";

const std::string bblack = "\x1B[40m";
const std::string bred = "\x1B[41m";
const std::string bgreen = "\x1B[42m";
const std::string byellow = "\x1B[43m";
const std::string bblue = "\x1B[44m";
const std::string bmagenta = "\x1B[45m";
const std::string bcyan = "\x1B[46m";
const std::string bwhite = "\x1B[47m";

const std::string newline = "\r\n\x1B[0m";


class Telnet
{

public:
    // ------------------------------------------------------------------------
    //  this is the handler type used for the telnet protocol
    // ------------------------------------------------------------------------
    typedef ConnectionHandler<Telnet, std::string> handler;

    // ------------------------------------------------------------------------
    //  Translates raw byte data into telnet data, and may send it out to
    //  the connection's current protocol handler
    // ------------------------------------------------------------------------
    void Translate( Connection<Telnet>& p_conn, char* p_buffer, int p_size );

    // ------------------------------------------------------------------------
    //  This sends a plain text string to the connection, doing any translations
    //  if neccessary.
    // ------------------------------------------------------------------------
    void SendString( Connection<Telnet>& p_conn, std::string p_string );

    // ------------------------------------------------------------------------
    //  Constructs the telnet policy.
    // ------------------------------------------------------------------------
    inline Telnet()
    {
        m_buffersize = 0;
    }

    inline int Buffered()   { return m_buffersize; }

protected:

    // This is the buffer that will contain all the processed telnet data
    char m_buffer[BUFFERSIZE];
    int m_buffersize;
};


}   // end namespace SocketLib

#endif
