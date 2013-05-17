// MUD Programming
// Ron Penton
// (C)2003
// CharacterAccessor.cpp - This file contains the character accessor class
// 
// 


#include "Accessors.h"
#include "../databases/CharacterDatabase.h"

namespace BetterMUD
{


ENTITYTEMPLATEIMPLEMENTATIONS( charactertemplate, m_character, CharacterDB );
HASDATABANKIMPLEMENTATIONS( charactertemplate, m_character );


ENTITYIMPLEMENTATIONS( character, m_character, CharacterDB );
HASROOMIMPLEMENTATIONS( character, m_character );
HASREGIONIMPLEMENTATIONS( character, m_character );
HASTEMPLATEIDIMPLEMENTATIONS( character, m_character );
HASITEMSIMPLEMENTATIONS( character, m_character );
HASLOGICIMPLEMENTATIONS( character, m_character );
HASDATABANKIMPLEMENTATIONS( character, m_character );
HASCOMMANDSIMPLEMENTAIONS( character, m_character );


bool character::Quiet()                 { return m_character->Quiet(); }               
bool character::IsPlayer()              { return m_character->IsPlayer(); }
bool character::Verbose()               { return m_character->Verbose(); }
entityid character::GetAccount()        { return m_character->GetAccount(); }
void character::SetQuiet( bool p_quiet )                { m_character->SetQuiet( p_quiet ); }
void character::SetAccount( entityid p_account )        { m_character->SetAccount( p_account ); }
bool character::IsLoggedIn()            { return m_character->IsLoggedIn(); }
void character::SetLoggedIn( bool p_loggedin ) { m_character->SetLoggedIn( p_loggedin ); }
std::string character::LastCommand()    { return m_character->LastCommand(); }

}   // end namespace BetterMUD
