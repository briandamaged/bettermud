import string
import BetterMUD
import PythonCommand


class visual( PythonCommand.Command ):
    name = "visual"
    usage = "\"visual <vision>\""
    description = "shows some text in a room"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError
        me = BetterMUD.character( self.me )
        self.mud.AddActionAbsolute( 0, "vision", me.Room(), 0, 0, 0, args )


class addcommand( PythonCommand.Command ):
    name = "addcommand"
    usage = "\"addcommand <player> <commandname>\""
    description = "This gives a character the ability to use a new command."

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError
        parms = args.split( None, 1 )
        if len(parms) < 2: raise PythonCommand.UsageError
        me = BetterMUD.character( self.me )
        id = self.mud.FindPlayerPart( parms[0] )
        if not id:
            me.DoAction( "error", 0, 0, 0, 0, "Cannot find player: " + parms[0] )
            return
        r = BetterMUD.character( id )
        if not r.AddCommand( parms[1] ):
            me.DoAction( "error", 0, 0, 0, 0, "Could not add command: " + parms[1] )
            return
        me.DoAction( "announce", 0, 0, 0, 0, "Successfully gave " + r.Name() + " command " + parms[1] + "." )
        r.DoAction( "announce", 0, 0, 0, 0, me.Name() + " gave you a new command: " + parms[1] + "!" )


class delcommand( PythonCommand.Command ):
    name = "delcommand"
    usage = "\"delcommand <player> <commandname>\""
    description = "This removes a command from a character."

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError
        parms = args.split( None, 1 )
        if len(parms) < 2: raise PythonCommand.UsageError
        me = BetterMUD.character( self.me )
        id = self.mud.FindPlayerPart( parms[0] )
        if not id:
            me.DoAction( "error", 0, 0, 0, 0, "Cannot find player: " + parms[0] )
            return
        t = BetterMUD.character( id )
        if not t.DelCommand( parms[1] ):
            me.DoAction( "error", 0, 0, 0, 0, "Could not delete command: " + parms[1] )
            return
        me.DoAction( "announce", 0, 0, 0, 0, "Successfully removed " + t.Name() + "s command " + parms[1] + "." )
        t.DoAction( "announce", 0, 0, 0, 0, me.Name() + " deleted your command: " + parms[1] + "!" )


class emulate( PythonCommand.Command ):
    name = "emulate"
    usage = "\"emulate <player> <text>\""
    description = "This tells the game to pretend that <player> typed in <text>"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError
        parms = args.split( None, 1 )
        if len(parms) < 2: raise PythonCommand.UsageError
        me = BetterMUD.character( self.me )
        id = self.mud.FindPlayerOnlinePart( parms[0] )
        if not id:
            me.DoAction( "error", 0, 0, 0, 0, "Cannot find player: " + parms[0] )
            return
        c = BetterMUD.character( id )
        self.mud.AddActionAbsolute( 0, "command", c.ID(), 0, 0, 0, parms[1] )


class addplayerlogic( PythonCommand.Command ):
    name = "addplayerlogic"
    usage = "\"addplayerlogic <player> <logicname>\""
    description = "This adds a logic module to a player."

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError
        parms = args.split( None, 1 )
        if len(parms) < 2: raise PythonCommand.UsageError
        me = BetterMUD.character( self.me )
        id = self.mud.FindPlayerPart( parms[0] )
        if not id:
            me.DoAction( "error", 0, 0, 0, 0, "Cannot find player: " + parms[0] )
            return
        c = BetterMUD.character( id )
        if not c.AddLogic( parms[1] ):
            me.DoAction( "error", 0, 0, 0, 0, "Could not add logic: " + parms[1] )
            return
        me.DoAction( "announce", 0, 0, 0, 0, "Successfully gave " + c.Name() + " logic module " + parms[1] + "." )
        c.DoAction( "announce", 0, 0, 0, 0, me.Name() + " gave you a new logic module: " + parms[1] + "!" )


