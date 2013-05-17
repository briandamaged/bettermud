import BetterMUD
import string
import data.bettermudscript

class logic( data.bettermudscript.bettermudscript ):
    def Attribute( self, attr ):
        return 0

    def Execute( self, action, arg1, arg2, arg3, arg4, data ):
        r = self.Run( action, arg1, arg2, arg3, arg4, data )
        if r: return r
        else : return 0
       