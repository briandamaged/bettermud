// MUD Programming
// Ron Penton
// (C)2003
// CPPCommand.h - This file contains the standard C++-implemented game command
//                base class
// 
// 


#ifndef BETTERMUDCPPCOMMAND_H
#define BETTERMUDCPPCOMMAND_H

#include "Command.h"
#include "../accessors/Accessors.h"

namespace BetterMUD
{


// -----------------------------------------------------------------------
//  The Base C++ Command Class
// -----------------------------------------------------------------------
class CPPCommand : public Command
{
public:
    CPPCommand( 
        entityid p_character,
        std::string p_name,
        const char* p_usage,
        const char* p_description )
    : m_character( p_character ),
      m_name( p_name ),
      m_usage( p_usage ), 
      m_description( p_description ) {};

    std::string Name()          { return m_name; }
    std::string Usage()         { return m_usage; }
    std::string Description()   { return m_description; }

protected:
    std::string m_name;
    const char* m_usage;
    const char* m_description;
    character m_character;

};  // end class CPPCommand


}   // end namespace BetterMUD


#endif
