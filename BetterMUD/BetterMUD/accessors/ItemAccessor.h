// MUD Programming
// Ron Penton
// (C)2003
// ItemAccessor.h - This file contains the item accessor class
// 
// 


#ifndef BETTERMUDITEMACCESSOR_H
#define BETTERMUDITEMACCESSOR_H

#include <set>
#include <list>
#include "../entities/Entity.h"
#include "AccessorMacros.h"

namespace BetterMUD
{

// forward declaration
class Item;
class ItemTemplate;



class itemtemplate
{
public:

    ENTITYTEMPLATEHEADERS( itemtemplate );
    HASDATABANKHEADERS;

    bool IsQuantity();
    int GetQuantity();

protected:
    ItemTemplate* m_item;
    
};  // end class itemtemplate



// Accessor
class item
{
public:

    ENTITYHEADERS( item );
    HASROOMHEADERS;
    HASREGIONHEADERS;
    HASTEMPLATEIDHEADERS;
    HASDATABANKHEADERS;
    HASLOGICHEADERS;

    bool IsQuantity();
    int GetQuantity();
    void SetQuantity( int p_quantity );

protected:
    Item* m_item;
    
};  // end class item

}   // end namespace BetterMUD


#endif
