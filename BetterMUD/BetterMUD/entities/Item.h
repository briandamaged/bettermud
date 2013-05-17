// MUD Programming
// Ron Penton
// (C)2003
// Item.h - This file contains the item entity type
// 
// 


#ifndef BETTERMUDITEM_H
#define BETTERMUDITEM_H

#include <string>
#include <list>
#include "BasicLib/BasicLib.h"
#include "Entity.h"
#include "LogicEntity.h"
#include "DataEntity.h"

namespace BetterMUD
{


// ============================================================================
//  Item Template Class
// ============================================================================
class ItemTemplate : 
    public Entity,
    public DataEntity
{
friend class Item;
public:
    typedef std::list< std::string > names;

    void Load( std::istream& p_stream );

    bool IsQuantity()                   { return m_isquantity; }
    int GetQuantity()                   { return m_quantity; }

protected:
    bool m_isquantity;          // is this a quantity object?
    int m_quantity;             // if so, what is the quantity?
    names m_logics;
};



// ============================================================================
//  Item Instance Class
// ============================================================================
class Item : 
    public LogicEntity, 
    public DataEntity,
    public HasRoom,
    public HasRegion,
    public HasTemplateID
{
public:

    Item();
    std::string Name();
    void Load( std::istream& p_stream );
    void Save( std::ostream& p_stream );
    void LoadTemplate( const ItemTemplate& p_template );
    
    bool IsQuantity()                   { return m_isquantity; }
    int GetQuantity()                   { return m_quantity; }
    void SetQuantity( int p_quantity )  { m_quantity = p_quantity; }

    // functions to add and remove an item "from the game"
    void Add();
    void Remove();
protected:

    bool m_isquantity;          // is this a quantity object?
    int m_quantity;             // if so, what is the quantity?


};  // end class Item

}   // end namespace BetterMUD


#endif
