// MUD Programming
// Ron Penton
// (C)2003
// SocketLibSystem.h - This header contains all of the socket functions
// that aren't related to any classes.



#ifndef SOCKETLIBSYSTEM_H
#define SOCKETLIBSYSTEM_H


// ========================================================================
//  Include Files
// ========================================================================
#include <string>
#include "SocketLibTypes.h"


namespace SocketLib
{

    // ========================================================================
    // Function:    GetIPAddress
    // Purpose:     To get the IP address of the string as an ipaddress
    //              structure. Throws an exception if the address cannot be
    //              converted.
    // ========================================================================
        ipaddress GetIPAddress( const std::string p_address );


    // ========================================================================
    // Function:    GetIPString
    // Purpose:     Converts an ipaddress structure to a string in numerical
    //              format.
    // ========================================================================
    std::string GetIPString( ipaddress p_address );


    // ========================================================================
    // Function:    GetHostNameString
    // Purpose:     Converts an ipaddress structure to a string using
    //              reverse-DNS lookup. This may block.
    // ========================================================================
    std::string GetHostNameString( ipaddress p_address );


    // ========================================================================
    // Function:    IsIPAddress
    // Purpose:     determines if a string contains a pure numerical IP address
    //              (returns true) or a DNS'able address (returns false)
    // ========================================================================
    bool IsIPAddress( const std::string p_address );



}


#endif

