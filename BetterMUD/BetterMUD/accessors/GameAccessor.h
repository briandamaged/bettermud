// MUD Programming
// Ron Penton
// (C)2003
// GameAccessor.h - This file contains the game accessor class
// 
// 


#ifndef BETTERMUDGAMEACCESSOR_H
#define BETTERMUDGAMEACCESSOR_H

#include "../databases/AllDatabases.h"

namespace BetterMUD
{

class GameWrap
{
public:
    entityid FindPlayerOnlinePart( const std::string& p_name );
    entityid FindPlayerOnlineFull( const std::string& p_name );
    entityid FindPlayerPart( const std::string& p_name );
    entityid FindPlayerFull( const std::string& p_name );
    bool HasPlayer( entityid p_id );
   
    bool Running();
    void ShutDown();

    BasicLib::sint64 GetTime();
    void ResetTime();


    void DoAction( 
        const std::string& p_act, 
        entityid p_data1, 
        entityid p_data2, 
        entityid p_data3, 
        entityid p_data4, 
        const std::string& p_data );


    void AddActionRelative( 
        BasicLib::sint64 p_time,
        const std::string& p_act, 
        entityid p_data1, 
        entityid p_data2, 
        entityid p_data3, 
        entityid p_data4, 
        const std::string& p_data );

    void AddActionAbsolute( 
        BasicLib::sint64 p_time,
        const std::string& p_act, 
        entityid p_data1, 
        entityid p_data2, 
        entityid p_data3, 
        entityid p_data4, 
        const std::string& p_data );
    

    size_t Characters();
    void BeginCharacter();
    entityid CurrentCharacter();
    void NextCharacter();
    bool IsValidCharacter();

    size_t CharacterTemplates();
    void BeginCharacterTemplate();
    entityid CurrentCharacterTemplate();
    void NextCharacterTemplate();
    bool IsValidCharacterTemplate();

    size_t Items();
    void BeginItem();
    entityid CurrentItem();
    void NextItem();
    bool IsValidItem();

    size_t ItemTemplates();
    void BeginItemTemplate();
    entityid CurrentItemTemplate();
    void NextItemTemplate();
    bool IsValidItemTemplate();

    size_t Rooms();
    void BeginRoom();
    entityid CurrentRoom();
    void NextRoom();
    bool IsValidRoom();

    size_t Regions();
    void BeginRegion();
    entityid CurrentRegion();
    void NextRegion();
    bool IsValidRegion();

    size_t Portals();
    void BeginPortal();
    entityid CurrentPortal();
    void NextPortal();
    bool IsValidPortal();

    size_t Accounts();
    void BeginAccount();
    entityid CurrentAccount();
    void NextAccount();
    bool IsValidAccount();

protected:
    CharacterDatabase::instances::iterator m_charitr;
    CharacterDatabase::templates::iterator m_chartemitr;
    ItemDatabase::instances::iterator m_itemitr;
    ItemDatabase::templates::iterator m_itemtemitr;

    RoomDatabase::container::iterator m_roomitr;
    RegionDatabase::container::iterator m_regitr;
    AccountDatabase::container::iterator m_accountitr;
    PortalDatabase::container::iterator m_portalitr;
};

}   // end namespace BetterMUD


#endif
