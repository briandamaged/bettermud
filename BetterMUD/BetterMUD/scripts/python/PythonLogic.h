// MUD Programming
// Ron Penton
// (C)2003
// PythonLogic.h - This file contains a python logic module
// 
// 


#ifndef BETTERMUDPYTHONLOGIC_H
#define BETTERMUDPYTHONLOGIC_H

#include "../Logic.h"
#include "PythonScript.h"

namespace BetterMUD
{


class PythonLogic : public Logic
{
public:
    PythonLogic( PythonInstance* p_inst )
        : m_instance( p_inst ) {}

    ~PythonLogic()
    {
        delete m_instance;
    }

    std::string Name()
    {
        return m_instance->Name();
    }


    void Init( entityid p_id );

    // get the state of the script, meaning varies depending on application
    int Attribute( const std::string& p_attr );

    // perform an action. return value varies depending on application
    int DoAction( const Action& p_action );

protected:
    PythonInstance* m_instance;

};  // end class Logic

}   // end namespace BetterMUD


#endif
