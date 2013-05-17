import random
import BetterMUD
import data.logics.logic
import string



class combat( data.logics.logic.logic ):

    def ScriptInit( self ):
        self.attackedlist = []
        self.target = 0
        self.attacktime = 5000   # 5 seconds


    def Break( self, me ):
        if self.target == 0:
            return
        t = BetterMUD.character( self.target )
        me.KillHook( "do", "attack" )
        self.mud.AddActionAbsolute( 0, "vision", me.Room(), 0, 0, 0, me.Name() + " stops attacking " + t.Name() + "!!" )
        t.DoAction( "do", 0, 0, self.me, 0, "brokeattack" )
        self.target = 0


    def Run( self, action, arg1, arg2, arg3, arg4, data ):
        me = BetterMUD.character( self.me )


        if action == "modifyattribute" and data == "experience":
            me.DoAction( "announce", 0, 0, 0, 0, "<#00FFFF>You gain " + str( arg4 ) + " experience!" )
            return

        # check for death
        if action == "modifyattribute" and data == "hitpoints":
            if arg3 <= 0:
                me.DoAction( "do", 0, 0, 0, 0, "died" )
            return

        # you killed someone... celebrate!
        if action == "do" and data == "killed":
            self.Break( me )
            return

        if action == "do" and data == "died":
            self.Break( me )
            self.mud.AddActionAbsolute( 0, "vision", me.Room(), 0, 0, 0, me.Name() + " dies!!!" )

            # calculate how much experience to give to everyone attacking you
            experience = me.GetAttribute( "giveexperience" )
            if len( self.attackedlist ) > 0:
                experience = experience / len( self.attackedlist )

            # go through everyone, tell them you died, and give them their experience

            for x in self.attackedlist[:]:
                c = BetterMUD.character( x )
                c.DoAction( "do", 0, 0, self.me, 0, "killed" )
                self.mud.DoAction( "modifyattribute", 0, x, c.GetAttribute( "experience" ) + experience, experience, "experience" )

            # clear the list
            self.attackedlist = []

            # go through all his items and force them to drop
            me.BeginItem()
            while me.IsValidItem():
                self.mud.DoAction( "dropitem", me.ID(), me.CurrentItem(), 0, 0, "" )
                me.NextItem()

            # now figure out how to kill the character
            if not me.IsPlayer():
                # just destroy non-players
                self.mud.AddActionAbsolute( 0, "destroycharacter", self.me, 0, 0, 0, "" )
            else:
                # give the player some hitpoints back
                me.SetAttribute( "hitpoints", (me.GetAttribute( "maxhitpoints" ) / 10) * 7 )

                # now spawn the player somewhere, checking the current room, current region, current character,
                # and finally giving up and sending the player to room 1.
                r = BetterMUD.room( me.Room() )
                if r.DoAction( "do", me.ID(), 0, 0, 0, "deathtransport" ):
                    return
                r = BetterMUD.region( me.Region() )
                if r.DoAction( "do", me.ID(), 0, 0, 0, "deathtransport" ):
                    return
                if me.DoAction( "do", me.ID(), 0, 0, 0, "deathtransport" ):
                    return
                self.mud.DoAction( "forcetransport", me.ID(), 1, 0, 0, "" )
            return


        # reset hp if maxhp goes down below hp.
        if action == "modifyattribute" and data == "maxhitpoints":
            if me.GetAttribute( "hitpoints" ) > me.GetAttribute( "maxhitpoints" ):
                me.SetAttribute( "hitpoints", me.GetAttribute( "maxhitpoints" ) )
            return

        # people with the combat module can be attacked
        if action == "query" and data == "canattack":
            return 1


        # add character to attacked list if he isn't there
        if action == "do" and data == "attacked":
            try:
                self.attackedlist.index( arg3 )
            except:
                self.attackedlist.append( arg3 )
            return

        # remove character from attacked list
        if action == "do" and data == "brokeattack":
            try:
                self.attackedlist.remove( arg3 )
            except:
                pass
            return


        # initiate an attack
        if action == "do" and data == "initattack":
            if arg3 == self.me: return

            # clear the old target if attacking someone else
            if self.target != 0:
                t = BetterMUD.character( self.target )
                t.DoAction( "do", 0, 0, self.me, 0, "brokeattack" )
            else:
                self.mud.AddActionRelative( 0, "do", 0, self.me, 0, 0, "attack" )

            # set the new target and tell him he's been attacked
            self.target = arg3
            t = BetterMUD.character( arg3 )
            t.DoAction( "do", 0, 0, self.me, 0, "attacked" )
            self.mud.AddActionAbsolute( 0, "vision", me.Room(), 0, 0, 0, me.Name() + " begins attacking " + t.Name() + "!!" )
            return


        # clear the old target if attacking someone else
        if action == "do" and data == "breakattack":
            self.Break( me )
            return

        # break if target or you leaves room
        if action == "leaveroom":
            if arg1 == self.target or arg1 == self.me:
                self.Break( me )
            return

        if action == "do" and data == "attack":

            # get the target
            target = BetterMUD.character( self.target )

            # set another attack round
            self.mud.AddActionRelative( self.attacktime, "do", 0, self.me, 0, 0, "attack" )

            # get the weapon
            if me.GetAttribute( "weapon" ) == 0:
                weapon = BetterMUD.itemtemplate( me.GetAttribute( "defaultweapon" ) )
            else:
                weapon = BetterMUD.item( me.GetAttribute( "weapon" ) )

            # calculate the accuracy
            accuracy = weapon.GetAttribute( "accuracy" )
            accuracy += target.DoAction( "query", me.ID(), target.ID(), 0, 0, "getaccuracydelta" )
            accuracy += me.DoAction( "query", me.ID(), target.ID(), 0, 0, "getaccuracydelta" )

            # see if you hit him
            if accuracy <= random.randint( 0, 99 ):
                self.mud.AddActionAbsolute( 0, "vision", me.Room(), 0, 0, 0, me.Name() + " swings at " + target.Name() + " with " + weapon.Name() + ", but misses!" )
                return

            # calculate damage and hit
            damage = random.randint( weapon.GetAttribute( "mindamage" ), weapon.GetAttribute( "maxdamage" ) )
            self.mud.DoAction( "vision", me.Room(), 0, 0, 0, "<#FF0000>" + me.Name() + " hits " + target.Name() + " with " + weapon.Name() + " for " + str( damage ) + " damage!" )
            self.mud.DoAction( "modifyattribute", 0, target.ID(), target.GetAttribute( "hitpoints" ) - damage, damage, "hitpoints" )





class evilmonster( data.logics.logic.logic ):

    def Run( self, action, arg1, arg2, arg3, arg4, data ):
        me = BetterMUD.character( self.me )

        # Attack anyone who enters the room
        if action == "enterroom":
            if arg1 != self.me:
                self.mud.AddActionAbsolute( 0, "do", 0, me.ID(), arg1, 0, "initattack" )
            return


        # you killed someone find another target!
        if action == "do" and data == "killed":
            r = BetterMUD.room( me.Room() )
            r.BeginCharacter()
            while r.IsValidCharacter():
                if r.CurrentCharacter() != arg3:    # make sure you don't re-attack the character you just killed!
                    self.mud.AddActionAbsolute( 0, "do", 0, me.ID(), r.CurrentCharacter(), 0, "initattack" )
                    return
                r.NextCharacter()
            return

