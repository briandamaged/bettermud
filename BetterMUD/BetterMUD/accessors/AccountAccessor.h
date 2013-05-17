// MUD Programming
// Ron Penton
// (C)2003
// AccountAccessor.h - This file contains the account accessor class
// 
// 


#ifndef BETTERMUDACCOUNTACCESSOR_H
#define BETTERMUDACCOUNTACCESSOR_H

#include "../entities/Entity.h"
#include "AccessorMacros.h"

namespace BetterMUD
{

// forward declaration
class Account;

// Accessor
class account
{
public:
    ENTITYHEADERS( account );
    HASCHARACTERSHEADERS;

    // Accessors
    std::string Password();
    BasicLib::sint64 LoginTime();
    int AccessLevel();
    bool Banned();
    int AllowedCharacters();

    // Modifiers
    void SetPass( const std::string& p_pass );
    void SetLoginTime( BasicLib::sint64 p_time );
    void SetAccessLevel( int p_level );
    void SetBanned( bool p_banned );
    void SetAllowedCharacters( int p_num );

protected:
    Account* m_account;

};

}   // end namespace BetterMUD


#endif
