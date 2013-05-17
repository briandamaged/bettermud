import BetterMUD
import string
import data.logics.logic

class noelves( data.logics.logic.logic ):
    def Run( self, action, arg1, arg2, arg3, arg4, data ):
        if action == "canenterregion":
            character = BetterMUD.character( arg1 )
            if character.TemplateID() == 2:
                character.SeekItem( "Dwarven Mine Pass" )
                if character.IsValidItem():
                    return 0
                character.DoAction( "error", 0, 0, 0, 0, "As an elf, you are morally obligated to not enter these mines!" )
                return 1