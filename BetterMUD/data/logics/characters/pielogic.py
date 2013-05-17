import BetterMUD
import data.logics.logic

class pies( data.logics.logic.logic ):
    def Run( self, action, arg1, arg2, arg3, arg4, data ):
        me = BetterMUD.character( self.me )
        if action == "say" and data.find( "pies" ) != -1 and arg1 != me.ID():
            c = BetterMUD.character( arg1 )
            self.mud.AddActionAbsolute( 0, "attemptsay", me.ID(), 0, 0, 0, c.Name() + ": YES!!! PIES!!!!!" )

        return 0


class glarepie( data.logics.logic.logic ):
    def Run( self, action, arg1, arg2, arg3, arg4, data ):
        if action == "getitem":
            item = BetterMUD.item( arg2 )
            print item.TemplateID()
            print "lies"
            if item.TemplateID() == 2:
                print "pies"
                self.mud.AddActionAbsolute( 0, "attemptsay", self.me, 0, 0, 0, "Hey!!!! Thos-a Pies aren't-a FREE!" )
                print "cries"

        return 0
