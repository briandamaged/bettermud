# This file was created automatically by SWIG.
# Don't modify this file, modify the SWIG interface instead.
# This file is compatible with both classic and new-style classes.
import _BetterMUD
def _swig_setattr(self,class_type,name,value):
    if (name == "this"):
        if isinstance(value, class_type):
            self.__dict__[name] = value.this
            if hasattr(value,"thisown"): self.__dict__["thisown"] = value.thisown
            del value.thisown
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    self.__dict__[name] = value

def _swig_getattr(self,class_type,name):
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError,name

import types
try:
    _object = types.ObjectType
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0


class account(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, account, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, account, name)
    def __init__(self,*args):
        _swig_setattr(self, account, 'this', apply(_BetterMUD.new_account,args))
        _swig_setattr(self, account, 'thisown', 1)
    def __del__(self, destroy= _BetterMUD.delete_account):
        try:
            if self.thisown: destroy(self)
        except: pass
    def ID(*args): return apply(_BetterMUD.account_ID,args)
    def Name(*args): return apply(_BetterMUD.account_Name,args)
    def Description(*args): return apply(_BetterMUD.account_Description,args)
    def SetID(*args): return apply(_BetterMUD.account_SetID,args)
    def SetName(*args): return apply(_BetterMUD.account_SetName,args)
    def SetDescription(*args): return apply(_BetterMUD.account_SetDescription,args)
    def AddCharacter(*args): return apply(_BetterMUD.account_AddCharacter,args)
    def DelCharacter(*args): return apply(_BetterMUD.account_DelCharacter,args)
    def Characters(*args): return apply(_BetterMUD.account_Characters,args)
    def BeginCharacter(*args): return apply(_BetterMUD.account_BeginCharacter,args)
    def CurrentCharacter(*args): return apply(_BetterMUD.account_CurrentCharacter,args)
    def NextCharacter(*args): return apply(_BetterMUD.account_NextCharacter,args)
    def IsValidCharacter(*args): return apply(_BetterMUD.account_IsValidCharacter,args)
    def SeekCharacter(*args): return apply(_BetterMUD.account_SeekCharacter,args)
    def Password(*args): return apply(_BetterMUD.account_Password,args)
    def LoginTime(*args): return apply(_BetterMUD.account_LoginTime,args)
    def AccessLevel(*args): return apply(_BetterMUD.account_AccessLevel,args)
    def Banned(*args): return apply(_BetterMUD.account_Banned,args)
    def AllowedCharacters(*args): return apply(_BetterMUD.account_AllowedCharacters,args)
    def SetPass(*args): return apply(_BetterMUD.account_SetPass,args)
    def SetLoginTime(*args): return apply(_BetterMUD.account_SetLoginTime,args)
    def SetAccessLevel(*args): return apply(_BetterMUD.account_SetAccessLevel,args)
    def SetBanned(*args): return apply(_BetterMUD.account_SetBanned,args)
    def SetAllowedCharacters(*args): return apply(_BetterMUD.account_SetAllowedCharacters,args)
    def __repr__(self):
        return "<C account instance at %s>" % (self.this,)

class accountPtr(account):
    def __init__(self,this):
        _swig_setattr(self, account, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, account, 'thisown', 0)
        _swig_setattr(self, account,self.__class__,account)
_BetterMUD.account_swigregister(accountPtr)

class charactertemplate(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, charactertemplate, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, charactertemplate, name)
    def __init__(self,*args):
        _swig_setattr(self, charactertemplate, 'this', apply(_BetterMUD.new_charactertemplate,args))
        _swig_setattr(self, charactertemplate, 'thisown', 1)
    def __del__(self, destroy= _BetterMUD.delete_charactertemplate):
        try:
            if self.thisown: destroy(self)
        except: pass
    def ID(*args): return apply(_BetterMUD.charactertemplate_ID,args)
    def Name(*args): return apply(_BetterMUD.charactertemplate_Name,args)
    def Description(*args): return apply(_BetterMUD.charactertemplate_Description,args)
    def GetAttribute(*args): return apply(_BetterMUD.charactertemplate_GetAttribute,args)
    def SetAttribute(*args): return apply(_BetterMUD.charactertemplate_SetAttribute,args)
    def HasAttribute(*args): return apply(_BetterMUD.charactertemplate_HasAttribute,args)
    def AddAttribute(*args): return apply(_BetterMUD.charactertemplate_AddAttribute,args)
    def DelAttribute(*args): return apply(_BetterMUD.charactertemplate_DelAttribute,args)
    def __repr__(self):
        return "<C charactertemplate instance at %s>" % (self.this,)

