// MUD Programming
// Ron Penton
// (C)2003
// ItemAccessor.cpp - This file contains the item accessor class
// 
// 


#include "../databases/ItemDatabase.h"
#include "ItemAccessor.h"

namespace BetterMUD
{

ENTITYTEMPLATEIMPLEMENTATIONS( itemtemplate, m_item, ItemDB );
HASDATABANKIMPLEMENTATIONS( itemtemplate, m_item );

bool itemtemplate::IsQuantity()         { return m_item->IsQuantity(); }
int itemtemplate::GetQuantity()         { return m_item->GetQuantity(); }


ENTITYIMPLEMENTATIONS( item, m_item, ItemDB );
HASROOMIMPLEMENTATIONS( item, m_item );
HASREGIONIMPLEMENTATIONS( item, m_item );
HASTEMPLATEIDIMPLEMENTATIONS( item, m_item );
HASLOGICIMPLEMENTATIONS( item, m_item );
HASDATABANKIMPLEMENTATIONS( item, m_item );


bool item::IsQuantity()                     { return m_item->IsQuantity(); }
int item::GetQuantity()                     { return m_item->GetQuantity(); }
void item::SetQuantity( int p_quantity )    { m_item->SetQuantity( p_quantity ); }

}   // end namespace BetterMUD
