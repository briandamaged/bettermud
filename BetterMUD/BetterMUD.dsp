# Microsoft Developer Studio Project File - Name="BetterMUD" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=BetterMUD - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BetterMUD.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BetterMUD.mak" CFG="BetterMUD - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BetterMUD - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "BetterMUD - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BetterMUD - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib python22.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "BetterMUD - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ  /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib python22.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "BetterMUD - Win32 Release"
# Name "BetterMUD - Win32 Debug"
# Begin Group "BetterMUD"

# PROP Default_Filter ""
# Begin Group "accessors"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BetterMUD\accessors\AccessorMacros.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\accessors\Accessors.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\accessors\AccountAccessor.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\accessors\AccountAccessor.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\accessors\CharacterAccessor.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\accessors\CharacterAccessor.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\accessors\GameAccessor.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\accessors\GameAccessor.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\accessors\ItemAccessor.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\accessors\ItemAccessor.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\accessors\PortalAccessor.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\accessors\PortalAccessor.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\accessors\RegionAccessor.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\accessors\RegionAccessor.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\accessors\RoomAccessor.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\accessors\RoomAccessor.h
# End Source File
# End Group
# Begin Group "databases"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BetterMUD\databases\AccountDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\databases\AccountDatabase.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\databases\AllDatabases.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\databases\CharacterDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\databases\CharacterDatabase.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\databases\CommandDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\databases\CommandDatabase.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\databases\Databases.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\databases\Databases.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\databases\ItemDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\databases\ItemDatabase.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\databases\LogicDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\databases\LogicDatabase.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\databases\PortalDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\databases\PortalDatabase.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\databases\RegionDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\databases\RegionDatabase.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\databases\RoomDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\databases\RoomDatabase.h
# End Source File
# End Group
# Begin Group "entities"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BetterMUD\entities\Account.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\entities\Account.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\entities\Action.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\entities\Action.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\entities\Attributes.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\entities\Character.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\entities\Character.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\entities\DataEntity.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\entities\Entity.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\entities\Item.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\entities\Item.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\entities\LogicEntity.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\entities\Portal.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\entities\Portal.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\entities\Region.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\entities\Region.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\entities\Room.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\entities\Room.h
# End Source File
# End Group
# Begin Group "network"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BetterMUD\network\BetterTelnet.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\network\BetterTelnet.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\network\TelnetGame.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\network\TelnetGame.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\network\TelnetLogon.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\network\TelnetLogon.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\network\TelnetMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\network\TelnetMenu.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\network\TelnetReporter.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\network\TelnetReporter.h
# End Source File
# End Group
# Begin Group "scripts"

# PROP Default_Filter ""
# Begin Group "Python"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BetterMUD\scripts\python\PythonCommand.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\scripts\python\PythonHelpers.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\scripts\python\PythonHelpers.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\scripts\python\PythonLogic.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\scripts\python\PythonLogic.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\scripts\python\PythonScript.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\scripts\python\PythonScript.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\scripts\python\PythonWrappers.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\scripts\python\PythonWrappers.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\BetterMUD\scripts\Command.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\scripts\CPPCommand.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\scripts\CPPCommands.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\scripts\Logic.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\scripts\LogicCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\scripts\LogicCollection.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\scripts\Script.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\BetterMUD\Exception.h
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\Game.cpp
# End Source File
# Begin Source File

SOURCE=.\BetterMUD\Game.h
# End Source File
# End Group
# Begin Group "SocketLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Libraries\SocketLib\Connection.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\SocketLib\ConnectionHandler.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\SocketLib\ConnectionManager.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\SocketLib\ListeningManager.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\SocketLib\SocketLib.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\SocketLib\SocketLibErrors.cpp
# End Source File
# Begin Source File

SOURCE=..\Libraries\SocketLib\SocketLibErrors.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\SocketLib\SocketLibSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\Libraries\SocketLib\SocketLibSocket.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\SocketLib\SocketLibSystem.cpp
# End Source File
# Begin Source File

SOURCE=..\Libraries\SocketLib\SocketLibSystem.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\SocketLib\SocketLibTypes.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\SocketLib\SocketSet.cpp
# End Source File
# Begin Source File

SOURCE=..\Libraries\SocketLib\SocketSet.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\SocketLib\Telnet.cpp
# End Source File
# Begin Source File

SOURCE=..\Libraries\SocketLib\Telnet.h
# End Source File
# End Group
# Begin Group "ThreadLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Libraries\ThreadLib\ThreadException.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\ThreadLib\ThreadLib.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\ThreadLib\ThreadLibFunctions.cpp
# End Source File
# Begin Source File

SOURCE=..\Libraries\ThreadLib\ThreadLibFunctions.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\ThreadLib\ThreadLibMutex.h
# End Source File
# End Group
# Begin Group "BasicLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Libraries\BasicLib\BasicLib.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\BasicLib\BasicLibFunctions.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\BasicLib\BasicLibLogger.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\BasicLib\BasicLibRandom.cpp
# End Source File
# Begin Source File

SOURCE=..\Libraries\BasicLib\BasicLibRandom.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\BasicLib\BasicLibString.cpp
# End Source File
# Begin Source File

SOURCE=..\Libraries\BasicLib\BasicLibString.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\BasicLib\BasicLibTime.cpp
# End Source File
# Begin Source File

SOURCE=..\Libraries\BasicLib\BasicLibTime.h
# End Source File
# Begin Source File

SOURCE=..\Libraries\BasicLib\BasicLibTypes.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\BetterMUD.cpp
# End Source File
# End Target
# End Project