class charactertemplatePtr(charactertemplate):
    def __init__(self,this):
        _swig_setattr(self, charactertemplate, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, charactertemplate, 'thisown', 0)
        _swig_setattr(self, charactertemplate,self.__class__,charactertemplate)
_BetterMUD.charactertemplate_swigregister(charactertemplatePtr)

class character(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, character, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, character, name)
    def __init__(self,*args):
        _swig_setattr(self, character, 'this', apply(_BetterMUD.new_character,args))
        _swig_setattr(self, character, 'thisown', 1)
    def __del__(self, destroy= _BetterMUD.delete_character):
        try:
            if self.thisown: destroy(self)
        except: pass
    def ID(*args): return apply(_BetterMUD.character_ID,args)
    def Name(*args): return apply(_BetterMUD.character_Name,args)
    def Description(*args): return apply(_BetterMUD.character_Description,args)
    def SetID(*args): return apply(_BetterMUD.character_SetID,args)
    def SetName(*args): return apply(_BetterMUD.character_SetName,args)
    def SetDescription(*args): return apply(_BetterMUD.character_SetDescription,args)
    def Room(*args): return apply(_BetterMUD.character_Room,args)
    def SetRoom(*args): return apply(_BetterMUD.character_SetRoom,args)
    def Region(*args): return apply(_BetterMUD.character_Region,args)
    def SetRegion(*args): return apply(_BetterMUD.character_SetRegion,args)
    def TemplateID(*args): return apply(_BetterMUD.character_TemplateID,args)
    def SetTemplateID(*args): return apply(_BetterMUD.character_SetTemplateID,args)
    def AddItem(*args): return apply(_BetterMUD.character_AddItem,args)
    def DelItem(*args): return apply(_BetterMUD.character_DelItem,args)
    def Items(*args): return apply(_BetterMUD.character_Items,args)
    def BeginItem(*args): return apply(_BetterMUD.character_BeginItem,args)
    def CurrentItem(*args): return apply(_BetterMUD.character_CurrentItem,args)
    def NextItem(*args): return apply(_BetterMUD.character_NextItem,args)
    def IsValidItem(*args): return apply(_BetterMUD.character_IsValidItem,args)
    def SeekItem(*args): return apply(_BetterMUD.character_SeekItem,args)
    def GetAttribute(*args): return apply(_BetterMUD.character_GetAttribute,args)
    def SetAttribute(*args): return apply(_BetterMUD.character_SetAttribute,args)
    def HasAttribute(*args): return apply(_BetterMUD.character_HasAttribute,args)
    def AddAttribute(*args): return apply(_BetterMUD.character_AddAttribute,args)
    def DelAttribute(*args): return apply(_BetterMUD.character_DelAttribute,args)
    def AddLogic(*args): return apply(_BetterMUD.character_AddLogic,args)
    def AddExistingLogic(*args): return apply(_BetterMUD.character_AddExistingLogic,args)
    def DelLogic(*args): return apply(_BetterMUD.character_DelLogic,args)
    def GetLogic(*args): return apply(_BetterMUD.character_GetLogic,args)
    def HasLogic(*args): return apply(_BetterMUD.character_HasLogic,args)
    def DoAction(*args): return apply(_BetterMUD.character_DoAction,args)
    def GetLogicAttribute(*args): return apply(_BetterMUD.character_GetLogicAttribute,args)
    def AddHook(*args): return apply(_BetterMUD.character_AddHook,args)
    def DelHook(*args): return apply(_BetterMUD.character_DelHook,args)
    def Hooks(*args): return apply(_BetterMUD.character_Hooks,args)
    def KillHook(*args): return apply(_BetterMUD.character_KillHook,args)
    def ClearHooks(*args): return apply(_BetterMUD.character_ClearHooks,args)
    def HasCommand(*args): return apply(_BetterMUD.character_HasCommand,args)
    def AddCommand(*args): return apply(_BetterMUD.character_AddCommand,args)
    def DelCommand(*args): return apply(_BetterMUD.character_DelCommand,args)
    def BeginCommands(*args): return apply(_BetterMUD.character_BeginCommands,args)
    def CurrentCommand(*args): return apply(_BetterMUD.character_CurrentCommand,args)
    def CurrentCommandUsage(*args): return apply(_BetterMUD.character_CurrentCommandUsage,args)
    def CurrentCommandDescription(*args): return apply(_BetterMUD.character_CurrentCommandDescription,args)
    def NextCommand(*args): return apply(_BetterMUD.character_NextCommand,args)
    def IsValidCommand(*args): return apply(_BetterMUD.character_IsValidCommand,args)
    def SeekCommand(*args): return apply(_BetterMUD.character_SeekCommand,args)
    def Quiet(*args): return apply(_BetterMUD.character_Quiet,args)
    def IsPlayer(*args): return apply(_BetterMUD.character_IsPlayer,args)
    def Verbose(*args): return apply(_BetterMUD.character_Verbose,args)
    def GetAccount(*args): return apply(_BetterMUD.character_GetAccount,args)
    def SetQuiet(*args): return apply(_BetterMUD.character_SetQuiet,args)
    def SetAccount(*args): return apply(_BetterMUD.character_SetAccount,args)
    def IsLoggedIn(*args): return apply(_BetterMUD.character_IsLoggedIn,args)
    def LastCommand(*args): return apply(_BetterMUD.character_LastCommand,args)
    def __repr__(self):
        return "<C character instance at %s>" % (self.this,)

