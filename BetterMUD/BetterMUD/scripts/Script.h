// MUD Programming
// Ron Penton
// (C)2003
// Script.h - This file contains the interfaces for bettermud scripts
// 
// 


#ifndef BETTERMUDSCRIPT_H
#define BETTERMUDSCRIPT_H

#include <string>
#include <iostream>

namespace BetterMUD
{
   

enum SCRIPTRELOADMODE
{
    LEAVEEXISTING,
    RELOADFUNCTIONS
};

// -----------------------------------------------------------------------
//  This is the basic script class, which allows loading and saving to
//  streams, and generic message passing
// -----------------------------------------------------------------------
class Script
{
public:

    virtual void Load( std::istream& p_stream ) 
    {
        // default to empty data loading, by chewing up the [DATA] and
        // [/DATA] tags.
        std::string temp;
        p_stream >> temp >> temp;
    };

    virtual void Save( std::ostream& p_stream ) 
    {
        // default to empty data saving
        p_stream << "[DATA]\n[/DATA]\n";
    };

    virtual std::string Name() = 0;
    virtual ~Script() {};
};  // end class Script

    
}   // end namespace BetterMUD


#endif
