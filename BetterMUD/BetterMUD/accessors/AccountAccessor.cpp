// MUD Programming
// Ron Penton
// (C)2003
// AccountAccessor.h - This file contains the account accessor class
// 
// 


#include "Accessors.h"
#include "../databases/AccountDatabase.h"

namespace BetterMUD
{

ENTITYIMPLEMENTATIONS( account, m_account, AccountDB );
HASCHARACTERSIMPLEMENTATIONS( account, m_account );


    // Accessors
std::string account::Password()             { return m_account->Password(); }
BasicLib::sint64 account::LoginTime()       { return m_account->LoginTime(); }
int account::AccessLevel()                  { return m_account->AccessLevel(); }
bool account::Banned()                      { return m_account->Banned(); }
int account::AllowedCharacters()            { return m_account->AllowedCharacters(); }

// Modifiers
void account::SetPass( const std::string& p_pass )          { m_account->SetPass( p_pass ); }
void account::SetLoginTime( BasicLib::sint64 p_time )       { m_account->SetLoginTime( p_time ); }
void account::SetAccessLevel( int p_level )                 { m_account->SetAccessLevel( (accesslevel)p_level ); }
void account::SetBanned( bool p_banned )                    { m_account->SetBanned( p_banned ); }
void account::SetAllowedCharacters( int p_num )             { m_account->SetAllowedCharacters( p_num ); }

}   // end namespace BetterMUD