class characterPtr(character):
    def __init__(self,this):
        _swig_setattr(self, character, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, character, 'thisown', 0)
        _swig_setattr(self, character,self.__class__,character)
_BetterMUD.character_swigregister(characterPtr)

class itemtemplate(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, itemtemplate, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, itemtemplate, name)
    def __init__(self,*args):
        _swig_setattr(self, itemtemplate, 'this', apply(_BetterMUD.new_itemtemplate,args))
        _swig_setattr(self, itemtemplate, 'thisown', 1)
    def __del__(self, destroy= _BetterMUD.delete_itemtemplate):
        try:
            if self.thisown: destroy(self)
        except: pass
    def ID(*args): return apply(_BetterMUD.itemtemplate_ID,args)
    def Name(*args): return apply(_BetterMUD.itemtemplate_Name,args)
    def Description(*args): return apply(_BetterMUD.itemtemplate_Description,args)
    def GetAttribute(*args): return apply(_BetterMUD.itemtemplate_GetAttribute,args)
    def SetAttribute(*args): return apply(_BetterMUD.itemtemplate_SetAttribute,args)
    def HasAttribute(*args): return apply(_BetterMUD.itemtemplate_HasAttribute,args)
    def AddAttribute(*args): return apply(_BetterMUD.itemtemplate_AddAttribute,args)
    def DelAttribute(*args): return apply(_BetterMUD.itemtemplate_DelAttribute,args)
    def IsQuantity(*args): return apply(_BetterMUD.itemtemplate_IsQuantity,args)
    def GetQuantity(*args): return apply(_BetterMUD.itemtemplate_GetQuantity,args)
    def __repr__(self):
        return "<C itemtemplate instance at %s>" % (self.this,)

class itemtemplatePtr(itemtemplate):
    def __init__(self,this):
        _swig_setattr(self, itemtemplate, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, itemtemplate, 'thisown', 0)
        _swig_setattr(self, itemtemplate,self.__class__,itemtemplate)
_BetterMUD.itemtemplate_swigregister(itemtemplatePtr)

class item(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, item, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, item, name)
    def __init__(self,*args):
        _swig_setattr(self, item, 'this', apply(_BetterMUD.new_item,args))
        _swig_setattr(self, item, 'thisown', 1)
    def __del__(self, destroy= _BetterMUD.delete_item):
        try:
            if self.thisown: destroy(self)
        except: pass
    def ID(*args): return apply(_BetterMUD.item_ID,args)
    def Name(*args): return apply(_BetterMUD.item_Name,args)
    def Description(*args): return apply(_BetterMUD.item_Description,args)
    def SetID(*args): return apply(_BetterMUD.item_SetID,args)
    def SetName(*args): return apply(_BetterMUD.item_SetName,args)
    def SetDescription(*args): return apply(_BetterMUD.item_SetDescription,args)
    def Room(*args): return apply(_BetterMUD.item_Room,args)
    def SetRoom(*args): return apply(_BetterMUD.item_SetRoom,args)
    def Region(*args): return apply(_BetterMUD.item_Region,args)
    def SetRegion(*args): return apply(_BetterMUD.item_SetRegion,args)
    def TemplateID(*args): return apply(_BetterMUD.item_TemplateID,args)
    def SetTemplateID(*args): return apply(_BetterMUD.item_SetTemplateID,args)
    def GetAttribute(*args): return apply(_BetterMUD.item_GetAttribute,args)
    def SetAttribute(*args): return apply(_BetterMUD.item_SetAttribute,args)
    def HasAttribute(*args): return apply(_BetterMUD.item_HasAttribute,args)
    def AddAttribute(*args): return apply(_BetterMUD.item_AddAttribute,args)
    def DelAttribute(*args): return apply(_BetterMUD.item_DelAttribute,args)
    def AddLogic(*args): return apply(_BetterMUD.item_AddLogic,args)
    def AddExistingLogic(*args): return apply(_BetterMUD.item_AddExistingLogic,args)
    def DelLogic(*args): return apply(_BetterMUD.item_DelLogic,args)
    def GetLogic(*args): return apply(_BetterMUD.item_GetLogic,args)
    def HasLogic(*args): return apply(_BetterMUD.item_HasLogic,args)
    def DoAction(*args): return apply(_BetterMUD.item_DoAction,args)
    def GetLogicAttribute(*args): return apply(_BetterMUD.item_GetLogicAttribute,args)
    def AddHook(*args): return apply(_BetterMUD.item_AddHook,args)
    def DelHook(*args): return apply(_BetterMUD.item_DelHook,args)
    def Hooks(*args): return apply(_BetterMUD.item_Hooks,args)
    def KillHook(*args): return apply(_BetterMUD.item_KillHook,args)
    def ClearHooks(*args): return apply(_BetterMUD.item_ClearHooks,args)
    def IsQuantity(*args): return apply(_BetterMUD.item_IsQuantity,args)
    def GetQuantity(*args): return apply(_BetterMUD.item_GetQuantity,args)
    def SetQuantity(*args): return apply(_BetterMUD.item_SetQuantity,args)
    def __repr__(self):
        return "<C item instance at %s>" % (self.this,)

