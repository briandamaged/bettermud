import string
import BetterMUD
import PythonCommand

FindTarget = PythonCommand.FindTarget

class announce( PythonCommand.Command ):
    name = "announce"
    usage = "\"announce <announcement>\""
    description = "This shows a system-wide announcement"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError
        me = BetterMUD.character( self.me )
        self.mud.AddActionAbsolute( 0, "announce", 0, 0, 0, 0, "Announcement by " + me.Name() + ": " + args )



class get( PythonCommand.Command ):
    name = "get"
    usage = "\"get <|quantity> <item>\""
    description = "This makes your character attempt to pick up an item"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError
        me = BetterMUD.character( self.me )
        r = BetterMUD.room( me.Room() )

        quantity = 0
        item = args

        if string.digits.find( args[0] ) != -1:
            # first letter is a digit, so get quantity
            split = args.split( None, 1 )
            try:
                quantity = int( split[0] )
                item = split[1]
            except:
                # do nothing
                pass

        i = BetterMUD.item( FindTarget( r.SeekItem, r.IsValidItem, r.CurrentItem, item ) )
        if i.IsQuantity() and quantity == 0:
            quantity = i.GetQuantity()

        self.mud.DoAction( "attemptgetitem", me.ID(), r.CurrentItem(), quantity, 0, "" )


class drop( PythonCommand.Command ):
    name = "drop"
    usage = "\"drop <item>\""
    description = "This makes your character attempt to drop an item"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError

        me = BetterMUD.character( self.me )

        quantity = 0
        item = args

        if string.digits.find( args[0] ) != -1:
            # first letter is a digit, so get quantity
            split = args.split( None, 1 )
            try:
                quantity = int( split[0] )
                item = split[1]
            except:
                # do nothing
                pass

        i = BetterMUD.item( FindTarget( me.SeekItem, me.IsValidItem, me.CurrentItem, item ) )

        # if user didn't specify the quantity of a quantity item,
        # just get the entire amount.
        if i.IsQuantity() and quantity == 0:
            quantity = i.GetQuantity()

        self.mud.DoAction( "attemptdropitem", me.ID(), me.CurrentItem(), quantity, 0, "" )


class give( PythonCommand.Command ):
    name = "give"
    usage = "\"give <character> <item>\""
    description = "This makes your character attempt give someone an item"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError
        parms = args.split( None, 1 )
        if len(parms) < 2: raise PythonCommand.UsageError

        me = BetterMUD.character( self.me )
        r = BetterMUD.room( me.Room() )


        recipient = FindTarget( r.SeekCharacter, r.IsValidCharacter, r.CurrentCharacter, parms[0] )
        if recipient == me.ID():
            me.DoAction( "error", 0, 0, 0, 0, "You can't give yourself an object!" )
            return

        quantity = 0
        item = parms[1]

        if string.digits.find( parms[1][0] ) != -1:
            # first letter is a digit, so get quantity
            split = parms[1].split( None, 1 )
            try:
                quantity = int( split[0] )
                item = split[1]
            except:
                # do nothing
                pass

        i = BetterMUD.item( FindTarget( me.SeekItem, me.IsValidItem, me.CurrentItem, item ) )

        # if user didn't specify the quantity of a quantity item,
        # just get the entire amount.
        if i.IsQuantity() and quantity == 0:
            quantity = i.GetQuantity()

        self.mud.DoAction( "attemptgiveitem", me.ID(), r.CurrentCharacter(), me.CurrentItem(), quantity, "" )



class receive( PythonCommand.Command ):
    name = "receive"
    usage = "\"receive <on|off>\""
    description = "Turns your item receiving mode on or off"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError
        if args != "on" and args != "off": raise PythonCommand.UsageError

        me = BetterMUD.character( self.me )
        if args == "on":
            if me.HasLogic( "cantreceiveitems" ):
                me.DelLogic( "cantreceiveitems" )
                me.DoAction( "announce", 0, 0, 0, 0, "Receiving mode is now ON" )
            else:
                me.DoAction( "error", 0, 0, 0, 0, "You are already in receiving mode!" )
        else:
            if not me.HasLogic( "cantreceiveitems" ):
                me.AddLogic( "cantreceiveitems" )
                me.DoAction( "announce", 0, 0, 0, 0, "Receiving mode is now OFF" )
            else:
                me.DoAction( "error", 0, 0, 0, 0, "You are already in non-receiving mode!" )




