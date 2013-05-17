// MUD Programming
// Ron Penton
// (C)2003
// SWIGHeaders.h - This file contains all of the information SWIG needs to 
//                 generate python files
// 
// 


typedef unsigned long int entityid;
typedef signed long int status;


class account
{
public:
    account( entityid p_id );
    ~account();
    entityid ID();
    std::string Name();
    std::string Description();
    void SetID( entityid p_id );
    void SetName( const std::string& p_name );
    void SetDescription( const std::string& p_desc );

    void AddCharacter( entityid p_id );
    void DelCharacter( entityid p_id );
    size_t Characters();
    void BeginCharacter();
    entityid CurrentCharacter();
    void NextCharacter();
    bool IsValidCharacter();
    void SeekCharacter( const std::string& p_name );

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



class charactertemplate
{
public:
    charactertemplate( entityid p_id );
    ~charactertemplate();
    entityid ID();
    std::string Name();
    std::string Description();

    int GetAttribute( const std::string& p_name );
    void SetAttribute( const std::string& p_name, int p_val );
    bool HasAttribute( const std::string& p_name );
    void AddAttribute( const std::string& p_name, int p_initialval );
    void DelAttribute( const std::string& p_name );
};



class character
{
public:
    character( entityid p_id );
    ~character();
    entityid ID();
    std::string Name();
    std::string Description();
    void SetID( entityid p_id );
    void SetName( const std::string& p_name );
    void SetDescription( const std::string& p_desc );

    entityid Room();
    void SetRoom( entityid p_room );

    entityid Region();
    void SetRegion( entityid p_region );

    entityid TemplateID();
    void SetTemplateID( entityid p_templateid );

    void AddItem( entityid p_id );
    void DelItem( entityid p_id );
    size_t Items();
    void BeginItem();
    entityid CurrentItem();
    void NextItem();
    bool IsValidItem();
    void SeekItem( const std::string& p_name );

    int GetAttribute( const std::string& p_name );
    void SetAttribute( const std::string& p_name, int p_val );
    bool HasAttribute( const std::string& p_name );
    void AddAttribute( const std::string& p_name, int p_initialval );
    void DelAttribute( const std::string& p_name );

    bool AddLogic( const std::string& p_logic );
    bool AddExistingLogic( Logic* p_logic );
    bool DelLogic( const std::string& p_logic );
    Logic* GetLogic( const std::string& p_logic );
    bool HasLogic( const std::string& p_logic );
    int DoAction( const Action& p_action );
    int DoAction( const std::string& p_act, entityid p_data1, entityid p_data2, entityid p_data3, entityid p_data4, const std::string& p_data );
    int GetLogicAttribute( const std::string& p_logic, const std::string& p_attr );
    void AddHook( TimedAction* p_hook );
    void DelHook( TimedAction* p_hook );
    size_t Hooks();
    void KillHook( const std::string& p_act, const std::string& p_stringdata );
    void ClearHooks();

    bool HasCommand( const std::string& p_command );
    bool AddCommand( const std::string& p_command );
    bool DelCommand( const std::string& p_command );
    void BeginCommands();
    std::string CurrentCommand();
    std::string CurrentCommandUsage();
    std::string CurrentCommandDescription();
    void NextCommand();
    bool IsValidCommand();
    void SeekCommand( const std::string& p_name );

    // accessors:
    bool Quiet();
    bool IsPlayer();
    bool Verbose();
    entityid GetAccount();
    void SetQuiet( bool p_quiet );
    void SetAccount( entityid p_account );
    bool IsLoggedIn();
    std::string LastCommand();

};


class itemtemplate
{
public:

    itemtemplate( entityid p_item );
    ~itemtemplate();
    entityid ID();
    std::string Name();
    std::string Description();

    int GetAttribute( const std::string& p_name );
    void SetAttribute( const std::string& p_name, int p_val );
    bool HasAttribute( const std::string& p_name );
    void AddAttribute( const std::string& p_name, int p_initialval );
    void DelAttribute( const std::string& p_name );

    bool IsQuantity();
    int GetQuantity();

};  // end class itemtemplate


class item
{
public:

    item( entityid p_item );
    ~item();
    entityid ID();
    std::string Name();
    std::string Description();
    void SetID( entityid p_id );
    void SetName( const std::string& p_name );
    void SetDescription( const std::string& p_desc );
   
    entityid Room();
    void SetRoom( entityid p_room );

    entityid Region();
    void SetRegion( entityid p_region );

    entityid TemplateID();
    void SetTemplateID( entityid p_templateid );

    int GetAttribute( const std::string& p_name );
    void SetAttribute( const std::string& p_name, int p_val );
    bool HasAttribute( const std::string& p_name );
    void AddAttribute( const std::string& p_name, int p_initialval );
    void DelAttribute( const std::string& p_name );

    bool AddLogic( const std::string& p_logic );
    bool AddExistingLogic( Logic* p_logic );
    bool DelLogic( const std::string& p_logic );
    Logic* GetLogic( const std::string& p_logic );
    bool HasLogic( const std::string& p_logic );
    int DoAction( const Action& p_action );
    int DoAction( const std::string& p_act, entityid p_data1, entityid p_data2, entityid p_data3, entityid p_data4, const std::string& p_data );
    int GetLogicAttribute( const std::string& p_logic, const std::string& p_attr );
    void AddHook( TimedAction* p_hook );
    void DelHook( TimedAction* p_hook );
    size_t Hooks();
    void KillHook( const std::string& p_act, const std::string& p_stringdata );
    void ClearHooks();

    bool IsQuantity();
    int GetQuantity();
    void SetQuantity( int p_quantity );

};  // end class item




class portal
{
public:
    portal( entityid p_id );
    ~portal();

    entityid ID();
    std::string Name();
    std::string Description();
    void SetID( entityid p_id );
    void SetName( const std::string& p_name );
    void SetDescription( const std::string& p_desc );

    entityid Region();
    void SetRegion( entityid p_region );

    int GetAttribute( const std::string& p_name );
    void SetAttribute( const std::string& p_name, int p_val );
    bool HasAttribute( const std::string& p_name );
    void AddAttribute( const std::string& p_name, int p_initialval );
    void DelAttribute( const std::string& p_name );

    bool AddLogic( const std::string& p_logic );
    bool AddExistingLogic( Logic* p_logic );
    bool DelLogic( const std::string& p_logic );
    Logic* GetLogic( const std::string& p_logic );
    bool HasLogic( const std::string& p_logic );
    int DoAction( const Action& p_action );
    int DoAction( const std::string& p_act, entityid p_data1, entityid p_data2, entityid p_data3, entityid p_data4, const std::string& p_data );
    int GetLogicAttribute( const std::string& p_logic, const std::string& p_attr );
    void AddHook( TimedAction* p_hook );
    void DelHook( TimedAction* p_hook );
    size_t Hooks();
    void KillHook( const std::string& p_act, const std::string& p_stringdata );
    void ClearHooks();

    // iterator functions:
    void BeginPath();
    entityid CurrentStart();
    std::string CurrentDirection();
    entityid CurrentEnd();
    void NextPath();
    bool IsValidPath();

    // These functions seek the iterator to the exit that matches a specific
    // starting or ending point
    void SeekStartRoom( entityid p_room );
    void SeekEndRoom( entityid p_room );


};


class region
{
public:
    region( entityid p_id );
    ~region();
    entityid ID();
    std::string Name();
    std::string Description();
    void SetID( entityid p_id );
    void SetName( const std::string& p_name );
    void SetDescription( const std::string& p_desc );

    void AddItem( entityid p_id );
    void DelItem( entityid p_id );
    size_t Items();
    void BeginItem();
    entityid CurrentItem();
    void NextItem();
    bool IsValidItem();
    void SeekItem( const std::string& p_name );

    void AddCharacter( entityid p_id );
    void DelCharacter( entityid p_id );
    size_t Characters();
    void BeginCharacter();
    entityid CurrentCharacter();
    void NextCharacter();
    bool IsValidCharacter();
    void SeekCharacter( const std::string& p_name );

    typedef std::set<entityid> rooms;
    void AddRoom( entityid p_id );
    void DelRoom( entityid p_id );
    size_t Rooms();
    void BeginRoom();
    entityid CurrentRoom();
    void NextRoom();
    bool IsValidRoom();
    void SeekRoom( const std::string& p_name );
    rooms::iterator m_roomitr;

