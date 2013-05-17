// MUD Programming
// Ron Penton
// (C)2003
// AccountDatabase.h - This file contains the account entity database
// 
// 


#ifndef BETTERMUDACCOUNTDATABASE_H
#define BETTERMUDACCOUNTDATABASE_H

#include "Databases.h"
#include "../entities/Account.h"
#include "../entities/Entity.h"


namespace BetterMUD
{

class AccountDatabase : public MapDatabase<Account>
{
public:

    entityid Create( 
        const std::string& p_name,          // name
        const std::string& p_pass );        // password

    void Load();
    void Save();
    bool AcceptibleName( const std::string& p_name );
};

extern AccountDatabase AccountDB;

}   // end namespace BetterMUD


#endif
