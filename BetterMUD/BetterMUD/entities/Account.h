// MUD Programming
// Ron Penton
// (C)2003
// Account.h - This file contains the account entity type
// 
// 


#ifndef BETTERMUDACCOUNT_H
#define BETTERMUDACCOUNT_H

#include <string>
#include "BasicLib/BasicLib.h"
#include "Entity.h"
#include "Attributes.h"

namespace BetterMUD
{

// ----------------------------------------------------------------------------
//  This is the Account class, which describes a single user account,
//  and all characters owned by it.
// ----------------------------------------------------------------------------
class Account : 
    public Entity,
    public HasCharacters
{
public:
    Account()
    : m_password( "UNDEFINED" ),
      m_logintime( 0 ),
      m_accesslevel( Peon ),
      m_allowedcharacters( 2 ),
      m_banned( false ) {}

    
    void Load( std::istream& p_stream );
    void Save( std::ostream& p_stream );

    // Accessors
    std::string Password()                          { return m_password; }
    BasicLib::sint64 LoginTime()                    { return m_logintime; }
    accesslevel AccessLevel()                       { return m_accesslevel; }
    bool Banned()                                   { return m_banned; }
    int AllowedCharacters()                         { return m_allowedcharacters; }

    // Modifiers
    void SetPass( const std::string& p_pass )       { m_password = p_pass; }
    void SetLoginTime( BasicLib::sint64 p_time )    { m_logintime = p_time; }
    void SetAccessLevel( accesslevel p_level )      { m_accesslevel = p_level; }
    void SetBanned( bool p_banned )                 { m_banned = p_banned; }
    void SetAllowedCharacters( int p_num )          { m_allowedcharacters = p_num; }

protected:
    std::string m_password;                 // users password
    BasicLib::sint64 m_logintime;           // time of first login
    accesslevel m_accesslevel;              // access level of player
    int m_allowedcharacters;                // number of characters player is allowed
    bool m_banned;                          // is user banned?

};  // end class Account

}   // end namespace BetterMUD


#endif
