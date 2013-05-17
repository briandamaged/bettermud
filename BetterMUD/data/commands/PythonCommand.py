import string
import BetterMUD
import data.bettermudscript

class UsageError(Exception):
    pass

class TargetError(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)


def FindTarget( seekf, validf, getf, name ):
    seekf( name )
    if not validf(): raise TargetError( name )
    return getf()


class Command( data.bettermudscript.bettermudscript ):

    # Usage
    def Usage( self ):
        return self.usage

    # description
    def Description( self ):
        return self.description

    # the standard call method.
    def Execute( self, args ):
        try:
            self.Run( args )
        except UsageError:
            me = BetterMUD.character( self.me )
            me.DoAction( "error", 0, 0, 0, 0, "Usage: " + self.Usage() )
        except TargetError, e:
            me = BetterMUD.character( self.me )
            me.DoAction( "error", 0, 0, 0, 0, "Cannot find: " + e.value )



            