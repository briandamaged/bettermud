// MUD Programming
// Ron Penton
// (C)2003
// Logic.h - This file contains a logic module, which responds to actions
// 
// 


#ifndef BETTERMUDLOGIC_H
#define BETTERMUDLOGIC_H

#include "../entities/Entity.h"
#include "../entities/Action.h"
#include "Script.h"


namespace BetterMUD
{


// forward declare the TimerAction class:
class TimerAction;


class Logic : 
    public Script
{
public:

    virtual std::string Name() = 0;

    virtual bool CanSave() { return true; }

    // get an attribute from the script
    virtual int Attribute( const std::string& p_attr ) { return 0; }

    // perform an action. return value varies depending on application
    virtual int DoAction( const Action& p_action ) { return 0; }
 
};  // end class Logic

}   // end namespace BetterMUD


#endif