class delplayerlogic( PythonCommand.Command ):
    name = "delplayerlogic"
    usage = "\"delplayerlogic <player> <logicname>\""
    description = "This removes a logic module from a player"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError
        parms = args.split( None, 1 )
        if len(parms) < 2: raise PythonCommand.UsageError
        id = self.mud.FindPlayerPart( parms[0] )
        me = BetterMUD.character( self.me )

        if not id:
            me.DoAction( "error", 0, 0, 0, 0, "Cannot find player: " + parms[0] )
            return
        c = BetterMUD.character( id )
        if not c.DelLogic( parms[1] ):
            me.DoAction( "error", 0, 0, 0, 0, "Could not delete logic: " + parms[1] )
            return
        me.DoAction( "announce", 0, 0, 0, 0, "Successfully removed " + c.Name() + "s logic module " + parms[1] + "." )
        c.DoAction( "announce", 0, 0, 0, 0, me.Name() + " deleted your logic module: " + parms[1] + "!" )


class pythonexec( PythonCommand.Command ):
    name = "pythonexec"
    usage = "\"pythonexec <code>\""
    description = "Executes some Python code"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError
        me = BetterMUD.character( self.me )
        s = string.replace( args, "<br>", "\n" )
        me.DoAction( "announce", 0, 0, 0, 0, "Executing Python Code, check your console window." )
        exec( s )


class spawnitem( PythonCommand.Command ):
    name = "spawnitem"
    usage = "\"spawnitem <item template id>\""
    description = "Spawns a new item in your inventory"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError

        me = BetterMUD.character( self.me )
        t = BetterMUD.itemtemplate( int( args ) )
        print t.ID()
        me.DoAction( "announce", 0, 0, 0, 0, "Spawning Item..." )
        self.mud.DoAction( "spawnitem", t.ID(), me.ID(), 1, 0, "" )
        me.DoAction( "announce", 0, 0, 0, 0, "Success." )


class spawncharacter( PythonCommand.Command ):
    name = "spawncharacter"
    usage = "\"spawncharacter <character template id>\""
    description = "Spawns a new character in your room"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError
        me = BetterMUD.character( self.me )
        t = BetterMUD.charactertemplate( int( args ) )
        me.DoAction( "announce", 0, 0, 0, 0, "Spawning Character..." )
        self.mud.DoAction( "spawncharacter", t.ID(), me.Room(), 0, 0, "" )
        me.DoAction( "announce", 0, 0, 0, 0, "Success." )


class teleport( PythonCommand.Command ):
    name = "teleport"
    usage = "\"teleport <room id>\""
    description = "Attempts to teleport you to a room"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError
        me = BetterMUD.character( self.me )
        oldroom = me.Room()
        self.mud.DoAction( "attempttransport", me.ID(), int(args), 0, 0, "" )


class destroyitem( PythonCommand.Command ):
    name = "destroyitem"
    usage = "\"destroyitem <item>\""
    description = "This destroys an item, searching your inventory first, then the room."

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError

        me = BetterMUD.character( self.me )
        me.SeekItem( args )

        if me.IsValidItem():
            item = me.CurrentItem()
        else:
            room = BetterMUD.room( me.Room() )
            room.SeekItem( args )
            if room.IsValidItem():
                item = room.CurrentItem()
            else:
                me.DoAction( "error", 0, 0, 0, 0, "Cannot find item: " + args )
                return

        i = BetterMUD.item( item )
        me.DoAction( "announce", 0, 0, 0, 0, "Destroying Item: " + i.Name() )
        self.mud.AddActionAbsolute( 0, "destroyitem", item, 0, 0, 0, "" )


class destroycharacter( PythonCommand.Command ):
    name = "destroycharacter"
    usage = "\"destroycharacter <item>\""
    description = "This destroys a character."

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError

        me = BetterMUD.character( self.me )
        room = BetterMUD.room( me.Room() )
        room.SeekCharacter( args )
        if room.IsValidCharacter():
            character = room.CurrentCharacter()
        else:
            me.DoAction( "error", 0, 0, 0, 0, "Cannot find character: " + args )
            return

        c = BetterMUD.character( character )
        me.DoAction( "announce", 0, 0, 0, 0, "Destroying Character: " + c.Name() )
        self.mud.AddActionAbsolute( 0, "destroycharacter", character, 0, 0, 0, "" )


