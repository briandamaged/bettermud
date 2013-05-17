import BetterMUD
import data.logics.logic

class cantreceiveitems( data.logics.logic.logic ):
    def Run( self, action, arg1, arg2, arg3, arg4, data ):
        if action == "canreceiveitem":
            g = BetterMUD.character( arg1 )
            if not g.IsPlayer(): return 0     # accept stuff from NPC's with the implcit promise that they aren't malicious
            i = BetterMUD.item( arg3 )
            me = BetterMUD.character( self.me )
            me.DoAction( "error", 0, 0, 0, 0, g.Name() + " tried to give you " + i.Name() + " but you have item receiving turned off. Type \"/receive on\" to turn receiving back on." )
            g.DoAction( "error", 0, 0, 0, 0, me.Name() + " refuses to take " + i.Name() + "!" )
            return 1




class encumbrance( data.logics.logic.logic ):
    def Weight( self, i, q ):
        item = BetterMUD.item( i )
        if item.IsQuantity():
            return q * item.GetAttribute( "weight" )
        else:
            return item.GetAttribute( "weight" )

    def Run( self, action, arg1, arg2, arg3, arg4, data ):
        me = BetterMUD.character( self.me )

        if action == "canleaveroom":
            if me.GetAttribute( "encumbrance" ) > me.GetAttribute( "maxencumbrance" ):
                me.DoAction( "error", 0, 0, 0, 0, "You cannot move! You're too heavy! Drop something first!" )
                return 1
            return 0

        if action == "getitem":
            if arg1 == self.me:
                item = BetterMUD.item( arg2 )
                weight = self.Weight( arg2, arg3 )
                me.SetAttribute( "encumbrance", me.GetAttribute( "encumbrance" ) + weight )
            return 0

        if action == "dropitem":
            if arg1 == self.me:
                item = BetterMUD.item( arg2 )
                weight = self.Weight( arg2, arg3 )
                me.SetAttribute( "encumbrance", me.GetAttribute( "encumbrance" ) - weight )
            return 0

        if action == "destroyitem":
            item = BetterMUD.item( arg1 )
            weight = self.Weight( arg1, item.GetQuantity() )
            me.SetAttribute( "encumbrance", me.GetAttribute( "encumbrance" ) - weight )
            return 0

        if action == "giveitem":
            if arg1 == self.me:
                item = BetterMUD.item( arg3 )
                weight = self.Weight( arg3, arg4 )
                me.SetAttribute( "encumbrance", me.GetAttribute( "encumbrance" ) - weight )
            if arg2 == self.me:
                item = BetterMUD.item( arg3 )
                weight = self.Weight( arg3, arg4 )
                me.SetAttribute( "encumbrance", me.GetAttribute( "encumbrance" ) + weight )
            return 0

        if action == "spawnitem":
            item = BetterMUD.item( arg1 )
            weight = self.Weight( arg1, item.GetQuantity() )
            me.SetAttribute( "encumbrance", me.GetAttribute( "encumbrance" ) + weight )
            return 0

        if action == "cangetitem":
            item = BetterMUD.item( arg2 )
            weight = self.Weight( arg2, arg3 )
            if weight + me.GetAttribute( "encumbrance" ) > me.GetAttribute( "maxencumbrance" ):
                me.DoAction( "error", 0, 0, 0, 0, "You can't pick up " + item.Name() + " because it's too heavy for you to carry!" )
                return 1
            return 0

        if action == "canreceiveitem":
            g = BetterMUD.character( arg1 )
            item = BetterMUD.item( arg3 )
            weight = self.Weight( arg3, arg4 )
            if weight + me.GetAttribute( "encumbrance" ) > me.GetAttribute( "maxencumbrance" ):
                me.DoAction( "error", 0, 0, 0, 0, g.Name() + " tried to give you " + item.Name() + " but it's too heavy for you to carry!" )
                g.DoAction( "error", 0, 0, 0, 0, "You can't give " + me.Name() + " the " + item.Name() + " because it is too heavy!" )
                return 1
            return 0




class armaments( data.logics.logic.logic ):

    def Disarm( self, itemtype ):
        if itemtype == 1:
            me = BetterMUD.character( self.me )
            if me.GetAttribute( "weapon" ) != 0:
                weapon = BetterMUD.item( me.GetAttribute( "weapon" ) )
                me.SetAttribute( "weapon", 0 )
                self.mud.AddActionAbsolute( 0, "vision", me.Room(), 0, 0, 0, me.Name() + " disarms " + weapon.Name() + "." )

    def Arm( self, item ):
        me = BetterMUD.character( self.me )
        if item.GetAttribute( "arms" ) == 1:
            me.SetAttribute( "weapon", item.ID() )
            self.mud.AddActionAbsolute( 0, "vision", me.Room(), 0, 0, 0, me.Name() + " arms " + item.Name() + "!" )

    def Lose( self, me, itemid ):
        if me.GetAttribute( "weapon" ) == itemid:
            self.Disarm( 1 )


    def Run( self, action, arg1, arg2, arg3, arg4, data ):
        me = BetterMUD.character( self.me )
        if action == "query" and data == "canarm":
            item = BetterMUD.item( arg1 )
            if item.GetAttribute( "arms" ) == 1:
                return 1
            return 0

        if action == "do" and data == "arm":
            item = BetterMUD.item( arg3 )
            self.Disarm( 1 )
            self.Arm( item )

        if action == "do" and data == "disarm":
            self.Disarm( arg3 )

        if action == "dropitem" and arg1 == me.ID():
            self.Lose( me, arg2 )

        if action == "giveitem" and arg1 == me.ID():
            self.Lose( me, arg3 )

        if action == "destroyitem":
            self.Lose( me, arg1 )
            