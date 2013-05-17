// MUD Programming
// Ron Penton
// (C)2003
// Character.h - This file contains the character entity type
// 
// 


#ifndef BETTERMUDCHARACTER_H
#define BETTERMUDCHARACTER_H

#include <string>
#include <list>
#include <iostream>
#include "BasicLib/BasicLib.h"
#include "../scripts/Command.h"
#include "../scripts/LogicCollection.h"
#include "Entity.h"
#include "LogicEntity.h"
#include "DataEntity.h"
#include "Attributes.h"

namespace BetterMUD
{



// ============================================================================
//  Character Template Class
// ============================================================================
class CharacterTemplate : 
    public Entity,
    public DataEntity
{
    friend class Character;
public:
    typedef std::list< std::string > names;
    void Load( std::istream& p_stream );

protected:

    names m_commands;
    names m_logics;

};

    


// ============================================================================
//  Character Instance Class
// ============================================================================
class Character : 
    public LogicEntity,
    public DataEntity,
    public HasRoom,
    public HasRegion,
    public HasTemplateID,
    public HasItems
{
public:
    typedef std::list<Command*> commands;

    Character();
    ~Character();

    void LoadTemplate( const CharacterTemplate& p_template );

    void Load( std::istream& p_stream );
    void Save( std::ostream& p_stream );
    commands::iterator CommandsBegin()  { return m_commands.begin(); }
    commands::iterator CommandsEnd()    { return m_commands.end(); }
    commands::iterator FindCommand( const std::string& p_name );

    // accessors:
    entityid GetAccount()               { return m_account; }
    bool Quiet()                        { return m_quiet; }
    bool IsPlayer()                     { return m_account != 0; }
    bool Verbose()                      { return m_verbose; }
    std::string LastCommand()           { return m_lastcommand; }
    bool IsLoggedIn()                   { return m_loggedin; }

    // modifiers:
    void SetAccount( entityid p_account )       { m_account = p_account; }
    void SetQuiet( bool p_quiet )               { m_quiet = p_quiet; }
    void SetVerbose( bool p_verbose )           { m_verbose = p_verbose; }
    void SetLastCommand( const std::string& p_command ) { m_lastcommand = p_command; }
    void SetLoggedIn( bool p_loggedin )         { m_loggedin = p_loggedin; }

    // script-related functions
    bool AddCommand( const std::string& p_command );
    bool DelCommand( const std::string& p_command );
    bool HasCommand( const std::string& p_command );


    // functions to add and remove a character "from the game"
    void Add();
    void Remove();


protected:
    // savable data
    entityid m_account;             // account number
    bool m_quiet;                   // if quiet, then report errors on unknown commands
    bool m_verbose;                 // verbose mode; are room descriptions printed?

    // temporary data
    bool m_loggedin;                // are you logged in?
    std::string m_lastcommand;      // the last command the character entered
    commands m_commands;            // which commands the character has

};  // end class Character




}   // end namespace BetterMUD


#endif