class itemPtr(item):
    def __init__(self,this):
        _swig_setattr(self, item, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, item, 'thisown', 0)
        _swig_setattr(self, item,self.__class__,item)
_BetterMUD.item_swigregister(itemPtr)

class portal(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, portal, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, portal, name)
    def __init__(self,*args):
        _swig_setattr(self, portal, 'this', apply(_BetterMUD.new_portal,args))
        _swig_setattr(self, portal, 'thisown', 1)
    def __del__(self, destroy= _BetterMUD.delete_portal):
        try:
            if self.thisown: destroy(self)
        except: pass
    def ID(*args): return apply(_BetterMUD.portal_ID,args)
    def Name(*args): return apply(_BetterMUD.portal_Name,args)
    def Description(*args): return apply(_BetterMUD.portal_Description,args)
    def SetID(*args): return apply(_BetterMUD.portal_SetID,args)
    def SetName(*args): return apply(_BetterMUD.portal_SetName,args)
    def SetDescription(*args): return apply(_BetterMUD.portal_SetDescription,args)
    def Region(*args): return apply(_BetterMUD.portal_Region,args)
    def SetRegion(*args): return apply(_BetterMUD.portal_SetRegion,args)
    def GetAttribute(*args): return apply(_BetterMUD.portal_GetAttribute,args)
    def SetAttribute(*args): return apply(_BetterMUD.portal_SetAttribute,args)
    def HasAttribute(*args): return apply(_BetterMUD.portal_HasAttribute,args)
    def AddAttribute(*args): return apply(_BetterMUD.portal_AddAttribute,args)
    def DelAttribute(*args): return apply(_BetterMUD.portal_DelAttribute,args)
    def AddLogic(*args): return apply(_BetterMUD.portal_AddLogic,args)
    def AddExistingLogic(*args): return apply(_BetterMUD.portal_AddExistingLogic,args)
    def DelLogic(*args): return apply(_BetterMUD.portal_DelLogic,args)
    def GetLogic(*args): return apply(_BetterMUD.portal_GetLogic,args)
    def HasLogic(*args): return apply(_BetterMUD.portal_HasLogic,args)
    def DoAction(*args): return apply(_BetterMUD.portal_DoAction,args)
    def GetLogicAttribute(*args): return apply(_BetterMUD.portal_GetLogicAttribute,args)
    def AddHook(*args): return apply(_BetterMUD.portal_AddHook,args)
    def DelHook(*args): return apply(_BetterMUD.portal_DelHook,args)
    def Hooks(*args): return apply(_BetterMUD.portal_Hooks,args)
    def KillHook(*args): return apply(_BetterMUD.portal_KillHook,args)
    def ClearHooks(*args): return apply(_BetterMUD.portal_ClearHooks,args)
    def BeginPath(*args): return apply(_BetterMUD.portal_BeginPath,args)
    def CurrentStart(*args): return apply(_BetterMUD.portal_CurrentStart,args)
    def CurrentDirection(*args): return apply(_BetterMUD.portal_CurrentDirection,args)
    def CurrentEnd(*args): return apply(_BetterMUD.portal_CurrentEnd,args)
    def NextPath(*args): return apply(_BetterMUD.portal_NextPath,args)
    def IsValidPath(*args): return apply(_BetterMUD.portal_IsValidPath,args)
    def SeekStartRoom(*args): return apply(_BetterMUD.portal_SeekStartRoom,args)
    def SeekEndRoom(*args): return apply(_BetterMUD.portal_SeekEndRoom,args)
    def __repr__(self):
        return "<C portal instance at %s>" % (self.this,)

