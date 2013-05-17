import BetterMUD
import string
import data.logics.logic



class spellscroll( data.logics.logic.logic ):
    def DoRead( self, character, item, name ):
        c = BetterMUD.character( character )
        i = BetterMUD.item( item )
        if c.HasCommand( name ):
            c.DoAction( "error", 0, 0, 0, 0, "You already know this spell!" )
            return

        c.AddCommand( name )
        self.mud.AddActionAbsolute( 0, "vision", c.Room(), 0, 0, 0, c.Name() + " reads " + i.Name() + "!" )
        self.mud.AddActionAbsolute( 1, "destroyitem", i.ID(), 0, 0, 0, "" )
        c.DoAction( "announce", 0, 0, 0, 0, "You now know the spell " + name + "!" )
        c.DoAction( "announce", 0, 0, 0, 0, "The " + i.Name() + " disappears in a bright flash of flame!" )


class uberweightscroll( spellscroll ):
    def Run( self, action, arg1, arg2, arg3, arg4, data ):
        if action == "do" and data == "read":
            self.DoRead( arg3, self.me, "uberweight" )
            return