class cleanup( PythonCommand.Command ):
    name = "cleanup"
    usage = "\"cleanup\""
    description = "Performs a manual database cleanup"

    def Run( self, args ):
        me = BetterMUD.character( self.me )
        me.DoAction( "announce", 0, 0, 0, 0, "Beginning Cleanup" )
        self.mud.AddActionAbsolute( 0, "cleanup", 0, 0, 0, 0, "" )



class savedatabase( PythonCommand.Command ):
    name = "savedatabase"
    usage = "\"savedatabase <all|region|players> <|regionid>\""
    description = "Performs a manual database save"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError

        me = BetterMUD.character( self.me )
        parms = args.split( None, 1 )
        if parms[0] == "all":
            me.DoAction( "announce", 0, 0, 0, 0, "Beginning Complete Database Save" )
            self.mud.AddActionAbsolute( 0, "savedatabases", 0, 0, 0, 0, "" )
            return
        if parms[0] == "region":
            if len(parms) < 2: raise PythonCommand.UsageError
            region = BetterMUD.region( int(parms[1]) )
            me.DoAction( "announce", 0, 0, 0, 0, "Beginning Region Database Save: " + region.Name() )
            self.mud.AddActionAbsolute( 0, "saveregion", int(parms[1]), 0, 0, 0, "" )
            return
        if parms[0] == "players":
            me.DoAction( "announce", 0, 0, 0, 0, "Beginning Player Database Save" )
            self.mud.AddActionAbsolute( 0, "saveplayers", 0, 0, 0, 0, "" )
            return
        raise PythonCommand.UsageError



class loaddatabase( PythonCommand.Command ):
    name = "loaddatabase"
    usage = "\"loaddatabase <items|characters|regions|commands|logics> <file name> <|keepdata|keepall>\""
    description = "Performs a manual database save"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError

        me = BetterMUD.character( self.me )
        parms = args.split( None )
        if len(parms) < 2: raise PythonCommand.UsageError

        if parms[0] == "items":
            me.DoAction( "announce", 0, 0, 0, 0, "Beginning Item Template Database Load: " + parms[1] )
            self.mud.DoAction( "reloaditems", 0, 0, 0, 0, parms[1] )
            return
        if parms[0] == "characters":
            me.DoAction( "announce", 0, 0, 0, 0, "Beginning Character Template Database Load: " + parms[1] )
            self.mud.DoAction( "reloadcharacters", 0, 0, 0, 0, parms[1] )
            return
        if parms[0] == "regions":
            me.DoAction( "announce", 0, 0, 0, 0, "Beginning Region Database Load: " + parms[1] )
            self.mud.DoAction( "reloadregion", 0, 0, 0, 0, parms[1] )
            return
        if parms[0] == "commands":
            if len(parms) < 3: raise PythonCommand.UsageError
            if parms[2] == "keepdata" : mode = 1
            elif parms[2] == "keepall" : mode = 0
            else : raise UsageError
            me.DoAction( "announce", mode, 0, 0, 0, "Beginning Command Database Load: " + parms[1] )
            self.mud.DoAction( "reloadcommandscript", mode, 0, 0, 0, parms[1] )
            return
        if parms[0] == "logics":
            if len(parms) < 3: raise PythonCommand.UsageError
            if parms[2] == "keepdata" : mode = 1
            elif parms[2] == "keepall" : mode = 0
            else : raise UsageError
            me.DoAction( "announce", 0, 0, 0, 0, "Beginning Logic Database Load: " + parms[1] )
            self.mud.DoAction( "reloadlogicscript", mode, 0, 0, 0, parms[1] )
            return


        raise PythonCommand.UsageError



class initialize( PythonCommand.Command ):
    name = "initialize"
    usage = "\"initialize <script>\""
    description = "Performs an initialization using a script"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError
        exec( "import data.logics.initializers." + args + "\nreload( data.logics.initializers." + args + " )\ndata.logics.initializers." + args + ".init()" )