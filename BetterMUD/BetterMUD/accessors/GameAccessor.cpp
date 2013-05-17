// MUD Programming
// Ron Penton
// (C)2003
// GameAccessor.cpp - This file contains the game accessor class
// 
// 


#include "GameAccessor.h"
#include "../databases/AllDatabases.h"

namespace BetterMUD
{

entityid GameWrap::FindPlayerOnlinePart( const std::string& p_name )  
{ 
    return g_game.FindPlayerOnlinePart( p_name ); 
}

entityid GameWrap::FindPlayerOnlineFull( const std::string& p_name )  
{ 
    return g_game.FindPlayerOnlineFull( p_name ); 
}

entityid GameWrap::FindPlayerPart( const std::string& p_name )    
{ 
    return g_game.FindPlayerPart( p_name ); 
}

entityid GameWrap::FindPlayerFull( const std::string& p_name )    
{ 
    return g_game.FindPlayerFull( p_name ); 
}

bool GameWrap::HasPlayer( entityid p_id )                         
{ 
    return g_game.HasPlayer( p_id ); 
}

bool GameWrap::Running()                                          
{ 
    return g_game.Running(); 
}

void GameWrap::ShutDown()                                         
{ 
    g_game.ShutDown(); 
}

BasicLib::sint64 GameWrap::GetTime()
{ 
    return g_game.GetTime(); 
}

void GameWrap::ResetTime()
{ 
    g_game.ResetTime(); 
}

void GameWrap::DoAction( 
    const std::string& p_act, 
    entityid p_data1, 
    entityid p_data2, 
    entityid p_data3, 
    entityid p_data4, 
    const std::string& p_data )
{
    g_game.DoAction( p_act, p_data1, p_data2, p_data3, p_data4, p_data );
}


void GameWrap::AddActionRelative( 
    BasicLib::sint64 p_time,
    const std::string& p_act, 
    entityid p_data1, 
    entityid p_data2, 
    entityid p_data3, 
    entityid p_data4, 
    const std::string& p_data )
{
    g_game.AddActionRelative( p_time, p_act, p_data1, p_data2, p_data3, p_data4, p_data );
}

void GameWrap::AddActionAbsolute( 
    BasicLib::sint64 p_time,
    const std::string& p_act, 
    entityid p_data1, 
    entityid p_data2, 
    entityid p_data3, 
    entityid p_data4, 
    const std::string& p_data )
{
    g_game.AddActionAbsolute( p_time, p_act, p_data1, p_data2, p_data3, p_data4, p_data );
}



size_t GameWrap::Characters()                      { return CharacterDB.size(); }
void GameWrap::BeginCharacter()                    { m_charitr = CharacterDB.begin(); }
entityid GameWrap::CurrentCharacter()              { return m_charitr->first; }
void GameWrap::NextCharacter()                     { ++m_charitr; }
bool GameWrap::IsValidCharacter()                  { return m_charitr != CharacterDB.end(); }

size_t GameWrap::CharacterTemplates()                      { return CharacterDB.sizetemplates(); }
void GameWrap::BeginCharacterTemplate()                    { m_chartemitr = CharacterDB.begintemplates(); }
entityid GameWrap::CurrentCharacterTemplate()              { return m_chartemitr->ID(); }
void GameWrap::NextCharacterTemplate()                     { ++m_chartemitr; }
bool GameWrap::IsValidCharacterTemplate()                  { return m_chartemitr != CharacterDB.endtemplates(); }

size_t GameWrap::Items()                      { return ItemDB.size(); }
void GameWrap::BeginItem()                    { m_itemitr = ItemDB.begin(); }
entityid GameWrap::CurrentItem()              { return m_itemitr->first; }
void GameWrap::NextItem()                     { ++m_itemitr; }
bool GameWrap::IsValidItem()                  { return m_itemitr != ItemDB.end(); }

size_t GameWrap::ItemTemplates()                      { return ItemDB.sizetemplates(); }
void GameWrap::BeginItemTemplate()                    { m_itemtemitr = ItemDB.begintemplates(); }
entityid GameWrap::CurrentItemTemplate()              { return m_itemtemitr->ID(); }
void GameWrap::NextItemTemplate()                     { ++m_itemtemitr; }
bool GameWrap::IsValidItemTemplate()                  { return m_itemtemitr != ItemDB.endtemplates(); }


size_t GameWrap::Rooms()                      { return RoomDB.size(); }
void GameWrap::BeginRoom()                    { m_roomitr = RoomDB.begin(); }
entityid GameWrap::CurrentRoom()              { return m_roomitr->ID(); }
void GameWrap::NextRoom()                     { ++m_roomitr; }
bool GameWrap::IsValidRoom()                  { return m_roomitr != RoomDB.end(); }

size_t GameWrap::Regions()                      { return RegionDB.size(); }
void GameWrap::BeginRegion()                    { m_regitr = RegionDB.begin(); }
entityid GameWrap::CurrentRegion()              { return m_regitr->ID(); }
void GameWrap::NextRegion()                     { ++m_regitr; }
bool GameWrap::IsValidRegion()                  { return m_regitr != RegionDB.end(); }

size_t GameWrap::Portals()                      { return PortalDB.size(); }
void GameWrap::BeginPortal()                    { m_portalitr = PortalDB.begin(); }
entityid GameWrap::CurrentPortal()              { return m_portalitr->ID(); }
void GameWrap::NextPortal()                     { ++m_portalitr; }
bool GameWrap::IsValidPortal()                  { return m_portalitr != PortalDB.end(); }

size_t GameWrap::Accounts()                      { return AccountDB.size(); }
void GameWrap::BeginAccount()                    { m_accountitr = AccountDB.begin(); }
entityid GameWrap::CurrentAccount()              { return m_accountitr->first; }
void GameWrap::NextAccount()                     { ++m_accountitr; }
bool GameWrap::IsValidAccount()                  { return m_accountitr != AccountDB.end(); }


}   // end namespace BetterMUD
