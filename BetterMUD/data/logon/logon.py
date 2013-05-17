import BetterMUD

def listchars():
    s =  "<#FFFFFF>--------------------------------------------------------------------------------\r\n"
    s += "<#00FF00> Please Choose a Race For Your Character:\r\n"
    s += "<#FFFFFF>--------------------------------------------------------------------------------\r\n"
    s += "<$reset> 0 - Go Back\r\n"
    s += "<$reset> 1 - Human\r\n"
    s += "<$reset> 2 - Elf\r\n"
    s += "<#FFFFFF>--------------------------------------------------------------------------------\r\n"
    s += "<#FFFFFF> Enter Choice: <$reset>"
    return s

def gettemplateid( option ):
    if option == 1: return 1
    if option == 2: return 2
    return 0


def setup( id ):
    c = BetterMUD.character( id )
    a = BetterMUD.account( c.GetAccount() )
    l = a.AccessLevel();



    if( l >= 0 ):
        c.AddCommand( "north" )
        c.AddCommand( "east" )
        c.AddCommand( "south" )
        c.AddCommand( "west" )
        c.AddCommand( "northeast" )
        c.AddCommand( "northwest" )
        c.AddCommand( "southeast" )
        c.AddCommand( "southwest" )
        c.AddCommand( "up" )
        c.AddCommand( "down" )
        c.AddCommand( "ne" )
        c.AddCommand( "nw" )
        c.AddCommand( "se" )
        c.AddCommand( "sw" )
        c.AddCommand( "get" )
        c.AddCommand( "give" )
        c.AddCommand( "drop" )
        c.AddCommand( "go" )
        c.AddCommand( "commands" )
        c.AddCommand( "look" )
        c.AddCommand( "quit" )
        c.AddCommand( "action" )
        c.AddCommand( "chat" )
        c.AddCommand( "say" )
        c.AddCommand( "quiet" )
        c.AddCommand( "receive" )
        c.AddCommand( "pies" )
        c.AddCommand( "inventory" )
        c.AddCommand( "arm" )
        c.AddCommand( "disarm" )
        c.AddCommand( "read" )
        c.AddCommand( "attack" )
        c.AddCommand( "breakattack" )

    if( l >= 2 ):
        c.AddCommand( "kick" )
        c.AddCommand( "announce" )

    if( l >= 3 ):
        c.AddCommand( "emulate" )
        c.AddCommand( "shutdown" )
        c.AddCommand( "addcommand" )
        c.AddCommand( "delcommand" )
        c.AddCommand( "addplayerlogic" )
        c.AddCommand( "delplayerlogic" )
        c.AddCommand( "reloadscript" )
        c.AddCommand( "pythonexec" )
        c.AddCommand( "spawnitem" )
        c.AddCommand( "spawncharacter" )
        c.AddCommand( "destroyitem" )
        c.AddCommand( "destroyitem" )
        c.AddCommand( "visual" )
        c.AddCommand( "loaddatabase" )
        c.AddCommand( "savedatabase" )


    c.SetRoom( 1 )
    c.SetRegion( 1 )



                                