// MUD Programming
// Ron Penton
// (C)2003
// Action.h - This file contains the Action type for BetterMUD.
// 
// 


#ifndef BETTERMUDACTION_H
#define BETTERMUDACTION_H

#include <string>
#include "Entity.h"


namespace BetterMUD
{

enum ENTITYTYPE
{
    CHARACTER,
    ITEM,
    ROOM,
    PORTAL,
    REGION
};


struct Action
{
    std::string actiontype;
    entityid data1;
    entityid data2;
    entityid data3;
    entityid data4;
    std::string stringdata;

    Action() {};

    Action( 
        const std::string& p_action, 
        entityid p_data1 = 0,
        entityid p_data2 = 0,
        entityid p_data3 = 0, 
        entityid p_data4 = 0,
        const std::string& p_data = "" )
    :   actiontype( p_action ),
        data1( p_data1 ),
        data2( p_data2 ),
        data3( p_data3 ),
        data4( p_data4 ),
        stringdata( p_data ) {}
};



struct TimedAction
{
    BasicLib::sint64 executiontime;
    Action actionevent;
    bool valid;

    TimedAction() :
        valid( true ){};

    TimedAction( BasicLib::sint64 time, const Action& act )
    : executiontime( time ),
      actionevent( act ) {}
    
    TimedAction( 
        BasicLib::sint64 time,
        const std::string& p_action, 
        entityid p_data1 = 0,
        entityid p_data2 = 0,
        entityid p_data3 = 0, 
        entityid p_data4 = 0,
        const std::string& p_data = "" ) :   
    executiontime( time ),
    actionevent( p_action, p_data1, p_data2, p_data3, p_data4, p_data ),
    valid( true ) {}

    void Hook();
    void Unhook();
    void Save( std::ofstream& p_stream );
    void Load( std::ifstream& p_stream );
};

class TimedActionComp : public std::binary_function<TimedAction*, TimedAction*, bool>
{
public:
    bool operator()( const first_argument_type& left, 
                   const second_argument_type& right )
    {
        return left->executiontime > right->executiontime;
    }
};






}   // end namespace BetterMUD


#endif
