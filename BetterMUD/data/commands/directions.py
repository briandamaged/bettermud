import string
import BetterMUD
import PythonCommand


class north( PythonCommand.Command ):
    name = "north"
    usage = "\"north\""
    description = "Attempts to move north"
    def Run( self, args ):
        c = BetterMUD.character( self.me )
        self.mud.DoAction( "command", c.ID(), 0, 0, 0, "/go north" )

class east( PythonCommand.Command ):
    name = "east"
    usage = "\"east\""
    description = "Attempts to move east"
    def Run( self, args ):
        c = BetterMUD.character( self.me )
        self.mud.DoAction( "command", c.ID(), 0, 0, 0, "/go east" )

class south( PythonCommand.Command ):
    name = "south"
    usage = "\"south\""
    description = "Attempts to move south"
    def Run( self, args ):
        c = BetterMUD.character( self.me )
        self.mud.DoAction( "command", c.ID(), 0, 0, 0, "/go south" )

class west( PythonCommand.Command ):
    name = "west"
    usage = "\"west\""
    description = "Attempts to move west"
    def Run( self, args ):
        c = BetterMUD.character( self.me )
        self.mud.DoAction( "command", c.ID(), 0, 0, 0, "/go west" )

class northeast( PythonCommand.Command ):
    name = "northeast"
    usage = "\"northeast\""
    description = "Attempts to move northeast"
    def Run( self, args ):
        c = BetterMUD.character( self.me )
        self.mud.DoAction( "command", c.ID(), 0, 0, 0, "/go northeast" )

class northwest( PythonCommand.Command ):
    name = "northwest"
    usage = "\"northwest\""
    description = "Attempts to move northwest"
    def Run( self, args ):
        c = BetterMUD.character( self.me )
        self.mud.DoAction( "command", c.ID(), 0, 0, 0, "/go northwest" )

class southeast( PythonCommand.Command ):
    name = "southeast"
    usage = "\"southeast\""
    description = "Attempts to move southeast"
    def Run( self, args ):
        c = BetterMUD.character( self.me )
        self.mud.DoAction( "command", c.ID(), 0, 0, 0, "/go southeast" )

class southwest( PythonCommand.Command ):
    name = "southwest"
    usage = "\"southwest\""
    description = "Attempts to move southwest"
    def Run( self, args ):
        c = BetterMUD.character( self.me )
        self.mud.DoAction( "command", c.ID(), 0, 0, 0, "/go southwest" )

class up( PythonCommand.Command ):
    name = "up"
    usage = "\"up\""
    description = "Attempts to move up"
    def Run( self, args ):
        c = BetterMUD.character( self.me )
        self.mud.DoAction( "command", c.ID(), 0, 0, 0, "/go above" )

class down( PythonCommand.Command ):
    name = "down"
    usage = "\"down\""
    description = "Attempts to move down"
    def Run( self, args ):
        c = BetterMUD.character( self.me )
        self.mud.DoAction( "command", c.ID(), 0, 0, 0, "/go below" )

class ne( northeast ):
    name = "ne"
    usage = "\"ne\""

class nw( northwest ):
    name = "nw"
    usage = "\"nw\""

class se( southeast ):
    name = "se"
    usage = "\"se\""

class sw( southwest ):
    name = "sw"
    usage = "\"sw\""