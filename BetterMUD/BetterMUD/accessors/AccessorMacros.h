// MUD Programming
// Ron Penton
// (C)2003
// AccessorMacros.h - This file includes loads of helpful accessor macro functions
// 
// 


#ifndef BETTERMUDACCESSORMACROS_H
#define BETTERMUDACCESSORMACROS_H


// ============================================================================
//  Entity header definitions
// ============================================================================
#define ENTITYHEADERS( AC )                                                 \
    AC( entityid p_id );                                                    \
    AC( const AC& p_right );                                                \
    AC& operator=( const AC& p_right );                                     \
    ~AC();                                                                  \
    entityid ID();                                                          \
    std::string Name();                                                     \
    std::string Description();                                              \
    void SetID( entityid p_id );                                            \
    void SetName( const std::string& p_name );                              \
    void SetDescription( const std::string& p_desc );

#define ENTITYTEMPLATEHEADERS( AC )                                         \
    AC( entityid p_id );                                                    \
    AC( const AC& p_right );                                                \
    AC& operator=( const AC& p_right );                                     \
    ~AC();                                                                  \
    entityid ID();                                                          \
    std::string Name();                                                     \
    std::string Description();


// ============================================================================
//  Entity implementation definitions
// ============================================================================
#define ENTITYIMPLEMENTATIONS( AC, PT, DB )                                 \
AC::AC( entityid p_id )                                                     \
{                                                                           \
    PT = &(DB.get( p_id ) );                                                \
    PT->AddRef();                                                           \
}                                                                           \
AC::AC( const AC& p_right )                                                 \
{                                                                           \
    PT->DelRef();                                                           \
    PT = p_right.PT;                                                        \
    PT->AddRef();                                                           \
}                                                                           \
AC& AC::operator=( const AC& p_right )                                      \
{                                                                           \
    PT = p_right.PT;                                                        \
    PT->AddRef();                                                           \
    return *this;                                                           \
}                                                                           \
AC::~AC()  { PT->DelRef(); }                                                \
entityid AC::ID()                                   { return PT->ID(); }                \
std::string AC::Name()                              { return PT->Name(); }              \
std::string AC::Description()                       { return PT->Description(); }       \
void AC::SetID( entityid p_id )                     { PT->SetID( p_id ); }              \
void AC::SetName( const std::string& p_name )       { PT->SetName( p_name ); }          \
void AC::SetDescription( const std::string& p_desc ){ PT->SetDescription( p_desc ); }



#define ENTITYTEMPLATEIMPLEMENTATIONS( AC, PT, DB )                         \
AC::AC( entityid p_id )                                                     \
{                                                                           \
    PT = &(DB.gettemplate( p_id ) );                                        \
    PT->AddRef();                                                           \
}                                                                           \
AC::AC( const AC& p_right )                                                 \
{                                                                           \
    PT->DelRef();                                                           \
    PT = p_right.PT;                                                        \
    PT->AddRef();                                                           \
}                                                                           \
AC& AC::operator=( const AC& p_right )                                      \
{                                                                           \
    PT = p_right.PT;                                                        \
    PT->AddRef();                                                           \
    return *this;                                                           \
}                                                                           \
AC::~AC()  { PT->DelRef(); }                                                \
entityid AC::ID()                                   { return PT->ID(); }                \
std::string AC::Name()                              { return PT->Name(); }              \
std::string AC::Description()                       { return PT->Description(); }


// ============================================================================
//  Mixin header definitions
// ============================================================================
#define HASREGIONHEADERS                                                    \
    entityid Region();                                                      \
    void SetRegion( entityid p_region );

#define HASROOMHEADERS                                                      \
    entityid Room();                                                        \
    void SetRoom( entityid p_room );

#define HASTEMPLATEIDHEADERS                                                \
    entityid TemplateID();                                                  \
    void SetTemplateID( entityid p_templateid );

