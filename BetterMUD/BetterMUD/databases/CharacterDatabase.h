// MUD Programming
// Ron Penton
// (C)2003
// CharacterDatabase.h - This file contains the character entity database
// 
// 


#ifndef BETTERMUDCHARACTERDATABASE_H
#define BETTERMUDCHARACTERDATABASE_H

#include "Databases.h"
#include "../entities/Character.h"


namespace BetterMUD
{

class CharacterDatabase : 
    public TemplateInstanceDatabase<Character, CharacterTemplate>
{
public:
    bool HasName();
    entityid FindPlayerFull( const std::string& p_name );
    entityid FindPlayerPart( const std::string& p_name );
    void SavePlayers();
    void LoadPlayers();
    void LoadTemplates();
    void LoadTemplates( const std::string& p_file );
    void LoadPlayer( const std::string& p_name );
};

extern CharacterDatabase CharacterDB;

}   // end namespace BetterMUD


#endif
