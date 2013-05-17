// MUD Programming
// Ron Penton
// (C)2003
// Command.h - This file contains the standard Command interface.
//             commands are objects given to players, and then executed
//             in the game when their names match
// 
// 


#ifndef BETTERMUDCOMMAND_H
#define BETTERMUDCOMMAND_H

#include "Script.h"

namespace BetterMUD
{


// -----------------------------------------------------------------------
//  The Command class, which belongs to a character and executes given
//  commands.
// -----------------------------------------------------------------------
class Command : public Script
{
public:

    virtual void Execute( const std::string& p_parameters ) = 0;
    virtual std::string Usage() = 0;
    virtual std::string Description() = 0;
};  // end class Command

}   // end namespace BetterMUD


#endif
