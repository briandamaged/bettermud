// MUD Programming
// Ron Penton
// (C)2003
// LogicCollection.h - This file contains a collection of logic modules, 
//                     accessible by name.
// 
// 


#ifndef BETTERMUDLOGICCOLLECTION_H
#define BETTERMUDLOGICCOLLECTION_H

#include "Logic.h"
#include "../entities/Attributes.h"

namespace BetterMUD
{


class LogicCollection
{
public:

    typedef Databank<Logic*> bank;
    typedef bank::iterator iterator;

    iterator begin()        { return m_collection.begin(); }
    iterator end()          { return m_collection.end(); }

    LogicCollection() {};
    ~LogicCollection();

    Logic* Get( const std::string& p_name );
    void AddExisting( Logic* l );
    void Add( const std::string& p_name, entityid p_id );
    void Del( const std::string& p_name );
    bool Has( const std::string& p_name );
    int Attribute( const std::string& p_module, const std::string& p_attr );
    int DoAction( const Action& p_action );

    void Load( std::istream& p_stream, entityid p_id );
    void Save( std::ostream& p_stream );

    LogicCollection& operator=( const LogicCollection& );
    LogicCollection( const LogicCollection& );

protected:
    bank m_collection;
};  // end class LogicCollection

}   // end namespace BetterMUD


#endif
