// MUD Programming
// Ron Penton
// (C)2003
// BetterMUD.h - The Main Module of BetterMUD.
// 
// 



#include <iostream>

#include "SocketLib/SocketLib.h"
#include "BetterMUD/network/TelnetLogon.h"
#include "BetterMUD/network/BetterTelnet.h"
#include "BetterMUD/Game.h"
#include "BetterMUD/Exception.h"
#include "BetterMUD/databases/AllDatabases.h"

using namespace SocketLib;
using namespace BetterMUD;
using namespace std;

int main()
{
    try
    {
      
    ListeningManager<BetterTelnet, TelnetLogon> telnetlistener;
    ConnectionManager<BetterTelnet, TelnetLogon> telnetconnectionmanager( 128, 60, 65536 );

    telnetlistener.SetConnectionManager( &telnetconnectionmanager );
    telnetlistener.AddPort( 5110 );

    g_game.LoadAll();


    while( g_game.Running() )
    {
        telnetlistener.Listen();
        telnetconnectionmanager.Manage();
        g_game.ExecuteLoop();
        ThreadLib::YieldThread();

        
    }

    }

    catch( BetterMUD::Exception& e )
    {
        PyErr_Print();          // print python errors
        std::cout << e.GetError();
    }
    catch( std::exception& e )
    {
        // catch standard errors
    }
    catch( ... )
    {
        // catch all other errors
    }

    g_game.SaveAll();

    CharacterDB.Purge();
    ItemDB.Purge();
    AccountDB.Purge();
    RoomDB.Purge();
    PortalDB.Purge();
    RegionDB.Purge();

    return 0;
}