class portalPtr(portal):
    def __init__(self,this):
        _swig_setattr(self, portal, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, portal, 'thisown', 0)
        _swig_setattr(self, portal,self.__class__,portal)
_BetterMUD.portal_swigregister(portalPtr)

class region(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, region, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, region, name)
    def __init__(self,*args):
        _swig_setattr(self, region, 'this', apply(_BetterMUD.new_region,args))
        _swig_setattr(self, region, 'thisown', 1)
    def __del__(self, destroy= _BetterMUD.delete_region):
        try:
            if self.thisown: destroy(self)
        except: pass
    def ID(*args): return apply(_BetterMUD.region_ID,args)
    def Name(*args): return apply(_BetterMUD.region_Name,args)
    def Description(*args): return apply(_BetterMUD.region_Description,args)
    def SetID(*args): return apply(_BetterMUD.region_SetID,args)
    def SetName(*args): return apply(_BetterMUD.region_SetName,args)
    def SetDescription(*args): return apply(_BetterMUD.region_SetDescription,args)
    def AddItem(*args): return apply(_BetterMUD.region_AddItem,args)
    def DelItem(*args): return apply(_BetterMUD.region_DelItem,args)
    def Items(*args): return apply(_BetterMUD.region_Items,args)
    def BeginItem(*args): return apply(_BetterMUD.region_BeginItem,args)
    def CurrentItem(*args): return apply(_BetterMUD.region_CurrentItem,args)
    def NextItem(*args): return apply(_BetterMUD.region_NextItem,args)
    def IsValidItem(*args): return apply(_BetterMUD.region_IsValidItem,args)
    def SeekItem(*args): return apply(_BetterMUD.region_SeekItem,args)
    def AddCharacter(*args): return apply(_BetterMUD.region_AddCharacter,args)
    def DelCharacter(*args): return apply(_BetterMUD.region_DelCharacter,args)
    def Characters(*args): return apply(_BetterMUD.region_Characters,args)
    def BeginCharacter(*args): return apply(_BetterMUD.region_BeginCharacter,args)
    def CurrentCharacter(*args): return apply(_BetterMUD.region_CurrentCharacter,args)
    def NextCharacter(*args): return apply(_BetterMUD.region_NextCharacter,args)
    def IsValidCharacter(*args): return apply(_BetterMUD.region_IsValidCharacter,args)
    def SeekCharacter(*args): return apply(_BetterMUD.region_SeekCharacter,args)
    def AddRoom(*args): return apply(_BetterMUD.region_AddRoom,args)
    def DelRoom(*args): return apply(_BetterMUD.region_DelRoom,args)
    def Rooms(*args): return apply(_BetterMUD.region_Rooms,args)
    def BeginRoom(*args): return apply(_BetterMUD.region_BeginRoom,args)
    def CurrentRoom(*args): return apply(_BetterMUD.region_CurrentRoom,args)
    def NextRoom(*args): return apply(_BetterMUD.region_NextRoom,args)
    def IsValidRoom(*args): return apply(_BetterMUD.region_IsValidRoom,args)
    def SeekRoom(*args): return apply(_BetterMUD.region_SeekRoom,args)
    __swig_setmethods__["m_roomitr"] = _BetterMUD.region_m_roomitr_set
    __swig_getmethods__["m_roomitr"] = _BetterMUD.region_m_roomitr_get
    if _newclass:m_roomitr = property(_BetterMUD.region_m_roomitr_get,_BetterMUD.region_m_roomitr_set)
    def AddPortal(*args): return apply(_BetterMUD.region_AddPortal,args)
    def DelPortal(*args): return apply(_BetterMUD.region_DelPortal,args)
    def Portals(*args): return apply(_BetterMUD.region_Portals,args)
    def BeginPortal(*args): return apply(_BetterMUD.region_BeginPortal,args)
    def CurrentPortal(*args): return apply(_BetterMUD.region_CurrentPortal,args)
    def NextPortal(*args): return apply(_BetterMUD.region_NextPortal,args)
    def IsValidPortal(*args): return apply(_BetterMUD.region_IsValidPortal,args)
    def SeekPortal(*args): return apply(_BetterMUD.region_SeekPortal,args)
    __swig_setmethods__["m_portalitr"] = _BetterMUD.region_m_portalitr_set
    __swig_getmethods__["m_portalitr"] = _BetterMUD.region_m_portalitr_get
    if _newclass:m_portalitr = property(_BetterMUD.region_m_portalitr_get,_BetterMUD.region_m_portalitr_set)
    def GetAttribute(*args): return apply(_BetterMUD.region_GetAttribute,args)
    def SetAttribute(*args): return apply(_BetterMUD.region_SetAttribute,args)
    def HasAttribute(*args): return apply(_BetterMUD.region_HasAttribute,args)
    def AddAttribute(*args): return apply(_BetterMUD.region_AddAttribute,args)
    def DelAttribute(*args): return apply(_BetterMUD.region_DelAttribute,args)
    def AddLogic(*args): return apply(_BetterMUD.region_AddLogic,args)
    def AddExistingLogic(*args): return apply(_BetterMUD.region_AddExistingLogic,args)
    def DelLogic(*args): return apply(_BetterMUD.region_DelLogic,args)
    def GetLogic(*args): return apply(_BetterMUD.region_GetLogic,args)
    def HasLogic(*args): return apply(_BetterMUD.region_HasLogic,args)
    def DoAction(*args): return apply(_BetterMUD.region_DoAction,args)
    def GetLogicAttribute(*args): return apply(_BetterMUD.region_GetLogicAttribute,args)
    def AddHook(*args): return apply(_BetterMUD.region_AddHook,args)
    def DelHook(*args): return apply(_BetterMUD.region_DelHook,args)
    def Hooks(*args): return apply(_BetterMUD.region_Hooks,args)
    def KillHook(*args): return apply(_BetterMUD.region_KillHook,args)
    def ClearHooks(*args): return apply(_BetterMUD.region_ClearHooks,args)
    def __repr__(self):
        return "<C region instance at %s>" % (self.this,)