#define HASCHARACTERSHEADERS                                                \
    typedef std::set<entityid> characters;                                  \
    void AddCharacter( entityid p_id );                                     \
    void DelCharacter( entityid p_id );                                     \
    size_t Characters();                                                    \
    void BeginCharacter();                                                  \
    entityid CurrentCharacter();                                            \
    void NextCharacter();                                                   \
    bool IsValidCharacter();                                                \
    void SeekCharacter( const std::string& p_name );                        \
    characters::iterator m_charitr;

#define HASITEMSHEADERS                                                     \
    typedef std::set<entityid> items;                                       \
    typedef items::iterator itemitr;                                        \
    void AddItem( entityid p_id );                                          \
    void DelItem( entityid p_id );                                          \
    size_t Items();                                                         \
    void BeginItem();                                                       \
    entityid CurrentItem();                                                 \
    void NextItem();                                                        \
    bool IsValidItem();                                                     \
    void SeekItem( const std::string& p_name );                             \
    itemitr m_itemitr;

#define HASROOMSHEADERS                                                     \
    typedef std::set<entityid> rooms;                                       \
    void AddRoom( entityid p_id );                                          \
    void DelRoom( entityid p_id );                                          \
    size_t Rooms();                                                         \
    void BeginRoom();                                                       \
    entityid CurrentRoom();                                                 \
    void NextRoom();                                                        \
    bool IsValidRoom();                                                     \
    void SeekRoom( const std::string& p_name );                             \
    rooms::iterator m_roomitr;

#define HASPORTALSHEADERS                                                   \
    typedef std::set<entityid> portals;                                     \
    void AddPortal( entityid p_id );                                        \
    void DelPortal( entityid p_id );                                        \
    size_t Portals();                                                       \
    void BeginPortal();                                                     \
    entityid CurrentPortal();                                               \
    void NextPortal();                                                      \
    bool IsValidPortal();                                                   \
    void SeekPortal( const std::string& p_name );                           \
    portals::iterator m_portalitr

#define HASDATABANKHEADERS                                                  \
    int GetAttribute( const std::string& p_name );                          \
    void SetAttribute( const std::string& p_name, int p_val );              \
    bool HasAttribute( const std::string& p_name );                         \
    void AddAttribute( const std::string& p_name, int p_initialval );       \
    void DelAttribute( const std::string& p_name );

#define HASLOGICHEADERS                                                     \
    bool AddLogic( const std::string& p_logic );                            \
    bool AddExistingLogic( Logic* p_logic );                                \
    bool DelLogic( const std::string& p_logic );                            \
    Logic* GetLogic( const std::string& p_logic );                          \
    bool HasLogic( const std::string& p_logic );                            \
    int DoAction( const Action& p_action );                                 \
    int DoAction( const std::string& p_act, entityid p_data1 = 0, entityid p_data2 = 0, entityid p_data3 = 0, entityid p_data4 = 0, const std::string& p_data = "" ); \
    int GetLogicAttribute( const std::string& p_logic, const std::string& p_attr ); \
    void AddHook( TimedAction* p_hook );                                    \
    void DelHook( TimedAction* p_hook );                                    \
    size_t Hooks();                                                         \
    void KillHook( const std::string& p_act, const std::string& p_stringdata ); \
    void ClearHooks();                                                      \
    void ClearLogicHooks( const std::string& p_logic );

#define HASCOMMANDSHEADERS                                                  \
    typedef std::list<Command*> commands;                                   \
    bool HasCommand( const std::string& p_command );                        \
    bool AddCommand( const std::string& p_command );                        \
    bool DelCommand( const std::string& p_command );                        \
    void BeginCommands();                                                   \
    std::string CurrentCommand();                                           \
    std::string CurrentCommandUsage();                                      \
    std::string CurrentCommandDescription();                                \
    void NextCommand();                                                     \
    bool IsValidCommand();                                                  \
    void SeekCommand( const std::string& p_name );                          \
    commands::iterator m_commanditr;


// ============================================================================
//  mixin implementations
// ============================================================================
#define HASREGIONIMPLEMENTATIONS( AC, PT )                                      \
entityid AC::Region()                           { return PT->Region(); }        \
void AC::SetRegion( entityid p_region )         { PT->SetRegion( p_region ); }

