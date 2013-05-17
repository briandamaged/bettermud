// MUD Programming
// Ron Penton
// (C)2003
// Entity.h - This file contains all types and functions related to
//            entities in BetterMUD
// 
// 


#ifndef BETTERMUDENTITY_H
#define BETTERMUDENTITY_H

#include <string>
#include <set>
#include "BasicLib/BasicLib.h"

namespace BetterMUD
{

// --------------------------------------------------------------------
//  Define the entityid datatype as 32 bits, allowing a range of 
//  ~2 billion entities. <=0 is always invalid.
// --------------------------------------------------------------------
typedef signed int entityid;
typedef signed int status;
const entityid maxentityvalue = 0x7FFFFFFF;




// -------------------------------------------------------------------
//  This is the entity class, just has a name and an ID
// -------------------------------------------------------------------
class Entity
{
public:
    Entity() :
      m_name( "UNDEFINED" ),
      m_description( "UNDEFINED" ),
      m_id( 0 ),
      m_refcount( 0 ) {}

      
    std::string Name() const        { return m_name; }
    std::string Description() const { return m_description; }
    entityid ID() const          { return m_id; }
    void AddRef()                   { m_refcount++; }
    void DelRef()                   { m_refcount--; }

    int Ref() const                 { return m_refcount; }

    void SetName( const std::string& p_name )       { m_name = p_name; }
    void SetDescription( const std::string& p_desc ){ m_description = p_desc; }
    void SetID( entityid p_id )                     { m_id = p_id; }

protected:
    entityid m_id;
    std::string m_name;
    std::string m_description;
    int m_refcount;
};


class HasRegion
{
public:
    HasRegion() : m_region( 0 ) {}
    entityid Region() const             { return m_region; }
    void SetRegion( entityid p_region ) { m_region = p_region; }
protected:
    entityid m_region;
};

class HasRoom
{
public:
    HasRoom() : m_room( 0 ) {}
    entityid Room() const           { return m_room; }
    void SetRoom( entityid p_room ) { m_room = p_room; }
protected:
    entityid m_room;
};

class HasTemplateID
{
public:
    HasTemplateID() : m_templateid( 0 ) {}
    entityid TemplateID() const                 { return m_templateid; }
    void SetTemplateID( entityid p_templateid ) { m_templateid = p_templateid; }
protected:
    entityid m_templateid;
};


class HasCharacters
{
public:
    typedef std::set<entityid> characters;
    typedef characters::iterator charitr;
    void AddCharacter( entityid p_id )      { m_characters.insert( p_id ); }
    void DelCharacter( entityid p_id )      { m_characters.erase( p_id ); }
    charitr CharactersBegin()               { return m_characters.begin(); }
    charitr CharactersEnd()                 { return m_characters.end(); }
    size_t Characters()                     { return m_characters.size(); }
protected:
    characters m_characters;
};

class HasItems
{
public:
    typedef std::set<entityid> items;
    typedef items::iterator itemitr;
    void AddItem( entityid p_id )           { m_items.insert( p_id ); }
    void DelItem( entityid p_id )           { m_items.erase( p_id ); }
    itemitr ItemsBegin()                    { return m_items.begin(); }
    itemitr ItemsEnd()                      { return m_items.end(); }
    size_t Items()                          { return m_items.size(); }
protected:
    items m_items;
};

class HasRooms
{
public:
    typedef std::set<entityid> rooms;
    typedef rooms::iterator roomitr;
    void AddRoom( entityid p_id )           { m_rooms.insert( p_id ); }
    void DelRoom( entityid p_id )           { m_rooms.erase( p_id ); }
    roomitr RoomsBegin()                    { return m_rooms.begin(); }
    roomitr RoomsEnd()                      { return m_rooms.end(); }
    size_t Rooms()                          { return m_rooms.size(); }
protected:
    rooms m_rooms;
};


class HasPortals
{
public:
    typedef std::set<entityid> portals;
    typedef portals::iterator portalitr;
    void AddPortal( entityid p_id )           { m_portals.insert( p_id ); }
    void DelPortal( entityid p_id )           { m_portals.erase( p_id ); }
    portalitr PortalsBegin()                  { return m_portals.begin(); }
    portalitr PortalsEnd()                    { return m_portals.end(); }
    size_t Portals()                          { return m_portals.size(); }
protected:
    portals m_portals;
};



// --------------------------------------------------------------------
//  String comparison functors
// --------------------------------------------------------------------

struct stringmatchfull
{ 
    // create the matcher with the search string, and lowercase it
    // to increase efficiency.
    stringmatchfull( const std::string& p_str )
        : search( BasicLib::LowerCase( p_str ) ) 
    { /* do nothing */ }

