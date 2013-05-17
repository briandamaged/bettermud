import string
import BetterMUD
import PythonCommand

FindTarget = PythonCommand.FindTarget

class superglue( PythonCommand.Command ):
    name = "superglue"
    usage = "\"superglue <character>\""
    description = "superglues someone to the floor"
    def Run( self, args ):
        if not args: raise PythonCommand.UsageError

        me = BetterMUD.character( self.me )
        r = BetterMUD.room( me.Room() )

        # find the name:
        id = FindTarget( r.SeekCharacter, r.IsValidCharacter, r.CurrentCharacter, args )
        c = BetterMUD.character( id )
        name = c.Name()

        self.mud.AddActionAbsolute( 0, "addlogic", 0, id, 0, 0, "superglue" )
        self.mud.AddActionAbsolute( 0, "vision", r.ID(), 0, 0, 0, "<#FF0000>OMG!!! " + me.Name() + " just SUPERGLUED " + name + " to the floor!!!!!" )
        self.mud.AddActionRelative( 20000, "messagelogic", 0, id, 0, 0, "superglue remove" )



class uberweight( PythonCommand.Command ):
    name = "uberweight"
    usage = "\"uberweight <item>\""
    description = "puts a magical weight on an item"
    def ScriptInit( self ):
        # init the next execution time to 0, so you can execute it right away
        self.executiontime = 0

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError

        me = BetterMUD.character( self.me )
        r = BetterMUD.room( me.Room() )

        time = self.mud.GetTime()
        if time < self.executiontime:
            me.DoAction( "error", 0, 0, 0, 0, "You need to wait " + str( (self.executiontime - time) / 1000 ) + " more seconds to use this again!" )
            return

        id = FindTarget( r.SeekItem, r.IsValidItem, r.CurrentItem, args )
        item = BetterMUD.item( id )
        name = item.Name()

        # add 120 seconds; 2 minutes
        self.executiontime = time + 120000

        self.mud.AddActionAbsolute( 0, "addlogic", 1, id, 0, 0, "uberweight" )
        self.mud.AddActionAbsolute( 0, "vision", r.ID(), 0, 0, 0, "<#FF0000>" + me.Name() + " just cast UBERWEIGHT on " + name + "!" )
        self.mud.AddActionRelative( 20000, "messagelogic", 1, id, 0, 0, "uberweight remove" )