#define HASROOMIMPLEMENTATIONS( AC, PT )                                        \
entityid AC::Room()                             { return PT->Room(); }    \
void AC::SetRoom( entityid p_room )             { PT->SetRoom( p_room ); }

#define HASTEMPLATEIDIMPLEMENTATIONS( AC, PT )                                  \
entityid AC::TemplateID()                       { return PT->TemplateID(); }    \
void AC::SetTemplateID( entityid p_templateid ) { PT->SetTemplateID( p_templateid ); }


#define HASCHARACTERSIMPLEMENTATIONS( AC, PT )                                  \
void AC::AddCharacter( entityid p_id )          { PT->AddCharacter( p_id ); }   \
void AC::DelCharacter( entityid p_id )          { PT->DelCharacter( p_id ); }   \
size_t AC::Characters()                         { return PT->Characters(); }    \
void AC::BeginCharacter()                       { m_charitr = PT->CharactersBegin(); } \
entityid AC::CurrentCharacter()                 { return *m_charitr; }          \
void AC::NextCharacter()                        { ++m_charitr; }                \
bool AC::IsValidCharacter()                     { return m_charitr != PT->CharactersEnd(); }  \
void AC::SeekCharacter( const std::string& p_name )                             \
{                                                                               \
    m_charitr = match<character>( PT->CharactersBegin(), PT->CharactersEnd(), p_name );\
}

#define HASITEMSIMPLEMENTATIONS( AC, PT )                                       \
void AC::AddItem( entityid p_id )               { PT->AddItem( p_id ); }        \
void AC::DelItem( entityid p_id )               { PT->DelItem( p_id ); }        \
size_t AC::Items()                              { return PT->Items(); }         \
void AC::BeginItem()                            { m_itemitr = PT->ItemsBegin(); } \
entityid AC::CurrentItem()                      { return *m_itemitr; }          \
void AC::NextItem()                             { ++m_itemitr; }                \
bool AC::IsValidItem()                          { return m_itemitr != PT->ItemsEnd(); } \
void AC::SeekItem( const std::string& p_name )                                  \
{                                                                               \
    m_itemitr = match<item>( PT->ItemsBegin(), PT->ItemsEnd(), p_name );          \
}

#define HASROOMSIMPLEMENTATIONS( AC, PT )                                       \
void AC::AddRoom( entityid p_id )               { PT->AddRoom( p_id ); }        \
void AC::DelRoom( entityid p_id )               { PT->DelRoom( p_id ); }        \
size_t AC::Rooms()                              { return PT->Rooms(); }         \
void AC::BeginRoom()                            { m_roomitr = PT->RoomsBegin(); } \
entityid AC::CurrentRoom()                      { return *m_roomitr; }          \
void AC::NextRoom()                             { ++m_roomitr; }                \
bool AC::IsValidRoom()                          { return m_roomitr != PT->RoomsEnd(); } \
void AC::SeekRoom( const std::string& p_name )                                  \
{                                                                               \
    m_roomitr = match<room>( PT->RoomsBegin(), PT->RoomsEnd(), p_name );          \
}

#define HASPORTALSIMPLEMENTATIONS( AC, PT )                                     \
void AC::AddPortal( entityid p_id )               { PT->AddPortal( p_id ); }        \
void AC::DelPortal( entityid p_id )               { PT->DelPortal( p_id ); }        \
size_t AC::Portals()                              { return PT->Portals(); }         \
void AC::BeginPortal()                            { m_portalitr = PT->PortalsBegin(); } \
entityid AC::CurrentPortal()                      { return *m_portalitr; }          \
void AC::NextPortal()                             { ++m_portalitr; }                \
bool AC::IsValidPortal()                          { return m_portalitr != PT->PortalsEnd(); } \
void AC::SeekPortal( const std::string& p_name )                                    \
{                                                                                   \
    stringmatchfull matchfull( p_name );                                            \
    BeginPortal();                                                                  \
    while( IsValidPortal() )                                                        \
    {                                                                               \
        portal p( CurrentPortal() );                                                \
        p.SeekStartRoom( PT->ID() );                                                \
        if( matchfull( p.CurrentDirection() ) )                                     \
            return;                                                                 \
        NextPortal();                                                               \
    }                                                                               \
    stringmatchpart matchpart( p_name );                                            \
    BeginPortal();                                                                  \
    while( IsValidPortal() )                                                        \
    {                                                                               \
        portal p( CurrentPortal() );                                             \
        p.SeekStartRoom( PT->ID() );                                                \
        if( matchpart( p.CurrentDirection() ) )                                     \
            return;                                                                 \
        NextPortal();                                                               \
    }                                                                               \
}

