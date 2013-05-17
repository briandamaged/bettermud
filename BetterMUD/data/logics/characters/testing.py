import BetterMUD
import data.logics.logic

class superglue( data.logics.logic.logic ):

    def Run( self, action, arg1, arg2, arg3, arg4, data ):
        me = BetterMUD.character( self.me )
        if action == "canleaveroom":
            me.DoAction( "error", 0, 0, 0, 0, "You're superglued to the ground. Sit tight, you ain't goin nowhere." )
            return 1
        if action == "messagelogic":
            if data == "superglue remove":
                self.mud.AddActionAbsolute( 0, "dellogic", 0, self.me, 0, 0, "superglue" )
                self.mud.AddActionAbsolute( 0, "vision", me.Room(), 0, 0, 0, "The superglue on " + me.Name() + " wears off!" )
