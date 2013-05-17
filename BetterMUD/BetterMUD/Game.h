// MUD Programming
// Ron Penton
// (C)2003
// Game.h - The game logic of BetterMUD.
// 
// 


#ifndef BETTERMUDGAME_H
#define BETTERMUDGAME_H

#include <set>
#include <queue>
#include "entities/Entity.h"
#include "entities/Action.h"
#include "accessors/Accessors.h"
#include "scripts/Script.h"

namespace BetterMUD
{



class Game
{
public:
    Game();
    ~Game();
    typedef std::set<entityid> characters;
    typedef std::set<entityid> players;


    // ------------------------------------------------------------------------
    // Game Actions. 
    // ------------------------------------------------------------------------

    void DoAction( const Action& p_action );
    void DoAction( const std::string& p_act, entityid p_data1 = 0, entityid p_data2 = 0, entityid p_data3 = 0, entityid p_data4 = 0, const std::string& p_data = "" );


protected:
    // ------------------------------------------------------------------------
    // Action helpers
    // ------------------------------------------------------------------------

    // perform actions on specific groups of entities
    void ActionRealmPlayers( const Action& p_action );
    void ActionRealmCharacters( const Action& p_action );
    void ActionRoomCharacters( const Action& p_action, entityid p_room );
    void ActionRoomItems( const Action& p_action, entityid p_room );

    // route an action somewhere
    void RouteAction( const Action& p_action );

    // modify an attribute
    void ModifyAttribute( const Action& p_action );

    // perform a command
    void DoCommand( 
        entityid p_player,              // player doing command
        const std::string& p_command ); // command being executed

    void Say( 
        entityid p_player,              // character saying something
        const std::string& p_text );    // text being said

    void Login( 
        entityid p_id );                // the ID of the character

    void Logout( 
        entityid p_id );                // the ID of the character

    // tells a room that someone has tried to enter through a portal
    void EnterPortal( 
        entityid p_character,                   // character who entered
        entityid p_portal );                    // portal entered from

    // tells a room that someone has transported
    void Transport( 
        entityid p_character,                   // character who left
        entityid p_room );                      // room id
        
    void ForceTransport( 
        entityid p_character,                   // character who left
        entityid p_room );                      // room id

    void GetItem( 
        entityid p_character,                   // character who wants item
        entityid p_item,                        // item
        entityid p_quantity );                  // optional quantity

    void DropItem( 
        entityid p_character,                   // character who wants to drop item
        entityid p_item,                        // item
        entityid p_quantity );                  // optional quantity

    void GiveItem( 
        entityid p_giver,                       // character who is giving
        entityid p_receiver,                    // character who is getting
        entityid p_item,                        // item
        entityid p_quantity );                  // optional quantity



    template< typename entity >
    void DoJoinQuantities( entity& p_e, entityid p_id )
    {
        // the item that we're keeping:
        item keep( p_id );


        // go through the items, finding any to merge with "keep"
        typename entity::itemitr itr = p_e.ItemsBegin();
        while( itr != p_e.ItemsEnd() )
        {
            typename entity::itemitr current = itr++;
            if( *current != keep.ID() )     // only check other items
            {
                item check( *current );
                if( check.TemplateID() == keep.TemplateID() )
                {
                    // items match, so join them and delete current.
                    keep.SetQuantity( keep.GetQuantity() + check.GetQuantity() );
                    DeleteItem( check.ID() );
                }
            }
        }
    }

    void SpawnItem( 
        entityid p_itemtemplate,                // template of item
        entityid p_location,                    // location to put it
        entityid p_player,                      // player or room?
        entityid p_quantity );                  // optional quantity

    void DestroyItem( entityid p_item );        // item to destroy
    void DestroyCharacter( entityid p_item );   // character to destroy

    void SpawnCharacter( 
        entityid p_chartemplate,                // template of character
        entityid p_location );                  // location to put it


    void LogicAction( const Action& p_act );
    void AddLogic( const Action& p_act );
    void DelLogic( const Action& p_act );


    // physical modifiers
    void AddCharacter( entityid p_id )          { m_characters.insert( p_id ); }
    void AddPlayer( entityid p_id )             { m_players.insert( p_id ); }
    void RemoveCharacter( entityid p_id )       { m_characters.erase( p_id ); }
    void RemovePlayer( entityid p_id )          { m_players.erase( p_id ); }


    void DeleteItem( entityid p_item );

public:
    // ------------------------------------------------------------------------
    // Misc.
    // ------------------------------------------------------------------------
    bool Running()                              { return m_running; }
    void ShutDown()                             { m_running = false; }

    players::iterator PlayersBegin()            { return m_players.begin(); }
    players::iterator PlayersEnd()              { return m_players.end(); }


    // ------------------------------------------------------------------------
    // Database Stuff
    // ------------------------------------------------------------------------
    // clean up all entities that have been deleted
    void Cleanup();
    
    // save EVERYTHING out to disk
    void SaveAll();

    // Save all the players out to disk
    void SavePlayers();

    // save a particular region out to disk
    void SaveRegion( entityid p_region );

    // load all the databases
    void LoadAll();

    // Reload files and stuff
    void ReloadItemTemplates( const std::string& p_file );
    void ReloadCharacterTemplates( const std::string& p_file );
    void ReloadRegion( const std::string& p_name );
    void ReloadCommandScript( const std::string& p_name, SCRIPTRELOADMODE p_mode );
    void ReloadLogicScript( const std::string& p_name, SCRIPTRELOADMODE p_mode );

    void SaveTimers();
    void LoadTimers();

    // ------------------------------------------------------------------------
    // Logged-in-player accessors. 
    // ------------------------------------------------------------------------
    entityid FindPlayerOnlinePart( const std::string& p_name );
    entityid FindPlayerOnlineFull( const std::string& p_name );
    entityid FindPlayerPart( const std::string& p_name );
    entityid FindPlayerFull( const std::string& p_name );
    bool HasPlayer( entityid p_id )             { return m_players.find( p_id ) != m_players.end(); }

    // ------------------------------------------------------------------------
    // Timer Stuff
    // ------------------------------------------------------------------------
    BasicLib::sint64 GetTime()          { return m_gametime.GetMS(); }
    void ResetTime()                    { m_gametime.Reset(); }
    void AddActionRelative( BasicLib::sint64 p_time, const Action& p_action );
    void AddActionRelative( BasicLib::sint64 p_time, const std::string& p_act, entityid p_data1 = 0, entityid p_data2 = 0, entityid p_data3 = 0, entityid p_data4 = 0, const std::string& p_data = "" );
    void AddActionAbsolute( BasicLib::sint64 p_time, const Action& p_action );
    void AddActionAbsolute( BasicLib::sint64 p_time, const std::string& p_act, entityid p_data1 = 0, entityid p_data2 = 0, entityid p_data3 = 0, entityid p_data4 = 0, const std::string& p_data = "" );
    void AddTimedAction( TimedAction* p_action );
    void ExecuteLoop();

protected:
    characters m_characters;
    players m_players;
    bool m_running;
    BasicLib::Timer m_gametime;

    typedef std::priority_queue< TimedAction*, std::vector<TimedAction*>, TimedActionComp > timerqueue;
    timerqueue m_timerregistry;
};


extern Game g_game;


}   // end namespace BetterMUD


#endif
