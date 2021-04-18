*Windows build notes*

Windows build is setup to use Visual Studio 2017.

Build requires python 2.7
Set the envirognment variables
PYTHON to the 32 bit python path (C:\Python27)
PYTHON64 to the 64 bit python path (C:\Python27_64)

Note that by default python does not ship debug libs, building bettermud in debug
requires the debug python libs. Build them yourself or get them from the inernet.