class inventory( PythonCommand.Command ):
    name = "inventory"
    usage = "\"inventory\""
    description = "Lists items in your inventory"

    def Run( self, args ):
        me = BetterMUD.character( self.me )
        string =  "<#FFFFFF>--------------------------------------------------------------------------------\r\n"
        string += "<#00FF00> Your Inventory\r\n"
        string += "<#FFFFFF>--------------------------------------------------------------------------------\r\n"
        string += "<$reset> "
        if me.Items() == 0:
            string += "NOTHING!!!\r\n"
        else:
            me.BeginItem()
            while me.IsValidItem():
                item = BetterMUD.item( me.CurrentItem() )
                string += item.Name()
                string += "<#00FF00>, <$reset>"
                me.NextItem()
        string += "\r\n<#FFFFFF>--------------------------------------------------------------------------------\r\n"
        string += "<#FFFFFF> Weapon:       <$reset>";
        if me.GetAttribute( "weapon" ) == 0:
            item = BetterMUD.itemtemplate( me.GetAttribute( "defaultweapon" ) )
        else:
            item = BetterMUD.item( me.GetAttribute( "weapon" ) )
        string += item.Name() + "\r\n"
        string += "<#FFFFFF> Total Weight: <$reset>" + str( me.GetAttribute( "encumbrance" ) ) + "\r\n"
        string += "<#FFFFFF> Max Weight:   <$reset>" + str( me.GetAttribute( "maxencumbrance" ) ) + "\r\n"
        string += "<#FFFFFF>--------------------------------------------------------------------------------\r\n"
        me.DoAction( "announce", 0, 0, 0, 0, string )




class arm( PythonCommand.Command ):
    name = "arm"
    usage = "\"arm <item>\""
    description = "Attempts to arm an item"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError

        me = BetterMUD.character( self.me )

        item = BetterMUD.item( FindTarget( me.SeekItem, me.IsValidItem, me.CurrentItem, args ) )

        if not me.DoAction( "query", item.ID(), 0, 0, 0, "canarm" ):
            me.DoAction( "error", 0, 0, 0, 0, "Cannot arm item: " + item.Name() + "!" )
            return

        me.DoAction( "do", 0, 0, item.ID(), 0, "arm" )



class disarm( PythonCommand.Command ):
    name = "disarm"
    usage = "\"disarm <item>\""
    description = "Attempts to disarm an item"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError

        me = BetterMUD.character( self.me )
        if args == "weapon":
            me.DoAction( "do", 0, 0, 1, 0, "disarm" )



class read( PythonCommand.Command ):
    name = "read"
    usage = "\"read <item>\""
    description = "Tries to read an item"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError

        me = BetterMUD.character( self.me )
        r = BetterMUD.room( me.Room() )

        try:
            item = BetterMUD.item( FindTarget( me.SeekItem, me.IsValidItem, me.CurrentItem, args ) )
        except:
            item = BetterMUD.item( FindTarget( r.SeekItem, r.IsValidItem, r.CurrentItem, args ) )

        if not item.DoAction( "query", 0, 0, 0, 0, "canread" ):
            me.DoAction( "error", 0, 0, 0, 0, "Cannot read " + item.Name() + "!" )
            return

        item.DoAction( "do", 0, 0, me.ID(), 0, "read" )


class list( PythonCommand.Command ):
    name = "list"
    usage = "\"list <merchant>\""
    description = "Gets a list of the merchants wares"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError

        me = BetterMUD.character( self.me )
        r = BetterMUD.room( me.Room() )
        m = BetterMUD.character( FindTarget( r.SeekCharacter, r.IsValidCharacter, r.CurrentCharacter, args ) )
        m.DoAction( "do", 0, 0, me.ID(), 0, "list" )


class buy( PythonCommand.Command ):
    name = "buy"
    usage = "\"buy <merchant> <item>\""
    description = "buys an item from a merchant"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError
        parms = args.split( None, 1 )
        if len( parms ) < 2: raise PythonCommand.UsageError

        me = BetterMUD.character( self.me )
        r = BetterMUD.room( me.Room() )

        m = BetterMUD.character( FindTarget( r.SeekCharacter, r.IsValidCharacter, r.CurrentCharacter, parms[0] ) )
        m.DoAction( "do", 0, 0, me.ID(), 0, "buy " + parms[1] )




class attack( PythonCommand.Command ):
    name = "attack"
    usage = "\"attack <character>\""
    description = "initiates attack mode on a character"

    def Run( self, args ):
        if not args: raise PythonCommand.UsageError

        me = BetterMUD.character( self.me )
        r = BetterMUD.room( me.Room() )

        t = FindTarget( r.SeekCharacter, r.IsValidCharacter, r.CurrentCharacter, args )
        target = BetterMUD.character( t )
        if not target.DoAction( "query", me.ID(), 0, 0, 0, "canattack" ):
            return

        me.DoAction( "do", 0, 0, t, 0, "initattack" )


class breakattack( PythonCommand.Command ):
    name = "breakattack"
    usage = "\"breakattack\""
    description = "Stops attacking your target"

    def Run( self, args ):
        me = BetterMUD.character( self.me )
        me.DoAction( "do", 0, 0, 0, 0, "breakattack" )        