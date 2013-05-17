import string
import BetterMUD

class bettermudscript:

    # Initialize the script with an ID
    def Init( self, id ):
        self.me = id
        self.mud = BetterMUD.GameWrap()
        self.ScriptInit()

    def ScriptInit( self ):
        pass

    def Name( self ):
        return self.name

    def LoadScript( self, s ):
        pass

    def SaveScript( self ):
        return ""