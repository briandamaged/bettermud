import BetterMUD
import data.logics.logic
import string

def HasEnoughCurrency( character, amount ):
    total = 0
    character.BeginItem()
    while character.IsValidItem():
        item = BetterMUD.item( character.CurrentItem() )
        if item.TemplateID() == 1:   # copper pieces
            total = total + item.GetQuantity()
        character.NextItem()

    if total >= amount:
        return 1
    return 0



def GiveCurrency( character, recipient, amount ):
    character.BeginItem()
    mud = BetterMUD.GameWrap()
    while character.IsValidItem():
        item = BetterMUD.item( character.CurrentItem() )
        if item.TemplateID() == 1:   # copper pieces
            mud.DoAction( "attemptgiveitem", character.ID(), recipient.ID(), item.ID(), amount, "" )
            return
        character.NextItem()


def FindName( classtype, list, search ):
    newsearch = string.lower( search )
    for x in list:
        item = classtype( x )
        if string.lower( item.Name() ) == newsearch:
            return x

    for x in list:
        item = classtype( x )
        name = string.lower( item.Name() )
        if string.find( name, newsearch ) == 0 or string.find( name, " " + newsearch ) != -1:
            return x

    return 0


class merchant( data.logics.logic.logic ):
    def Run( self, action, arg1, arg2, arg3, arg4, data ):
        me = BetterMUD.character( self.me )

        if action == "do" and data == "list":
            character = BetterMUD.character( arg3 )
            character.DoAction( "announce", 0, 0, 0, 0, "<#7F7F7F>--------------------------------------------------------------------------------" )
            character.DoAction( "announce", 0, 0, 0, 0, "<#FFFFFF> Item                                      | Cost" )
            character.DoAction( "announce", 0, 0, 0, 0, "<#7F7F7F>--------------------------------------------------------------------------------" )
            for x in self.iteminventory:
                item = BetterMUD.itemtemplate( x )
                character.DoAction( "announce", 0, 0, 0, 0, "<#7F7F7F> " + item.Name().ljust( 42 ) + "| " + str( item.GetAttribute( "value" ) ) )
            character.DoAction( "announce", 0, 0, 0, 0, "<#7F7F7F>--------------------------------------------------------------------------------" )
            return

        if action == "do" and data[:3] == "buy":
            itemname = data.split( None, 1 )
            itemname = itemname[1]
            character = BetterMUD.character( arg3 )
            id = FindName( BetterMUD.itemtemplate, self.iteminventory, itemname )
            if id == 0:
                character.DoAction( "announce", 0, 0, 0, 0, "Sorry, you can't buy " + itemname + "here!" )
                return

            t = BetterMUD.itemtemplate( id )
            if not HasEnoughCurrency( character, t.GetAttribute( "value" ) ):
                character.DoAction( "announce", 0, 0, 0, 0, "Sorry, you don't have enough money to buy " + t.Name() + "!" )
                return

            GiveCurrency( character, me, t.GetAttribute( "value" ) )
            self.mud.DoAction( "spawnitem", id, character.ID(), 1, 0, "" )
            self.mud.AddActionAbsolute( 0, "vision", character.Room(), 0, 0, 0, character.Name() + " buys " + t.Name() + "." )



                