// MUD Programming
// Ron Penton
// (C)2003
// DataEntity.h - This file contains the DataEntity class, which is an 
//                entity class that contains a databank
// 
// 


#ifndef BETTERMUDDATAENTITY_H
#define BETTERMUDDATAENTITY_H

#include "Entity.h"

namespace BetterMUD
{

class DataEntity
{
public:
    int GetAttribute( const std::string& p_name )
    {
        return m_attributes.Get( p_name );
    }

    void SetAttribute( const std::string& p_name, int p_val )
    {
        m_attributes.Set( p_name, p_val );
    }
    
    bool HasAttribute( const std::string& p_name )
    {
        return m_attributes.Has( p_name );
    }

    void AddAttribute( const std::string& p_name, int p_initialval )
    {
        m_attributes.Add( p_name, p_initialval );
    }

    void DelAttribute( const std::string& p_name )
    {
        m_attributes.Del( p_name );
    }
protected:
    Databank<int> m_attributes;
};  // end class DataEntity



}   // end namespace BetterMUD


#endif