    // the matching function; utilizes string::operator== for a full match
    bool operator() ( const std::string& p_name )
    {
        return search == BasicLib::LowerCase( p_name );
    }

    std::string search;
};

struct stringmatchpart
{
    // create the matcher with the search string, and lowercase it
    // to increase efficiency.
    stringmatchpart( const std::string& p_str )
        : search( BasicLib::LowerCase( p_str ) ) 
    { /* do nothing */ }

    // the matching function. This matches on
    //    a) empty search strings
    //    b) partial matches at the start of the string
    //    c) partial matches of any word in the string
    bool operator() ( const std::string& p_name )
    {
        // match on empty strings
        if( search.size() == 0 )
            return true;

        // grab the comparison name
        std::string name = BasicLib::LowerCase( p_name );

        // find the position of the first match
        size_t pos = name.find( search );

        // perform 0 or more passes if needed.
        // for example, if the user types "st" when searching a "rusty stake",
        // only one pass would find the 'st' in "rusty", and determine that
        // there is no match because "st" is in the middle of a string.
        // A second pass is needed to find the "st" in "stake".
        while( pos != std::string::npos )
        {
            // match found at beginning, or match found at beginning of a word, 
            // therefore, return true.
            if( pos == 0 || name[pos-1] == ' ' )
                return true;

            // perform another search, starting at where the last one left off
            pos = name.find( search, pos + 1 );
        }

        // no matches
        return false;
    }

    std::string search;
};


// ====================================================================
//  Entity searching functions
// ====================================================================


// --------------------------------------------------------------------
// One-pass accessor-based matching
// --------------------------------------------------------------------
template< typename accessor, typename iterator, typename functor >
iterator matchonepass( iterator begin, iterator end, functor matches )
{
    // begin looping
    while( begin != end )
    {
        // create an accessor pointing to the object
        // (*begin is an entityid/pointer)
        accessor a( *begin );

        // try matching the name
        if( matches( a.Name() ) )
            return begin;

        // no match, go to next
        ++begin;
    }

    // no matches at all, return end iterator
    return end;
}

// --------------------------------------------------------------------
// Two-pass accessor-based matching
// --------------------------------------------------------------------
template< typename accessor, typename iterator, typename functor1, typename functor2 >
iterator matchtwopass( iterator begin, iterator end, functor1 matches1, functor2 matches2 )
{
    iterator itr = 
        matchonepass< accessor, iterator, functor1 >( begin, end, matches1 );
    if( itr == end )
        itr = 
        matchonepass< accessor, iterator, functor2 >( begin, end, matches2 );
    
    return itr;
}


// --------------------------------------------------------------------
// Helper function that performs a two-pass string match on a container
// of entityid's, using accessor lookups.
// --------------------------------------------------------------------
template< typename accessor, typename iterator >
iterator match( iterator begin, iterator end, const std::string& search )
{
    return matchtwopass< accessor, iterator, stringmatchfull,
                         stringmatchpart >
        ( begin, end,
          stringmatchfull( search ),
          stringmatchpart( search ) );
}



// this defines a portal entry
struct portalentry
{
    entityid startroom;             // starting room
    std::string directionname;      // name of the direction used to enter portal
    entityid destinationroom;       // ending room

    void Load( std::istream& p_stream );
    void Save( std::ostream& p_stream );
};



}   // end namespace BetterMUD


#endif