class regionPtr(region):
    def __init__(self,this):
        _swig_setattr(self, region, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, region, 'thisown', 0)
        _swig_setattr(self, region,self.__class__,region)
_BetterMUD.region_swigregister(regionPtr)

class room(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, room, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, room, name)
    def __init__(self,*args):
        _swig_setattr(self, room, 'this', apply(_BetterMUD.new_room,args))
        _swig_setattr(self, room, 'thisown', 1)
    def __del__(self, destroy= _BetterMUD.delete_room):
        try:
            if self.thisown: destroy(self)
        except: pass
    def ID(*args): return apply(_BetterMUD.room_ID,args)
    def Name(*args): return apply(_BetterMUD.room_Name,args)
    def Description(*args): return apply(_BetterMUD.room_Description,args)
    def SetID(*args): return apply(_BetterMUD.room_SetID,args)
    def SetName(*args): return apply(_BetterMUD.room_SetName,args)
    def SetDescription(*args): return apply(_BetterMUD.room_SetDescription,args)
    def Region(*args): return apply(_BetterMUD.room_Region,args)
    def SetRegion(*args): return apply(_BetterMUD.room_SetRegion,args)
    def AddItem(*args): return apply(_BetterMUD.room_AddItem,args)
    def DelItem(*args): return apply(_BetterMUD.room_DelItem,args)
    def Items(*args): return apply(_BetterMUD.room_Items,args)
    def BeginItem(*args): return apply(_BetterMUD.room_BeginItem,args)
    def CurrentItem(*args): return apply(_BetterMUD.room_CurrentItem,args)
    def NextItem(*args): return apply(_BetterMUD.room_NextItem,args)
    def IsValidItem(*args): return apply(_BetterMUD.room_IsValidItem,args)
    def SeekItem(*args): return apply(_BetterMUD.room_SeekItem,args)
    def AddCharacter(*args): return apply(_BetterMUD.room_AddCharacter,args)
    def DelCharacter(*args): return apply(_BetterMUD.room_DelCharacter,args)
    def Characters(*args): return apply(_BetterMUD.room_Characters,args)
    def BeginCharacter(*args): return apply(_BetterMUD.room_BeginCharacter,args)
    def CurrentCharacter(*args): return apply(_BetterMUD.room_CurrentCharacter,args)
    def NextCharacter(*args): return apply(_BetterMUD.room_NextCharacter,args)
    def IsValidCharacter(*args): return apply(_BetterMUD.room_IsValidCharacter,args)
    def SeekCharacter(*args): return apply(_BetterMUD.room_SeekCharacter,args)
    def AddPortal(*args): return apply(_BetterMUD.room_AddPortal,args)
    def DelPortal(*args): return apply(_BetterMUD.room_DelPortal,args)
    def Portals(*args): return apply(_BetterMUD.room_Portals,args)
    def BeginPortal(*args): return apply(_BetterMUD.room_BeginPortal,args)
    def CurrentPortal(*args): return apply(_BetterMUD.room_CurrentPortal,args)
    def NextPortal(*args): return apply(_BetterMUD.room_NextPortal,args)
    def IsValidPortal(*args): return apply(_BetterMUD.room_IsValidPortal,args)
    def SeekPortal(*args): return apply(_BetterMUD.room_SeekPortal,args)
    __swig_setmethods__["m_portalitr"] = _BetterMUD.room_m_portalitr_set
    __swig_getmethods__["m_portalitr"] = _BetterMUD.room_m_portalitr_get
    if _newclass:m_portalitr = property(_BetterMUD.room_m_portalitr_get,_BetterMUD.room_m_portalitr_set)
    def GetAttribute(*args): return apply(_BetterMUD.room_GetAttribute,args)
    def SetAttribute(*args): return apply(_BetterMUD.room_SetAttribute,args)
    def HasAttribute(*args): return apply(_BetterMUD.room_HasAttribute,args)
    def AddAttribute(*args): return apply(_BetterMUD.room_AddAttribute,args)
    def DelAttribute(*args): return apply(_BetterMUD.room_DelAttribute,args)
    def AddLogic(*args): return apply(_BetterMUD.room_AddLogic,args)
    def AddExistingLogic(*args): return apply(_BetterMUD.room_AddExistingLogic,args)
    def DelLogic(*args): return apply(_BetterMUD.room_DelLogic,args)
    def GetLogic(*args): return apply(_BetterMUD.room_GetLogic,args)
    def HasLogic(*args): return apply(_BetterMUD.room_HasLogic,args)
    def DoAction(*args): return apply(_BetterMUD.room_DoAction,args)
    def GetLogicAttribute(*args): return apply(_BetterMUD.room_GetLogicAttribute,args)
    def AddHook(*args): return apply(_BetterMUD.room_AddHook,args)
    def DelHook(*args): return apply(_BetterMUD.room_DelHook,args)
    def Hooks(*args): return apply(_BetterMUD.room_Hooks,args)
    def KillHook(*args): return apply(_BetterMUD.room_KillHook,args)
    def ClearHooks(*args): return apply(_BetterMUD.room_ClearHooks,args)
    def __repr__(self):
        return "<C room instance at %s>" % (self.this,)

