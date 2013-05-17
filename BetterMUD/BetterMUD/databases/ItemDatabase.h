// MUD Programming
// Ron Penton
// (C)2003
// ItemDatabase.h - This file contains the item entity database
// 
// 


#ifndef BETTERMUDITEMDATABASE_H
#define BETTERMUDITEMDATABASE_H

#include "Databases.h"
#include "../entities/Item.h"


namespace BetterMUD
{

class ItemDatabase : public TemplateInstanceDatabase<Item, ItemTemplate>
{
public:
    void LoadTemplates();
    void LoadTemplates( const std::string& p_file );
};



extern ItemDatabase ItemDB;

}   // end namespace BetterMUD


#endif
