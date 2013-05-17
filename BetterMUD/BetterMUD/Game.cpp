// MUD Programming
// Ron Penton
// (C)2003
// Game.cpp - The game logic of BetterMUD.
// 
// 


#include "Game.h"
#include "Exception.h"
#include "accessors/Accessors.h"
#include "databases/AccountDatabase.h"
#include "databases/CharacterDatabase.h"
#include "databases/ItemDatabase.h"
#include "databases/CommandDatabase.h"
#include "databases/LogicDatabase.h"
#include "databases/RoomDatabase.h"
#include "databases/PortalDatabase.h"
#include "databases/RegionDatabase.h"

namespace BetterMUD
{

// declare the static instances
Game g_game;


Game::Game()
{
    m_running = true;
}

Game::~Game()
{
    while( m_timerregistry.size() )
    {
        TimedAction* a = m_timerregistry.top();
        delete a;
        m_timerregistry.pop();
    }
}

// ------------------------------------------------------------------------
// Game Actions. 
// ------------------------------------------------------------------------
void Game::DoAction( 
    const std::string& p_act, 
    entityid p_data1, 
    entityid p_data2, 
    entityid p_data3, 
    entityid p_data4, 
    const std::string& p_data )
{
    DoAction( Action( p_act, p_data1, p_data2, p_data3, p_data4, p_data ) );
}



void Game::DoAction( const Action& p_action )
{
    if( p_action.actiontype == "chat" || 
        p_action.actiontype == "announce" )
        ActionRealmPlayers( p_action );
    else if( p_action.actiontype == "do" )
        RouteAction( p_action );
    else if( p_action.actiontype == "modifyattribute" )
        ModifyAttribute( p_action );
    else if( p_action.actiontype == "vision"  )
        ActionRoomCharacters( p_action, p_action.data1 );
    else if( p_action.actiontype == "enterrealm" )
        Login( p_action.data1 );
    else if( p_action.actiontype == "leaverealm" )
        Logout( p_action.data1 );
    else if( p_action.actiontype == "attemptsay" )
        Say( p_action.data1, p_action.stringdata );
    else if( p_action.actiontype == "command" )
        DoCommand( p_action.data1, p_action.stringdata );
    else if( p_action.actiontype == "attemptenterportal" )
        EnterPortal( p_action.data1, p_action.data2 );
    else if( p_action.actiontype == "attempttransport" )
        Transport( p_action.data1, p_action.data2 );
    else if( p_action.actiontype == "forcetransport" )
        ForceTransport( p_action.data1, p_action.data2 );
    else if( p_action.actiontype == "attemptgetitem" )
        GetItem( p_action.data1, p_action.data2, p_action.data3 );
    else if( p_action.actiontype == "attemptdropitem" )
        DropItem( p_action.data1, p_action.data2, p_action.data3 );
    else if( p_action.actiontype == "attemptgiveitem" )
        GiveItem( p_action.data1, p_action.data2, p_action.data3, p_action.data4 );
    else if( p_action.actiontype == "spawnitem" )
        SpawnItem( p_action.data1, p_action.data2, p_action.data3, p_action.data4 );
    else if( p_action.actiontype == "spawncharacter" )
        SpawnCharacter( p_action.data1, p_action.data2 );
    else if( p_action.actiontype == "destroyitem" )
        DestroyItem( p_action.data1 );
    else if( p_action.actiontype == "destroycharacter" )
        DestroyCharacter( p_action.data1 );
    else if( p_action.actiontype == "cleanup" )
        Cleanup();
    else if( p_action.actiontype == "savedatabases" )
        SaveAll();
    else if( p_action.actiontype == "saveregion" )
        SaveRegion( p_action.data1 );
    else if( p_action.actiontype == "saveplayers" )
        SavePlayers();
    else if( p_action.actiontype == "reloaditems" )
        ReloadItemTemplates( p_action.stringdata );
    else if( p_action.actiontype == "reloadcharacters" )
        ReloadCharacterTemplates( p_action.stringdata );
    else if( p_action.actiontype == "reloadregion" )
        ReloadRegion( p_action.stringdata );
    else if( p_action.actiontype == "reloadcommandscript" )
        ReloadCommandScript( p_action.stringdata, (SCRIPTRELOADMODE)p_action.data1 );
    else if( p_action.actiontype == "reloadlogicscript" )
        ReloadLogicScript( p_action.stringdata, (SCRIPTRELOADMODE)p_action.data1 );
    else if( p_action.actiontype == "messagelogic" )
        LogicAction( p_action );
    else if( p_action.actiontype == "addlogic" )
        AddLogic( p_action );
    else if( p_action.actiontype == "dellogic" )
        DelLogic( p_action );
}



void Game::ActionRealmPlayers( const Action& p_action )
{
    // tell every player about the action
    players::iterator itr = m_players.begin();
    while( itr != m_players.end() )
    {
        character p( *itr );
        p.DoAction( p_action );
        ++itr;
    }
}


void Game::ActionRealmCharacters( const Action& p_action )
{
    // tell every character about the action
    characters::iterator itr = m_characters.begin();
    while( itr != m_characters.end() )
    {
        character c( *itr );
        c.DoAction( p_action );
        ++itr;
    }
}


void Game::ActionRoomCharacters( const Action& p_action, entityid p_room )
{
    room r( p_room );
    r.BeginCharacter();
    while( r.IsValidCharacter() )
    {
        character c( r.CurrentCharacter() );
        c.DoAction( p_action );
        r.NextCharacter();
    }
}

void Game::ActionRoomItems( const Action& p_action, entityid p_room )
{
    room r( p_room );
    r.BeginItem();
    while( r.IsValidItem() )
    {
        item i( r.CurrentItem() );
        i.DoAction( p_action );
        r.NextItem();
    }
}

void Game::RouteAction( const Action& p_action )
{
    switch( p_action.data1 )
    {
    case CHARACTER:
        character( p_action.data2 ).DoAction( p_action );
        break;
    case ITEM:
        item( p_action.data2 ).DoAction( p_action );
        break;
    case ROOM:
        room( p_action.data2 ).DoAction( p_action );
        break;
    case PORTAL:
        portal( p_action.data2 ).DoAction( p_action );
        break;
    case REGION:
        region( p_action.data2 ).DoAction( p_action );
        break;
    }
}


void Game::ModifyAttribute( const Action& p_action )
{
    switch( p_action.data1 )
    {
    case CHARACTER:
        {
        character c( p_action.data2 );
        c.SetAttribute( p_action.stringdata, p_action.data3 );
        c.DoAction( p_action );
        }
        break;
    case ITEM:
        {
        item i( p_action.data2 );
        i.SetAttribute( p_action.stringdata, p_action.data3 );
        i.DoAction( p_action );
        }
        break;
    case ROOM:
        {
        room r( p_action.data2 );
        r.SetAttribute( p_action.stringdata, p_action.data3 );
        r.DoAction( p_action );
        }
        break;
    case PORTAL:
        {
        portal p( p_action.data2 );
        p.SetAttribute( p_action.stringdata, p_action.data3 );
        p.DoAction( p_action );
        }
        break;
    case REGION:
        {
        region reg( p_action.data2 );
        reg.SetAttribute( p_action.stringdata, p_action.data3 );
        reg.DoAction( p_action );
        }
        break;
    }
}

void Game::DoCommand( 
    entityid p_player,              // player doing command
    const std::string& p_command )  // command being executed
{
    // get the player
    Character& c = CharacterDB.get( p_player );

    std::string full = p_command;

    // handle "repeating commands" here
    if( full == "/" )
        full = c.LastCommand();         // repeat last command
    else
        c.SetLastCommand( full );       // set last command

    // get the first word  "the command"
    std::string command = BasicLib::ParseWord( full, 0 );

    // get the "the arguments"
    std::string args = BasicLib::RemoveWord( full, 0 );


    // in loud mode, commands must be prefixed with "/", everything else is 
    // local talking
    // in quiet mode, what you say must be a command
    if( !c.Quiet() && command[0] != '/' )
    {
        DoAction( "attemptsay", p_player, 0, 0, 0, full );
        return;
    }

    
    // if a string starts with '/', it is always assumed to be a command,
    // so erase the slash
    if( command[0] == '/' )
        command.erase( 0, 1 );

    // the next part must be inside a try block in case anything fails, you
    // don't want to bring down the whole game
    try
    {
        // try to find the command:
        Character::commands::iterator itr = c.FindCommand( command );
        if( itr == c.CommandsEnd() )
        {
            c.DoAction( "error", 0, 0, 0, 0, "Unrecognized Command: " + command );
            return;
        }

        // try executing the command:
        (*itr)->Execute( args );
    }
    catch( ... )
    {
        c.DoAction( "error", 0, 0, 0, 0, "SERIOUS ERROR: Cannot execute " + command + 
            ", please tell your administrator" );
    }
}



void Game::Say( 
    entityid p_player,              // character saying something
    const std::string& p_text )     // text being said
{
    // ========================================================================
    //  PERFORM LOOKUPS
    // ========================================================================
    character c( p_player );
    room r( c.Room() );
    region reg( c.Region() );

    // ========================================================================
    //  PERFORM QUERIES
    // ========================================================================
    // query the character to see if he can do it first.
    if( c.DoAction( "cansay", p_player, 0, 0, 0, p_text ) == 1 )
        return;
    if( r.DoAction( "cansay", p_player, 0, 0, 0, p_text ) == 1 )
        return;
    if( reg.DoAction( "cansay", p_player, 0, 0, 0, p_text ) == 1 )
        return;

    // ========================================================================
    //  PERFORM EVENT NOTIFICATIONS
    // ========================================================================
    ActionRoomCharacters( Action( "say", p_player, 0, 0, 0, p_text ), c.Room() );
    r.DoAction( "say", p_player, 0, 0, 0, p_text );
    reg.DoAction( "say", p_player, 0, 0, 0, p_text );
}


void Game::Login( 
    entityid p_id )                 // the ID of the character
{
    character c( p_id );
    room r( c.Room() );
    region reg( r.Region() );


    // add character to the game
    c.SetLoggedIn( true );
    AddCharacter( p_id );
    AddPlayer( p_id );
    reg.AddCharacter( p_id );
    r.AddCharacter( p_id );

    ActionRealmPlayers( Action( "enterrealm", p_id ) );
    reg.DoAction( Action( "enterregion", p_id ) );
    c.DoAction( Action( "enterregion", p_id ) );
    r.DoAction( Action( "enterroom", p_id, 0 ) );
    ActionRoomCharacters( Action( "enterroom", p_id, 0 ), r.ID() );
    ActionRoomItems( Action( "enterroom", p_id, 0 ), r.ID() );
}


void Game::Logout( 
        entityid p_id )                 // the ID of the character
{
    character c( p_id );
    room r( c.Room() );
    region reg( r.Region() );

    // tell everyone about it
    ActionRoomItems( Action( "leaveroom", p_id, 0 ), c.Room() );
    ActionRoomCharacters( Action( "leaveroom", p_id, 0 ), c.Room() );
    r.DoAction( Action( "leaveroom", p_id, 0 ) );
    c.DoAction( Action( "leaveregion", p_id ) );
    reg.DoAction( Action( "leaveregion", p_id ) );
    ActionRealmPlayers( Action( "leaverealm", p_id ) );

    // remove him from the game
    r.DelCharacter( p_id );
    reg.DelCharacter( p_id );
    RemovePlayer( p_id );
    RemoveCharacter( p_id );
    c.SetLoggedIn( false );
}



// tells a room that someone has entered
void Game::EnterPortal( 
    entityid p_character,                   // character who entered
    entityid p_portal )                     // portal entered from
{
    character c( p_character );
    portal p( p_portal );
    room oldroom( c.Room() );

    // make sure that character can enter portal from current room
    p.SeekStartRoom( c.Room() );
    if( !p.IsValidPath() )
        throw Exception( 
            "Character " + c.Name() + " tried entering portal " + p.Name() +
            " but has no exit from room " + BasicLib::tostring( c.Room() ) );

    // get the destination room
    room newroom( p.CurrentEnd() );
    bool changeregion = oldroom.Region() != newroom.Region();
    region oldreg( oldroom.Region() );
    region newreg( newroom.Region() );

    // "ask permission" of everyone to leave the room:
    if( changeregion )
    {
        if( oldreg.DoAction( "canleaveregion", p_character, oldreg.ID() ) == 1 )
            return;
        if( newreg.DoAction( "canenterregion", p_character, newreg.ID() ) == 1 )
            return;
        if( c.DoAction( "canleaveregion", p_character, oldreg.ID() ) == 1 )
            return;
        if( c.DoAction( "canenterregion", p_character, newreg.ID() ) == 1 )
            return;
    }

    if( oldroom.DoAction( "canleaveroom", p_character ) == 1 )
        return;
    if( newroom.DoAction( "canenterroom", p_character ) == 1 )
        return;
    if( c.DoAction( "canleaveroom", p_character ) == 1 )
        return;
    if( p.DoAction( "canenterportal", p_character ) == 1 )
        return;

    // tell the room that the player is leaving
    if( changeregion )
    {
        oldreg.DoAction( "leaveregion", p_character, oldreg.ID() );
        c.DoAction( "leaveregion", p_character, oldreg.ID() );
    }

    ActionRoomCharacters( Action( "leaveroom", p_character, p_portal ), c.Room() );
    ActionRoomItems( Action( "leaveroom", p_character, p_portal ), c.Room() );
    oldroom.DoAction( "leaveroom", p_character, p_portal );

    // now tell the portal that the player has actually entered
    p.DoAction( "enterportal", p_character, p.ID() );
    c.DoAction( "enterportal", p_character, p.ID() );

    // now move the character
    if( changeregion )
    {
        oldreg.DelCharacter( p_character );
        c.SetRegion( newreg.ID() );
        newreg.AddCharacter( p_character );
    }

    oldroom.DelCharacter( p_character );
    c.SetRoom( newroom.ID() );
    newroom.AddCharacter( p_character );

    // tell everyone in the room that the player has entered
    if( changeregion )
    {
        newreg.DoAction( "enterregion", p_character, newreg.ID() );
        c.DoAction( "enterregion", p_character, newreg.ID() );
    }

    newroom.DoAction( "enterroom", p_character, p_portal );
    ActionRoomCharacters( Action( "enterroom", p_character, p_portal ), c.Room() );
    ActionRoomItems( Action( "enterroom", p_character, p_portal ), c.Room() );
}


void Game::Transport( 
        entityid p_character,                   // character who left
        entityid p_room )                       // room id
{

    // ========================================================================
    //  PERFORM LOOKUPS
    // ========================================================================
    character c( p_character );
    room oldroom( c.Room() );
    room newroom( p_room );
    bool changeregion = oldroom.Region() != newroom.Region();
    region oldreg( oldroom.Region() );
    region newreg( newroom.Region() );

    // ========================================================================
    //  PERFORM QUERIES
    // ========================================================================
    // "ask permission" of everyone to leave the room:
    if( changeregion )
    {
        if( oldreg.DoAction( "canleaveregion", p_character, oldreg.ID() ) == 1 )
            return;
        if( newreg.DoAction( "canenterregion", p_character, newreg.ID() ) == 1 )
            return;
        if( c.DoAction( "canleaveregion", p_character, oldreg.ID() ) == 1 )
            return;
        if( c.DoAction( "canenterregion", p_character, newreg.ID() ) == 1 )
            return;
    }

    if( oldroom.DoAction( "canleaveroom", p_character, oldroom.ID() ) == 1 )
        return;
    if( newroom.DoAction( "canenterroom", p_character, newroom.ID() ) == 1 )
        return;
    if( c.DoAction( "canleaveroom", p_character, oldroom.ID() ) == 1 )
        return;
    if( c.DoAction( "canenterroom", p_character, newroom.ID() ) == 1 )
        return;


    // ========================================================================
    //  PHYSICAL MOVEMENT
    // ========================================================================
    // now move the character
    if( changeregion )
    {
        oldreg.DelCharacter( p_character );
        c.SetRegion( newreg.ID() );
        newreg.AddCharacter( p_character );
    }

    oldroom.DelCharacter( p_character );
    c.SetRoom( newroom.ID() );
    newroom.AddCharacter( p_character );


    // ========================================================================
    //  PERFORM EVENT NOTIFICATIONS
    // ========================================================================
    // tell the room that the player is leaving
    if( changeregion )
    {
        oldreg.DoAction( "leaveregion", p_character, oldreg.ID() );
        c.DoAction( "leaveregion", p_character, oldreg.ID() );
    }

    oldroom.DoAction( "leaveroom", p_character, 0 );
    c.DoAction( "leaveroom", p_character, 0 );
    ActionRoomCharacters( Action( "leaveroom", p_character, 0 ), c.Room() );
    ActionRoomItems( Action( "leaveroom", p_character, 0 ), c.Room() );

    // tell everyone in the room that the player has entered
    if( changeregion )
    {
        newreg.DoAction( "enterregion", p_character, newreg.ID() );
        c.DoAction( "enterregion", p_character, newreg.ID() );
    }

    newroom.DoAction( "enterroom", p_character, 0 );
    ActionRoomCharacters( Action( "enterroom", p_character, 0 ), c.Room() );
    ActionRoomItems( Action( "enterroom", p_character, 0 ), c.Room() );
}



void Game::ForceTransport( 
        entityid p_character,                   // character who left
        entityid p_room )                       // room id
{

    // ========================================================================
    //  PERFORM LOOKUPS
    // ========================================================================
    character c( p_character );
    room oldroom( c.Room() );
    room newroom( p_room );
    bool changeregion = oldroom.Region() != newroom.Region();
    region oldreg( oldroom.Region() );
    region newreg( newroom.Region() );

    // ========================================================================
    //  PHYSICAL MOVEMENT
    // ========================================================================
    // now move the character
    if( changeregion )
    {
        oldreg.DelCharacter( p_character );
        c.SetRegion( newreg.ID() );
        newreg.AddCharacter( p_character );
    }

    oldroom.DelCharacter( p_character );
    c.SetRoom( newroom.ID() );
    newroom.AddCharacter( p_character );


    // ========================================================================
    //  PERFORM EVENT NOTIFICATIONS
    // ========================================================================
    // tell the room that the player is leaving
    if( changeregion )
    {
        oldreg.DoAction( "leaveregion", p_character, oldreg.ID() );
        c.DoAction( "leaveregion", p_character, oldreg.ID() );
    }

    oldroom.DoAction( "leaveroom", p_character, 0 );
    c.DoAction( "leaveroom", p_character, 0 );
    ActionRoomCharacters( Action( "leaveroom", p_character, 0 ), c.Room() );
    ActionRoomItems( Action( "leaveroom", p_character, 0 ), c.Room() );

    // tell everyone in the room that the player has entered
    if( changeregion )
    {
        newreg.DoAction( "enterregion", p_character, newreg.ID() );
        c.DoAction( "enterregion", p_character, newreg.ID() );
    }

    newroom.DoAction( "enterroom", p_character, 0 );
    ActionRoomCharacters( Action( "enterroom", p_character, 0 ), c.Room() );
    ActionRoomItems( Action( "enterroom", p_character, 0 ), c.Room() );
}




void Game::GetItem( 
    entityid p_character,                   // character who wants item
    entityid p_item,                        // item
    entityid p_quantity )                   // optional quantity
{
    // ========================================================================
    //  PERFORM LOOKUPS
    // ========================================================================
    character c( p_character );
    item i( p_item );
    room r( c.Room() );
    region reg( r.Region() );


    // ========================================================================
    //  PERFORM STABILITY CHECKS
    // ========================================================================
    // make sure item and character are in the same room
    if( i.Room() != c.Room() || i.Region() == 0 )
        throw Exception( 
            "Character " + c.Name() + " tried picking up item " + i.Name() +
            " but they are not in the same room." );

    if( i.IsQuantity() && p_quantity < 1 )
    {
        c.DoAction( "error", 0, 0, 0, 0, 
            "You can't get " + BasicLib::tostring( p_quantity ) + 
            " of those, it's just not physically possible! FOOL!" );
        return;
    }

    if( i.IsQuantity() && p_quantity > i.GetQuantity() )
    {
        c.DoAction( "error", 0, 0, 0, 0, 
            "You can't get " + BasicLib::tostring( p_quantity ) + 
            ", there are only " + BasicLib::tostring( i.GetQuantity() ) + "!" );
        return;
    }

    // ========================================================================
    //  PERFORM QUERIES
    // ========================================================================
    if( i.DoAction( "cangetitem", p_character, p_item, p_quantity ) == 1 )
        return;
    if( r.DoAction( "cangetitem", p_character, p_item, p_quantity ) == 1 )
        return;
    if( reg.DoAction( "cangetitem", p_character, p_item, p_quantity ) == 1 )
        return;
    if( c.DoAction( "cangetitem", p_character, p_item, p_quantity ) == 1 )
        return;


    // ========================================================================
    //  PHYSICAL MOVEMENT
    // ========================================================================
    entityid newitemid = 0;
    if( i.IsQuantity() && p_quantity != i.GetQuantity() )
    {
        newitemid = ItemDB.generate( i.TemplateID() );      // generate new item
        item( newitemid ).SetQuantity( p_quantity );        // set quantity
        i.SetQuantity( i.GetQuantity() - p_quantity );      // reset old quantity
    }
    else
    {
        // normal transfer, delete from old room
        r.DelItem( p_item );
        reg.DelItem( p_item );
        newitemid = i.ID();
    }


    // now move the item to the player
    item newitem( newitemid );
    newitem.SetRoom( c.ID() );
    newitem.SetRegion( 0 );
    c.AddItem( newitem.ID() );


    // ========================================================================
    //  PERFORM EVENT NOTIFICATIONS
    // ========================================================================
    r.DoAction( "getitem", p_character, newitemid, p_quantity );
    newitem.DoAction( "getitem", p_character, newitemid, p_quantity );
    ActionRoomCharacters( Action( "getitem", p_character, newitemid, p_quantity ), c.Room() );
    ActionRoomItems( Action( "getitem", p_character, newitemid, p_quantity ), c.Room() );


    // ========================================================================
    //  JOIN QUANTITY ITEMS IF NEEDED
    // ========================================================================
    if( newitem.IsQuantity() )
        DoJoinQuantities( CharacterDB.get( c.ID() ), newitemid );
}





void Game::DropItem( 
    entityid p_character,                   // character who wants to drop item
    entityid p_item,                        // item
    entityid p_quantity )                   // optional quantity
{
    // ========================================================================
    //  PERFORM LOOKUPS
    // ========================================================================
    character c( p_character );
    item i( p_item );
    room r( c.Room() );
    region reg( r.Region() );

    // ========================================================================
    //  PERFORM STABILITY CHECKS
    // ========================================================================
    if( i.Room() != c.ID() || i.Region() != 0 )
        throw Exception( 
            "Character " + c.Name() + " tried dropping item " + i.Name() +
            " but he does not own it." );

    if( i.IsQuantity() && p_quantity < 1 )
    {
        c.DoAction( "error", 0, 0, 0, 0, 
            "You can't drop " + BasicLib::tostring( p_quantity ) + 
            " of those, it's just not physically possible! FOOL!" );
        return;
    }

    if( i.IsQuantity() && p_quantity > i.GetQuantity() )
    {
        c.DoAction( "error", 0, 0, 0, 0, 
            "You can't drop " + BasicLib::tostring( p_quantity ) + 
            ", there are only " + BasicLib::tostring( i.GetQuantity() ) + "!" );
        return;
    }


    // ========================================================================
    //  PERFORM QUERIES
    // ========================================================================
    if( i.DoAction( "candropitem", p_character, p_item ) == 1 )
        return;
    if( r.DoAction( "candropitem", p_character, p_item ) == 1 )
        return;
    if( c.DoAction( "candropitem", p_character, p_item ) == 1 )
        return;

    // ========================================================================
    //  PHYSICAL MOVEMENT
    // ========================================================================
    entityid newitemid = 0;
    if( i.IsQuantity() && p_quantity != i.GetQuantity() )
    {
        newitemid = ItemDB.generate( i.TemplateID() );      // generate new item
        item( newitemid ).SetQuantity( p_quantity );        // set quantity
        i.SetQuantity( i.GetQuantity() - p_quantity );      // reset old quantity
    }
    else
    {
        // normal transfer, delete from old player
        c.DelItem( p_item );
        newitemid = i.ID();
    }

    // now move the item to the room
    item newitem( newitemid );
    newitem.SetRoom( r.ID() );
    newitem.SetRegion( reg.ID() );
    r.AddItem( newitemid );
    reg.AddItem( newitemid );


    // ========================================================================
    //  PERFORM EVENT NOTIFICATIONS
    // ========================================================================
    r.DoAction( "dropitem", p_character, newitemid, p_quantity );
    ActionRoomCharacters( Action( "dropitem", p_character, newitemid, p_quantity ), c.Room() );
    ActionRoomItems( Action( "dropitem", p_character, newitemid, p_quantity ), c.Room() );

    // ========================================================================
    //  JOIN QUANTITY ITEMS IF NEEDED
    // ========================================================================
    if( newitem.IsQuantity() )
        DoJoinQuantities( RoomDB.get( r.ID() ), newitem.ID() );
}


void Game::GiveItem( 
    entityid p_giver,                       // character who is giving
    entityid p_receiver,                    // character who is getting
    entityid p_item,                        // item
    entityid p_quantity )                   // optional quantity
{
    // ========================================================================
    //  PERFORM LOOKUPS
    // ========================================================================
    character g( p_giver );
    character r( p_receiver );
    item i( p_item );

    // ========================================================================
    //  PERFORM STABILITY CHECKS
    // ========================================================================
    if( g.Room() != r.Room() )
        throw Exception( 
            "Character " + g.Name() + " tried giving item " + i.Name() +
            " to " + r.Name() + " but they are not in the same room." );

    if( i.IsQuantity() && p_quantity < 1 )
    {
        g.DoAction( "error", 0, 0, 0, 0, 
            "You can't give away " + BasicLib::tostring( p_quantity ) + 
            " of those, it's just not physically possible! FOOL!" );
        return;
    }

    if( i.IsQuantity() && p_quantity > i.GetQuantity() )
    {
        g.DoAction( "error", 0, 0, 0, 0, 
            "You can't give away " + BasicLib::tostring( p_quantity ) + 
            ", you only have " + BasicLib::tostring( i.GetQuantity() ) + "!" );
        return;
    }

    // ========================================================================
    //  PERFORM QUERIES
    // ========================================================================
    if( i.DoAction( "candropitem", p_giver, p_item, p_quantity ) == 1 ||
        g.DoAction( "candropitem", p_giver, p_item, p_quantity ) == 1  ||
        i.DoAction( "canreceiveitem", p_giver, p_receiver, p_item, p_quantity ) == 1 ||
        r.DoAction( "canreceiveitem", p_giver, p_receiver, p_item, p_quantity ) == 1 )
        return;

    // ========================================================================
    //  PHYSICAL MOVEMENT
    // ========================================================================
    entityid newitemid = 0;
    if( i.IsQuantity() && p_quantity != i.GetQuantity() )
    {
        newitemid = ItemDB.generate( i.TemplateID() );      // generate new item
        item( newitemid ).SetQuantity( p_quantity );        // set quantity
        i.SetQuantity( i.GetQuantity() - p_quantity );      // reset old quantity
    }
    else
    {
        // normal transfer, delete from old player
        g.DelItem( p_item );
        newitemid = i.ID();
    }

    // now move the item to the other player
    item newitem( newitemid );
    newitem.SetRoom( r.ID() );
    r.AddItem( newitemid );


    // ========================================================================
    //  PERFORM EVENT NOTIFICATIONS
    // ========================================================================
    ActionRoomCharacters( Action( "giveitem", p_giver, p_receiver, newitemid, p_quantity ), g.Room() );


    // ========================================================================
    //  JOIN QUANTITY ITEMS IF NEEDED
    // ========================================================================
    if( newitem.IsQuantity() )
        DoJoinQuantities( CharacterDB.get( r.ID() ), newitemid );

}



void Game::SpawnItem( 
    entityid p_itemtemplate,                // template of item
    entityid p_location,                    // location to put it
    entityid p_player,                      // player or room?
    entityid p_quantity )                   // optional quantity
{
    entityid newitem = ItemDB.generate( p_itemtemplate );
    item i( newitem );

    if( p_player == 0 )
    {
        // load up the room and region
        room r( p_location );
        region reg( r.Region() );
        
        // physically place it into the realm
        i.SetRoom( p_location );
        i.SetRegion( r.Region() );
        r.AddItem( i.ID() );
        reg.AddItem( i.ID() );

        // tell the room and the region about the new item
        r.DoAction( "spawnitem", newitem );
        reg.DoAction( "spawnitem", newitem );
    }
    else
    {
        // load up the character
        character c( p_location );
        
        // physically place it into the player
        i.SetRoom( p_location );
        i.SetRegion( 0 );
        c.AddItem( i.ID() );

        // tell the characterabout the new item
        c.DoAction( "spawnitem", newitem );
    }
}


void Game::SpawnCharacter( 
    entityid p_chartemplate,                // template of character
    entityid p_location )                   // location to put it
{
    entityid newchar = CharacterDB.generate( p_chartemplate );
    character c( newchar );
    room r( p_location );
    region reg( r.Region() );

    // physically place it into the realm
    c.SetRoom( r.ID() );
    c.SetRegion( reg.ID() );
    r.AddCharacter( c.ID() );
    reg.AddCharacter( c.ID() );

    // tell the room and the region about the new item
    r.DoAction( "spawncharacter", newchar );
    reg.DoAction( "spawncharacter", newchar );
}




void Game::DestroyItem( entityid p_item )
{
    item i( p_item );

    if( i.Region() == 0 )
    {
        character c( i.Room() );
        c.DoAction( "destroyitem", p_item );
        i.DoAction( "destroyitem", p_item );
    }
    else
    {
        room r( i.Room() );
        region reg( i.Region() );
        reg.DoAction( "destroyitem", p_item );
        r.DoAction( "destroyitem", p_item );
        i.DoAction( "destroyitem", p_item );
    }

    DeleteItem( p_item );
}


void Game::DestroyCharacter( entityid p_character )
{
    character c( p_character );
    room r( c.Room() );
    region reg( c.Region() );

    if( c.IsPlayer() )
        throw Exception( "Trying to delete a player" );

    reg.DoAction( "destroycharacter", p_character );
    r.DoAction( "destroycharacter", p_character );
    c.DoAction( "destroycharacter", p_character );


    // force the items into the room
    c.BeginItem();
    while( c.IsValidItem() )
    {
        item i( c.CurrentItem() );
        r.AddItem( i.ID() );
        reg.AddItem( i.ID() );
        i.SetRoom( r.ID() );
        i.SetRegion( reg.ID() );
        r.DoAction( "dropitem", p_character, i.ID(), i.GetQuantity() );
        reg.DoAction( "dropitem", p_character, i.ID(), i.GetQuantity() );
        c.NextItem();
    }


    r.DelCharacter( p_character );
    reg.DelCharacter( p_character );

    c.ClearHooks();
    c.SetRoom( 0 );
    c.SetRegion( 0 );
    CharacterDB.erase( p_character );
}




void Game::LogicAction( const Action& p_act )
{
    std::string modname = BasicLib::ParseWord( p_act.stringdata, 0 );
    Logic* l = 0;
    switch( p_act.data1 )
    {
    case CHARACTER:
        l = character( p_act.data2 ).GetLogic( modname );
        break;
    case ITEM:
        l = item( p_act.data2 ).GetLogic( modname );
        break;
    case ROOM:
        l = room( p_act.data2 ).GetLogic( modname );
        break;
    case PORTAL:
        l = portal( p_act.data2 ).GetLogic( modname );
        break;
    case REGION:
        l = region( p_act.data2 ).GetLogic( modname );
        break;
    }
    if( !l )   throw Exception( "Game::LogicAction: Cannot load logic " + modname );
    l->DoAction( p_act );
}

void Game::AddLogic( const Action& p_act )
{
    switch( p_act.data1 )
    {
    case CHARACTER:
        character( p_act.data2 ).AddLogic( p_act.stringdata );
        break;
    case ITEM:
        item( p_act.data2 ).AddLogic( p_act.stringdata );
        break;
    case ROOM:
        room( p_act.data2 ).AddLogic( p_act.stringdata );
        break;
    case PORTAL:
        portal( p_act.data2 ).AddLogic( p_act.stringdata );
        break;
    case REGION:
        region( p_act.data2 ).AddLogic( p_act.stringdata );
        break;
    }
}

void Game::DelLogic( const Action& p_act  )
{
    switch( p_act.data1 )
    {
    case CHARACTER:
        character( p_act.data2 ).DelLogic( p_act.stringdata );
        break;
    case ITEM:
        item( p_act.data2 ).DelLogic( p_act.stringdata );
        break;
    case ROOM:
        room( p_act.data2 ).DelLogic( p_act.stringdata );
        break;
    case PORTAL:
        portal( p_act.data2 ).DelLogic( p_act.stringdata );
        break;
    case REGION:
        region( p_act.data2 ).DelLogic( p_act.stringdata );
        break;
    }
}




void Game::DeleteItem( entityid p_item )
{
    item i( p_item );
    if( i.Region() )
    {
        region reg( i.Region() );
        reg.DelItem( p_item );
        room r( i.Room() );
        r.DelItem( p_item );
    }
    else
    {
        character c( i.Room() );
        c.DelItem( p_item );
    }

    i.SetRoom( 0 );
    i.SetRegion( 0 );
    i.ClearHooks();
    ItemDB.erase( p_item );
}





void Game::Cleanup()
{
    ItemDB.Cleanup();
    CharacterDB.Cleanup();
}


void Game::SaveAll()
{
    AccountDB.Save();
    CharacterDB.SavePlayers();
    RegionDB.SaveAll();
    SaveTimers();
}

void Game::SavePlayers()
{
    AccountDB.Save();
    CharacterDB.SavePlayers();
}


void Game::SaveRegion( entityid p_region )
{
    RegionDB.SaveRegion( p_region );
}


void Game::LoadAll()
{
    // load the templates and accounts first; they depend on nothing else
    AccountDB.Load();
    CharacterDB.LoadTemplates();
    ItemDB.LoadTemplates();

    // load the scripts now
    InitPython();
    CommandDB.Load();
    LogicDB.Load();

    // load the regions
    RegionDB.LoadAll();
    CharacterDB.LoadPlayers();

    LoadTimers();
}


void Game::ReloadItemTemplates( const std::string& p_file )
{
    ItemDB.LoadTemplates( p_file );
}

void Game::ReloadCharacterTemplates( const std::string& p_file )
{
    CharacterDB.LoadTemplates( p_file );
}

void Game::ReloadRegion( const std::string& p_name )
{
    RegionDB.LoadRegion( p_name );
}
void Game::ReloadCommandScript( const std::string& p_name, SCRIPTRELOADMODE p_mode )
{
    CommandDB.Reload( "data.commands." + p_name, p_mode );
}
void Game::ReloadLogicScript( const std::string& p_name, SCRIPTRELOADMODE p_mode )
{
    LogicDB.Reload( "data.logics." + p_name, p_mode );
}


void Game::SaveTimers()
{
    std::ofstream timerfile( "data/timers/timers.data", std::ios::binary );

    
    timerfile << "[GAMETIME]              ";
    BasicLib::insert( timerfile, GetTime() );
    timerfile << "\n\n";
    
    // copy the timer queue
    timerqueue temp( m_timerregistry );
    while( temp.size() )
    {
        TimedAction* a = temp.top();
        temp.pop();
        a->Save( timerfile );
        timerfile << "\n";
    }
}


void Game::LoadTimers()
{
    std::ifstream timerfile( "data/timers/timers.data", std::ios::binary );
    std::string temp;
    timerfile >> std::ws;

    if( timerfile.good() )
    {
        timerfile >> temp;
        BasicLib::sint64 t;
        BasicLib::extract( timerfile, t );
        m_gametime.Reset( t );    

        timerfile >> std::ws;

        while( timerfile.good() )
        {
            TimedAction* a = new TimedAction;
            a->Load( timerfile );
            timerfile >> std::ws;
            AddTimedAction( a );
        }
    }
}


entityid Game::FindPlayerOnlinePart( const std::string& p_name )
{
    players::iterator itr = (match<character>( PlayersBegin(), PlayersEnd(), p_name ));
    if( itr != PlayersEnd() )
        return *itr;
    return 0;
}


entityid Game::FindPlayerOnlineFull( const std::string& p_name )
{
    players::iterator itr = (matchonepass<character>( PlayersBegin(), PlayersEnd(), stringmatchfull( p_name ) ));
    if( itr != PlayersEnd() )
        return *itr;
    return 0;
}

entityid Game::FindPlayerPart( const std::string& p_name )
{
    return CharacterDB.FindPlayerPart( p_name );
}

entityid Game::FindPlayerFull( const std::string& p_name )
{
    return CharacterDB.FindPlayerFull( p_name );
}




void Game::AddActionRelative( BasicLib::sint64 p_time, const Action& p_action )
{
    AddTimedAction( new TimedAction( p_time + GetTime(), p_action ) );
}

void Game::AddActionRelative( 
    BasicLib::sint64 p_time, 
    const std::string& p_act, 
    entityid p_data1, 
    entityid p_data2, 
    entityid p_data3, 
    entityid p_data4, 
    const std::string& p_data )
{
    AddTimedAction( 
        new TimedAction( 
            p_time + GetTime(), 
            Action( p_act, p_data1, p_data2, p_data3, p_data4, p_data ) ) );
}

void Game::AddActionAbsolute( BasicLib::sint64 p_time, const Action& p_action )
{
    AddTimedAction( new TimedAction( p_time, p_action ) );
}

void Game::AddActionAbsolute( 
    BasicLib::sint64 p_time, 
    const std::string& p_act, 
    entityid p_data1, 
    entityid p_data2, 
    entityid p_data3, 
    entityid p_data4, 
    const std::string& p_data )
{
    AddTimedAction( 
        new TimedAction( 
            p_time, 
            Action( p_act, p_data1, p_data2, p_data3, p_data4, p_data ) ) );
}


void Game::ExecuteLoop()
{
    BasicLib::sint64 t = GetTime();

    while( m_timerregistry.size() > 0 && 
           m_timerregistry.top()->executiontime <= t )
    {
        TimedAction* a = m_timerregistry.top();
        m_timerregistry.pop();
 
        // perform the action if it's a valid one (ie: it hasn't been unhooked)
        if( a->valid )
        {
            try {
            a->Unhook();                        // unhook it
            DoAction( a->actionevent );
            }   catch( ... ) {}
        }

        // delete it
        delete a;
    }
}


void Game::AddTimedAction( TimedAction* p_action )
{
    std::cout << p_action->actionevent.actiontype << "\n";
    std::cout << p_action->actionevent.stringdata << "\n";
    BasicLib::insert( std::cout, p_action->executiontime );
    std::cout << std::endl;

    m_timerregistry.push( p_action );
    p_action->Hook();
}





}   // end namespace BetterMUD