    typedef std::set<entityid> portals;
    void AddPortal( entityid p_id );
    void DelPortal( entityid p_id );
    size_t Portals();
    void BeginPortal();
    entityid CurrentPortal();
    void NextPortal();
    bool IsValidPortal();
    void SeekPortal( const std::string& p_name );
    portals::iterator m_portalitr;

    int GetAttribute( const std::string& p_name );
    void SetAttribute( const std::string& p_name, int p_val );
    bool HasAttribute( const std::string& p_name );
    void AddAttribute( const std::string& p_name, int p_initialval );
    void DelAttribute( const std::string& p_name );

    bool AddLogic( const std::string& p_logic );
    bool AddExistingLogic( Logic* p_logic );
    bool DelLogic( const std::string& p_logic );
    Logic* GetLogic( const std::string& p_logic );
    bool HasLogic( const std::string& p_logic );
    int DoAction( const Action& p_action );
    int DoAction( const std::string& p_act, entityid p_data1, entityid p_data2, entityid p_data3, entityid p_data4, const std::string& p_data );
    int GetLogicAttribute( const std::string& p_logic, const std::string& p_attr );
    void AddHook( TimedAction* p_hook );
    void DelHook( TimedAction* p_hook );
    size_t Hooks();
    void KillHook( const std::string& p_act, const std::string& p_stringdata );
    void ClearHooks();
};



class room
{
public:
    room( entityid p_room );
    ~room();
    entityid ID();
    std::string Name();
    std::string Description();
    void SetID( entityid p_id );
    void SetName( const std::string& p_name );
    void SetDescription( const std::string& p_desc );

    entityid Region();
    void SetRegion( entityid p_region );

    void AddItem( entityid p_id );
    void DelItem( entityid p_id );
    size_t Items();
    void BeginItem();
    entityid CurrentItem();
    void NextItem();
    bool IsValidItem();
    void SeekItem( const std::string& p_name );

    void AddCharacter( entityid p_id );
    void DelCharacter( entityid p_id );
    size_t Characters();
    void BeginCharacter();
    entityid CurrentCharacter();
    void NextCharacter();
    bool IsValidCharacter();
    void SeekCharacter( const std::string& p_name );

    typedef std::set<entityid> portals;
    void AddPortal( entityid p_id );
    void DelPortal( entityid p_id );
    size_t Portals();
    void BeginPortal();
    entityid CurrentPortal();
    void NextPortal();
    bool IsValidPortal();
    void SeekPortal( const std::string& p_name );
    portals::iterator m_portalitr;

    int GetAttribute( const std::string& p_name );
    void SetAttribute( const std::string& p_name, int p_val );
    bool HasAttribute( const std::string& p_name );
    void AddAttribute( const std::string& p_name, int p_initialval );
    void DelAttribute( const std::string& p_name );

    bool AddLogic( const std::string& p_logic );
    bool AddExistingLogic( Logic* p_logic );
    bool DelLogic( const std::string& p_logic );
    Logic* GetLogic( const std::string& p_logic );
    bool HasLogic( const std::string& p_logic );
    int DoAction( const Action& p_action );
    int DoAction( const std::string& p_act, entityid p_data1, entityid p_data2, entityid p_data3, entityid p_data4, const std::string& p_data );
    int GetLogicAttribute( const std::string& p_logic, const std::string& p_attr );
    void AddHook( TimedAction* p_hook );
    void DelHook( TimedAction* p_hook );
    size_t Hooks();
    void KillHook( const std::string& p_act, const std::string& p_stringdata );
    void ClearHooks();
};



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

    long long GetTime();
    void ResetTime();

    void DoAction( 
        const std::string& p_act, 
        entityid p_data1, 
        entityid p_data2, 
        entityid p_data3, 
        entityid p_data4, 
        const std::string& p_data );


    void AddActionRelative( 
        long long p_time,
        const std::string& p_act, 
        entityid p_data1, 
        entityid p_data2, 
        entityid p_data3, 
        entityid p_data4, 
        const std::string& p_data );

    void AddActionAbsolute( 
        long long p_time,
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
};
