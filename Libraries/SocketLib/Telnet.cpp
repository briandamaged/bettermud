// MUD Programming
// Ron Penton
// (C)2003
// Telnet.cpp - This is the header for the telnet policy class; it receives raw 
//              data from a connection and strips out or takes care of any 
//              command codes.


#include "Telnet.h"

namespace SocketLib
{

using std::string;

// ------------------------------------------------------------------------
//  Translates raw byte data into telnet data, and may send it out to
//  the connection's current protocol handler
// ------------------------------------------------------------------------
void Telnet::Translate( Connection<Telnet>& p_conn, char* p_buffer, int p_size )
{
    for( int i = 0; i < p_size; i++ )
    {

        // if the character is a letter and the buffer isn't full,
        // add it to the buffer
        char c = p_buffer[i];
        if( c >= 32 && c != 127 && m_buffersize < BUFFERSIZE )
        {
            m_buffer[m_buffersize] = c;
            m_buffersize++;
        }

        // else check if it's a backspace
        else if( c == 8 && m_buffersize > 0 )
        {
            // erase the last character
            m_buffersize--;
        }

        // else check if it is a newline, meaning the line is complete
        else if( c == '\n' || c == '\r' )
        {
            // if the buffer size is more than 0, turn the buffer into
            // a string and send it off to the current handler of the 
            // connection. Then reset the size of the buffer.
            if( m_buffersize > 0 && p_conn.Handler() != 0 )
            {
                p_conn.Handler()->Handle( string( m_buffer, m_buffersize ) );
            }
            m_buffersize = 0;
        }
    }
}


// ------------------------------------------------------------------------
//  This sends a plain text string to the connection, doing any translations
//  if neccessary.
// ------------------------------------------------------------------------
void Telnet::SendString( Connection<Telnet>& p_conn, string p_string )
{
    // just buffer the data on the connection
    p_conn.BufferData( p_string.data(), (int)p_string.size() );
}


}   // end namespace SocketLib
