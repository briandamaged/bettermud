// MUD Programming
// Ron Penton
// (C)2003
// CharacterAccessor.h - This file contains the character accessor class
// 
// 


#ifndef BETTERMUDCHARACTERACCESSOR_H
#define BETTERMUDCHARACTERACCESSOR_H

#include "../entities/Entity.h"
#include "../entities/Action.h"
#include "../scripts/Logic.h"
#include <list>
#include "AccessorMacros.h"

namespace BetterMUD
{

// forward declaration
class Character;
class CharacterTemplate;
class Reporter;
class Command;



class charactertemplate
{
public:
    ENTITYTEMPLATEHEADERS( charactertemplate );
    HASDATABANKHEADERS;

protected:
    CharacterTemplate* m_character;

};


// Accessor
class character
{
public:
    ENTITYHEADERS( character );
    HASROOMHEADERS;
    HASREGIONHEADERS;
    HASTEMPLATEIDHEADERS;
    HASITEMSHEADERS;
    HASDATABANKHEADERS;
    HASLOGICHEADERS;
    HASCOMMANDSHEADERS;


    // accessors:
    bool Quiet();
    bool IsPlayer();
    bool Verbose();
    entityid GetAccount();

    // modifiers
    void SetQuiet( bool p_quiet );
    void SetAccount( entityid p_account );
    bool IsLoggedIn();
    void SetLoggedIn( bool p_loggedin );
    std::string LastCommand();

protected:
    Character* m_character;

};

}   // end namespace BetterMUD


#endif