class roomPtr(room):
    def __init__(self,this):
        _swig_setattr(self, room, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, room, 'thisown', 0)
        _swig_setattr(self, room,self.__class__,room)
_BetterMUD.room_swigregister(roomPtr)

class GameWrap(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, GameWrap, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, GameWrap, name)
    def FindPlayerOnlinePart(*args): return apply(_BetterMUD.GameWrap_FindPlayerOnlinePart,args)
    def FindPlayerOnlineFull(*args): return apply(_BetterMUD.GameWrap_FindPlayerOnlineFull,args)
    def FindPlayerPart(*args): return apply(_BetterMUD.GameWrap_FindPlayerPart,args)
    def FindPlayerFull(*args): return apply(_BetterMUD.GameWrap_FindPlayerFull,args)
    def HasPlayer(*args): return apply(_BetterMUD.GameWrap_HasPlayer,args)
    def Running(*args): return apply(_BetterMUD.GameWrap_Running,args)
    def ShutDown(*args): return apply(_BetterMUD.GameWrap_ShutDown,args)
    def GetTime(*args): return apply(_BetterMUD.GameWrap_GetTime,args)
    def ResetTime(*args): return apply(_BetterMUD.GameWrap_ResetTime,args)
    def DoAction(*args): return apply(_BetterMUD.GameWrap_DoAction,args)
    def AddActionRelative(*args): return apply(_BetterMUD.GameWrap_AddActionRelative,args)
    def AddActionAbsolute(*args): return apply(_BetterMUD.GameWrap_AddActionAbsolute,args)
    def Characters(*args): return apply(_BetterMUD.GameWrap_Characters,args)
    def BeginCharacter(*args): return apply(_BetterMUD.GameWrap_BeginCharacter,args)
    def CurrentCharacter(*args): return apply(_BetterMUD.GameWrap_CurrentCharacter,args)
    def NextCharacter(*args): return apply(_BetterMUD.GameWrap_NextCharacter,args)
    def IsValidCharacter(*args): return apply(_BetterMUD.GameWrap_IsValidCharacter,args)
    def CharacterTemplates(*args): return apply(_BetterMUD.GameWrap_CharacterTemplates,args)
    def BeginCharacterTemplate(*args): return apply(_BetterMUD.GameWrap_BeginCharacterTemplate,args)
    def CurrentCharacterTemplate(*args): return apply(_BetterMUD.GameWrap_CurrentCharacterTemplate,args)
    def NextCharacterTemplate(*args): return apply(_BetterMUD.GameWrap_NextCharacterTemplate,args)
    def IsValidCharacterTemplate(*args): return apply(_BetterMUD.GameWrap_IsValidCharacterTemplate,args)
    def Items(*args): return apply(_BetterMUD.GameWrap_Items,args)
    def BeginItem(*args): return apply(_BetterMUD.GameWrap_BeginItem,args)
    def CurrentItem(*args): return apply(_BetterMUD.GameWrap_CurrentItem,args)
    def NextItem(*args): return apply(_BetterMUD.GameWrap_NextItem,args)
    def IsValidItem(*args): return apply(_BetterMUD.GameWrap_IsValidItem,args)
    def ItemTemplates(*args): return apply(_BetterMUD.GameWrap_ItemTemplates,args)
    def BeginItemTemplate(*args): return apply(_BetterMUD.GameWrap_BeginItemTemplate,args)
    def CurrentItemTemplate(*args): return apply(_BetterMUD.GameWrap_CurrentItemTemplate,args)
    def NextItemTemplate(*args): return apply(_BetterMUD.GameWrap_NextItemTemplate,args)
    def IsValidItemTemplate(*args): return apply(_BetterMUD.GameWrap_IsValidItemTemplate,args)
    def Rooms(*args): return apply(_BetterMUD.GameWrap_Rooms,args)
    def BeginRoom(*args): return apply(_BetterMUD.GameWrap_BeginRoom,args)
    def CurrentRoom(*args): return apply(_BetterMUD.GameWrap_CurrentRoom,args)
    def NextRoom(*args): return apply(_BetterMUD.GameWrap_NextRoom,args)
    def IsValidRoom(*args): return apply(_BetterMUD.GameWrap_IsValidRoom,args)
    def Regions(*args): return apply(_BetterMUD.GameWrap_Regions,args)
    def BeginRegion(*args): return apply(_BetterMUD.GameWrap_BeginRegion,args)
    def CurrentRegion(*args): return apply(_BetterMUD.GameWrap_CurrentRegion,args)
    def NextRegion(*args): return apply(_BetterMUD.GameWrap_NextRegion,args)
    def IsValidRegion(*args): return apply(_BetterMUD.GameWrap_IsValidRegion,args)
    def Portals(*args): return apply(_BetterMUD.GameWrap_Portals,args)
    def BeginPortal(*args): return apply(_BetterMUD.GameWrap_BeginPortal,args)
    def CurrentPortal(*args): return apply(_BetterMUD.GameWrap_CurrentPortal,args)
    def NextPortal(*args): return apply(_BetterMUD.GameWrap_NextPortal,args)
    def IsValidPortal(*args): return apply(_BetterMUD.GameWrap_IsValidPortal,args)
    def Accounts(*args): return apply(_BetterMUD.GameWrap_Accounts,args)
    def BeginAccount(*args): return apply(_BetterMUD.GameWrap_BeginAccount,args)
    def CurrentAccount(*args): return apply(_BetterMUD.GameWrap_CurrentAccount,args)
    def NextAccount(*args): return apply(_BetterMUD.GameWrap_NextAccount,args)
    def IsValidAccount(*args): return apply(_BetterMUD.GameWrap_IsValidAccount,args)
    def __init__(self,*args):
        _swig_setattr(self, GameWrap, 'this', apply(_BetterMUD.new_GameWrap,args))
        _swig_setattr(self, GameWrap, 'thisown', 1)
    def __del__(self, destroy= _BetterMUD.delete_GameWrap):
        try:
            if self.thisown: destroy(self)
        except: pass
    def __repr__(self):
        return "<C GameWrap instance at %s>" % (self.this,)

class GameWrapPtr(GameWrap):
    def __init__(self,this):
        _swig_setattr(self, GameWrap, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, GameWrap, 'thisown', 0)
        _swig_setattr(self, GameWrap,self.__class__,GameWrap)
_BetterMUD.GameWrap_swigregister(GameWrapPtr)


