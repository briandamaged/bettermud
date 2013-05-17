// MUD Programming
// Ron Penton
// (C)2003
// BetterTelnet.cpp - This is the header for the BETTER telnet policy class; it 
//                    is similar to the old telnet policy, but it does automatic
//                    BetterMUD color conversions.
//
//

#include "BetterTelnet.h"

namespace BetterMUD
{

using std::string;

// ------------------------------------------------------------------------
//  Translates raw byte data into telnet data, and may send it out to
//  the connection's current protocol handler
// ------------------------------------------------------------------------
void BetterTelnet::Translate( connection& p_conn, char* p_buffer, int p_size )
{
    for( int i = 0; i < p_size; i++ )
    {
        // if the character is a letter and the buffer isn't full,
        // add it to the buffer
        char c = p_buffer[i];
        if( c >= 32 && c != 127 && m_buffersize < SocketLib::BUFFERSIZE )
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
void BetterTelnet::SendString( connection& p_conn, const string& p_string )
{
    // just buffer the data on the connection
    string str = TranslateColors( p_string );
    p_conn.BufferData( str.data(), (int)str.size() );
}




// ------------------------------------------------------------------------
//  Translate BetterMUD color codes into telnet codes
// ------------------------------------------------------------------------
std::string BetterTelnet::TranslateColors(      // this translates BetterMUD
    const std::string& p_str )                  // color strings into telnet colors.
{
    std::string str( p_str );
    std::string::size_type i = str.find( "<" );
    

    while( i != std::string::npos )
    {
        if( str[i + 1] == '$' )
        {
            std::string::size_type j = str.find( ">", i );
            if( j != std::string::npos )
            {
                TranslateStringColor( i, j, str );
            }
        }
        else if( str[i + 1] == '#' )
        {
            std::string::size_type j = str.find( ">", i );
            if( j != std::string::npos )
            {
                TranslateNumberColor( i, j, str );
            }
        }
        i = str.find( "<", i + 1 );
    }

    return str;
}

// ------------------------------------------------------------------------
//  Translate string-based color codes into telnet codes
// ------------------------------------------------------------------------
void BetterTelnet::TranslateStringColor(
    std::string::size_type i,                   // start of color
    std::string::size_type j,                   // end of color
    std::string& p_str )                        // string
{
    using namespace SocketLib;
    std::string col = p_str.substr( i, j - i + 1 );

    if( col == "<$black>" )
        p_str.replace( i, j - i + 1, black );
    else if( col == "<$red>" )
        p_str.replace( i, j - i + 1, red );
    else if( col == "<$green>" )
        p_str.replace( i, j - i + 1, green );
    else if( col == "<$yellow>" )
        p_str.replace( i, j - i + 1, yellow );
    else if( col == "<$blue>" )
        p_str.replace( i, j - i + 1, blue );
    else if( col == "<$magenta>" )
        p_str.replace( i, j - i + 1, magenta );
    else if( col == "<$cyan>" )
        p_str.replace( i, j - i + 1, cyan );
    else if( col == "<$white>" )
        p_str.replace( i, j - i + 1, white );
    else if( col == "<$bold>" )
        p_str.replace( i, j - i + 1, bold );
    else if( col == "<$dim>" )
        p_str.replace( i, j - i + 1, dim );
    else if( col == "<$reset>" )
        p_str.replace( i, j - i + 1, reset );
}


// ------------------------------------------------------------------------
//  The following section of code defines an array of strings used to convert
//  24-bit colors into the 15 different telnet colors. An anonymous class
//  is defined here to auto construct them. I prefer this method over explicit
//  initialization, due to the ugly syntax. This method is "cleaner", because
//  you can see the indexes of the colors as they are initialized.
// ------------------------------------------------------------------------
std::string g_telnetcolors[3][3][3];
class INITTELNETCOLORS
{
public:
    // Initialize the colors.
    INITTELNETCOLORS()
    {
        using namespace SocketLib;

        // Due to the lack of depth of telnet colors (only 15), not all colors
        // can be represented. Colors that are not exact have a * after them,
        // and colors that are very different have ** after them.
        // For example, [2][1][0] is really supposed to be orange, but there is
        // no way to represent orange in telnet, so I used what I thought to be
        // the closest equivalent, dim yellow. Another example is [0][1][2],
        // which is a really cool seagreen-blue color, but the closest there is
        // in telnet would be bright blue.
        g_telnetcolors[0][0][0] = black + dim;
        g_telnetcolors[0][0][1] = blue + dim;
        g_telnetcolors[0][0][2] = blue + bold;
        g_telnetcolors[0][1][0] = green + dim;
        g_telnetcolors[0][1][1] = cyan + dim;
        g_telnetcolors[0][1][2] = blue + bold;              // *
        g_telnetcolors[0][2][0] = green + bold;
        g_telnetcolors[0][2][1] = green + bold;             // *
        g_telnetcolors[0][2][2] = cyan + bold;

        g_telnetcolors[1][0][0] = red + dim;
        g_telnetcolors[1][0][1] = magenta + dim;
        g_telnetcolors[1][0][2] = magenta + bold;           // *
        g_telnetcolors[1][1][0] = yellow + dim;
        g_telnetcolors[1][1][1] = white + dim;
        g_telnetcolors[1][1][2] = blue + bold;              // *
        g_telnetcolors[1][2][0] = green + bold;             // *
        g_telnetcolors[1][2][1] = green + bold;             // *
        g_telnetcolors[1][2][2] = cyan + bold;              // *

        g_telnetcolors[2][0][0] = red + bold;
        g_telnetcolors[2][0][1] = red + bold;               // *
        g_telnetcolors[2][0][2] = magenta + bold;
        g_telnetcolors[2][1][0] = yellow + dim;             // **
        g_telnetcolors[2][1][1] = red + bold;               // **
        g_telnetcolors[2][1][2] = magenta + bold;           // *
        g_telnetcolors[2][2][0] = yellow + bold;
        g_telnetcolors[2][2][1] = yellow + bold;            // *
        g_telnetcolors[2][2][2] = white + bold;
    }
};  // end class INITTELNETCOLORS

// declare instance of class, to init colors.
INITTELNETCOLORS g_initetelnetcolors;



// ------------------------------------------------------------------------
//  The following section of code defines the functions that translate 
//  bettermud truecolor strings into telnet color
// ------------------------------------------------------------------------
void BetterTelnet::TranslateNumberColor(
    std::string::size_type i,                   // start of color
    std::string::size_type j,                   // end of color
    std::string& p_str )                        // string
{
    // just return if the string is invalid
    if( (j - i) != 8 )
        return;

    // chop off the six digits, ie the "XXXXXX" inside "<#XXXXXX>"
    std::string col = p_str.substr( i + 2, j - i );
    
    using BasicLib::ASCIIToHex;
    int r = ASCIIToHex( col[0] ) * 16 + ASCIIToHex( col[1] );
    int g = ASCIIToHex( col[2] ) * 16 + ASCIIToHex( col[3] );
    int b = ASCIIToHex( col[4] ) * 16 + ASCIIToHex( col[5] );

    // convert the numbers to the 0-2 range
    // ie:  0 -  85 = 0
    //     86 - 171 = 1
    //    172 - 255 = 2
    // This gives a good approximation of the true color by assigning equal
    // ranges to each value.
    r = r / 86;
    g = g / 86;
    b = b / 86;

    p_str.replace( i, j - i + 1, g_telnetcolors[r][g][b] );
}


}   // end namespace SocketLib
