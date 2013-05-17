import string
import BetterMUD
import PythonCommand


class action( PythonCommand.Command ):
    name = "action"
    usage = "\"action <verb phrase>\""
    description = "This executes a superflous action that doesn't affect game logic."

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError
        c = BetterMUD.character( self.me )
        self.mud.AddActionAbsolute( 0, "announce", 0, 0, 0, 0, "<#FFFF00>" + c.Name() + " " + args )


class pies( PythonCommand.Command ):
    name = "pies"
    usage = "\"pies <|character>\""
    description = "Silly action"
    def Run( self, args ):
        me = BetterMUD.character( self.me )
        r = BetterMUD.room( me.Room() )

        # find the name:
        if not args:
            name = "himself"
        else:
            r.SeekCharacter( args )
            if not r.IsValidCharacter():
                me.DoAction( "error", 0, 0, 0, 0, "Cannot find character: " + args )
                return
            id = r.CurrentCharacter()
            c = BetterMUD.character( id )
            name = c.Name()

        self.mud.AddActionAbsolute( 0, "vision", r.ID(), 0, 0, 0, "<#00FF00>OMG!!! " + me.Name() + " just threw a huge <#FFFF00>CUSTARD PIE<#00FF00> at " + name + "!!!!" )



