// MUD Programming
// Ron Penton
// (C)2003
// PythonCommand.h - This file contains interface for python command objects
// 
// 


#ifndef BETTERMUDPYTHONCOMMAND_H
#define BETTERMUDPYTHONCOMMAND_H

#include <string>
#include "PythonScript.h"
#include "../Command.h"
#include "../../Game.h"

namespace BetterMUD
{


// -----------------------------------------------------------------------
//  Tells a user to quit.
// -----------------------------------------------------------------------
class PythonCommand : public Command
{
public:
    PythonCommand( 
        entityid p_character,                       // the character
        PythonInstance* p_classinstance )           // the script
        : m_script( p_classinstance ) 
    {
        m_script->Call( "Init", EntityToPy(p_character) );
    }

    ~PythonCommand()
    {
        if( m_script )
            delete m_script;
    }

    void Execute( const std::string& p_parameters ) { m_script->Call( "Execute", StringToPy(p_parameters) ); }
    std::string Name()                              { return StringFromPy( m_script->Call( "Name" ) ); }
    std::string Usage()                             { return StringFromPy( m_script->Call( "Usage" ) ); }
    std::string Description()                       { return StringFromPy( m_script->Call( "Description" ) ); }
    void Load( std::istream& p_stream )             { m_script->Load( p_stream ); }
    void Save( std::ostream& p_stream )             { m_script->Save( p_stream ); }


protected:
    PythonInstance* m_script;

};  // end class CommandQuit




}   // end namespace BetterMUD


#endif