#define HASDATABANKIMPLEMENTATIONS( AC, PT )                                \
int AC::GetAttribute( const std::string& p_name )                    { return PT->GetAttribute( p_name ); }         \
void AC::SetAttribute( const std::string& p_name, int p_val )        { PT->SetAttribute( p_name, p_val ); }         \
bool AC::HasAttribute( const std::string& p_name )                   { return PT->HasAttribute( p_name ); }         \
void AC::AddAttribute( const std::string& p_name, int p_initialval ) { PT->AddAttribute( p_name, p_initialval ); }  \
void AC::DelAttribute( const std::string& p_name )                   { PT->DelAttribute( p_name ); }

#define HASLOGICIMPLEMENTATIONS( AC, PT )                                   \
bool AC::AddLogic( const std::string& p_logic )         { return PT->AddLogic( p_logic ); }             \
bool AC::AddExistingLogic( Logic* p_logic )             { return PT->AddExistingLogic( p_logic ); }     \
bool AC::DelLogic( const std::string& p_logic )         { return PT->DelLogic( p_logic ); }             \
Logic* AC::GetLogic( const std::string& p_logic )       { return PT->GetLogic( p_logic ); }             \
bool AC::HasLogic( const std::string& p_logic )         { return PT->HasLogic( p_logic ); }             \
int AC::DoAction( const Action& p_action )              { return PT->DoAction( p_action ); }            \
int AC::DoAction( const std::string& p_act, entityid p_data1, entityid p_data2, entityid p_data3, entityid p_data4, const std::string& p_data )     { return PT->DoAction( Action( p_act, p_data1, p_data2, p_data3, p_data4, p_data ) ); }     \
int AC::GetLogicAttribute( const std::string& p_logic, const std::string& p_attr ) { return PT->GetLogicAttribute( p_logic, p_attr ); }     \
void AC::AddHook( TimedAction* p_hook )                 { PT->AddHook( p_hook ); }                      \
void AC::DelHook( TimedAction* p_hook )                 { PT->DelHook( p_hook ); }                      \
size_t AC::Hooks()                                      { return PT->Hooks(); }                         \
void AC::KillHook( const std::string& p_act, const std::string& p_stringdata ) { PT->KillHook( p_act, p_stringdata ); } \
void AC::ClearHooks()                                   { PT->ClearHooks(); }                           \
void AC::ClearLogicHooks( const std::string& p_logic )                  { PT->ClearLogicHooks( p_logic ); }

#define HASCOMMANDSIMPLEMENTAIONS( AC, PT )                         \
bool AC::AddCommand( const std::string& p_command ) { return PT->AddCommand( p_command ); }             \
bool AC::DelCommand( const std::string& p_command ) { return PT->DelCommand( p_command ); }             \
bool AC::HasCommand( const std::string& p_command ) { return PT->HasCommand( p_command ); }             \
void AC::BeginCommands()                            { m_commanditr = PT->CommandsBegin(); }             \
std::string AC::CurrentCommand()                    { return (*m_commanditr)->Name(); }                 \
std::string AC::CurrentCommandUsage()               { return (*m_commanditr)->Usage(); }                \
std::string AC::CurrentCommandDescription()         { return (*m_commanditr)->Description(); }          \
void AC::NextCommand()                              { ++m_commanditr; }                                 \
bool AC::IsValidCommand()                           { return m_commanditr != PT->CommandsEnd(); }       \
void AC::SeekCommand( const std::string& p_name )   { m_commanditr = PT->FindCommand( p_name ); }



#endif
