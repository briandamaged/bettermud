// MUD Programming
// Ron Penton
// (C)2003
// PythonLogic.cpp - This file contains a python logic module
// 
// 


#include "PythonLogic.h"
#include "PythonScript.h"
namespace BetterMUD
{


void PythonLogic::Init( entityid p_id )
{
    m_instance->Call( "Init", EntityToPy( p_id ) );
}

// get the state of the script, meaning varies depending on application
int PythonLogic::Attribute( const std::string& p_attr )
{ 
    return LongFromPy( m_instance->Call( "Attribute", StringToPy( p_attr ) ) );
}

// perform an action. return value varies depending on application
int PythonLogic::DoAction( const Action& p_action ) 
{ 
    return LongFromPy( 
        m_instance->Call( 
            "Execute",
            StringToPy( p_action.actiontype ),
            EntityToPy( p_action.data1 ),
            EntityToPy( p_action.data2 ),
            EntityToPy( p_action.data3 ),
            EntityToPy( p_action.data4 ),
            StringToPy( p_action.stringdata ) ) );
}


}   // end namespace BetterMUD

