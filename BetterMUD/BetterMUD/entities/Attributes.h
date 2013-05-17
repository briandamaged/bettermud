// MUD Programming
// Ron Penton
// (C)2003
// Attributes.h - This file contains the character attribute classes
//                and enumerations.
// 
// 


#ifndef BETTERMUDATTRIBUTES_H
#define BETTERMUDATTRIBUTES_H

#include <map>
#include "BasicLib/BasicLib.h"
#include "../Exception.h"

namespace BetterMUD
{

enum accesslevel
{
    Peon,
    Builder,
    God,
    Admin
};

const std::string ACCESSLEVELSTRINGS[] = 
{
    "Peon",
    "Builder",
    "God",
    "Admin" 
};

const int AccessLevels = 4;





template< typename type >
class Databank
{
public:
    typedef          std::map< std::string, type > container;
    typedef typename container::iterator           iterator;


    iterator begin()     { return m_bank.begin(); }
    iterator end()       { return m_bank.end(); }

    bool Has( const std::string& p_name )
    {
        return m_bank.find( p_name ) != m_bank.end();
    }

    void Set( const std::string& p_name, const type& p_val )
    {
        iterator itr = m_bank.find( p_name );
        if( itr == m_bank.end() )
            throw Exception( "INVALID DATABANK ATTRIBUTE: " + p_name );

        itr->second = p_val;
    }

    type& Get( const std::string& p_name )
    {
        iterator itr = m_bank.find( p_name );
        if( itr == m_bank.end() )
            throw Exception( "INVALID DATABANK ATTRIBUTE: " + p_name );

        return itr->second;
    }

    void Add( const std::string& p_name, const type& p_val )
    {
        m_bank[p_name] = p_val;
    }

    void Del( const std::string& p_name )
    {
        m_bank.erase( p_name );
    }

    void Save( std::ostream& p_stream )
    {
        p_stream << "[DATABANK]\n";
        
        iterator itr = m_bank.begin();
        while( itr != m_bank.end() )
        {
            p_stream << BasicLib::tostring( itr->first, 24 ) << 
                itr->second << "\n";
            ++itr;
        }

        p_stream << "[/DATABANK]\n";
    }


    void Load( std::istream& p_stream )
    {
        std::string temp;
        p_stream >> temp;       // extract "[DATABANK]"
        
        while( BasicLib::extract( p_stream, temp ) != "[/DATABANK]" )
        {
            type t;
            p_stream >> t;
            Add( temp, t );
        }
    }


    void Clear() { m_bank.clear(); }
    size_t size() { return m_bank.size(); }


protected:
    container m_bank;
};














}   // end namespace BetterMUD









namespace BasicLib
{
    using namespace BetterMUD;

    template<>
    inline void insert<accesslevel>( std::ostream& s, const accesslevel& n )
    {
        s << ACCESSLEVELSTRINGS[n];
    }

    template<>
    inline accesslevel& extract<accesslevel>( std::istream& s, accesslevel& n )
    {
        std::string str;
        s >> str;
        str = BasicLib::LowerCase( str );

        for( int i = 0; i < AccessLevels; i++ )
        {
            if( str == BasicLib::LowerCase( ACCESSLEVELSTRINGS[i] ) )
                n = (accesslevel)i;
            break;
        }
        
        return n;
    }


}   // end namespace BasicLib


#endif
