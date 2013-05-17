// MUD Programming
// Ron Penton
// (C)2003
// Account.cpp - This file contains the account entity type
// 
// 


#include "Account.h"
#include "../accessors/Accessors.h"

namespace BetterMUD
{


void Account::Load( std::istream& p_stream )
{
    std::string temp;
    p_stream >> temp >> m_name;
    p_stream >> temp >> m_password;
    p_stream >> temp; BasicLib::extract( p_stream, m_logintime );
    p_stream >> temp; BasicLib::extract( p_stream, m_accesslevel );
    p_stream >> temp >> m_allowedcharacters;
    p_stream >> temp >> m_banned;


    p_stream >> temp;
    m_characters.clear();
    entityid c;
    while( BasicLib::extract( p_stream, c ) != 0 )
        m_characters.insert( c );
}

void Account::Save( std::ostream& p_stream )
{
    p_stream << "[NAME]                  " << m_name << "\n";
    p_stream << "[PASS]                  " << m_password << "\n";
    p_stream << "[FIRSTLOGINTIME]        "; BasicLib::insert( p_stream, m_logintime ); p_stream << "\n";
    p_stream << "[ACCESSLEVEL]           "; BasicLib::insert( p_stream, m_accesslevel ); p_stream << "\n";
    p_stream << "[ALLOWEDCHARS]          " << m_allowedcharacters << "\n";
    p_stream << "[BANNED]                " << m_banned << "\n";


    p_stream << "[CHARACTERS]            ";
    characters::iterator itr = m_characters.begin();
    while( itr != m_characters.end() )
    {
        p_stream << *itr << " ";
        ++itr;
    }

    p_stream << "0\n";
}


}   // end namespace BetterMUD

