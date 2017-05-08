# Compiler is G++
CXX = g++

#MUDLib directory
MUDLIBDIR = ../Libraries
SOCKETLIBDIR = $(MUDLIBDIR)/SocketLib
THREADLIBDIR = $(MUDLIBDIR)/ThreadLib
BASICLIBDIR  = $(MUDLIBDIR)/BasicLib
BETTERMUDDIR = ./BetterMUD

# libraries
LIBS = -lpthread -ldl -lutil

PYTHONDIR = /usr/include/python2.7

ACCESSORS = $(BETTERMUDDIR)/accessors
DATABASES = $(BETTERMUDDIR)/databases
ENTITIES  = $(BETTERMUDDIR)/entities
NETWORK   = $(BETTERMUDDIR)/network
SCRIPTS   = $(BETTERMUDDIR)/scripts
PYSCRIPTS = $(BETTERMUDDIR)/scripts/python

# flags
CFLAGS = -I$(PYTHONDIR) -I$(MUDLIBDIR) -Xlinker -export-dynamic -g

libs: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) $(SOCKETLIBDIR)/*.cpp -c;
	$(CXX) $(CFLAGS) $(THREADLIBDIR)/*.cpp -c;
	$(CXX) $(CFLAGS) $(BASICLIBDIR)/*.cpp -c;

bettermud: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) *.cpp -c;
	$(CXX) $(CFLAGS) $(BETTERMUDDIR)/*.cpp -c;
	$(CXX) $(CFLAGS) $(ACCESSORS)/*.cpp -c;
	$(CXX) $(CFLAGS) $(DATABASES)/*.cpp -c;
	$(CXX) $(CFLAGS) $(ENTITIES)/*.cpp -c;
	$(CXX) $(CFLAGS) $(NETWORK)/*.cpp -c;
	$(CXX) $(CFLAGS) $(SCRIPTS)/*.cpp -c;
	$(CXX) $(CFLAGS) $(PYSCRIPTS)/*.cpp -c;


main: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) *.cpp -c;

link: $(wildcard *.cpp)
	$(CXX) $(CFLAGS) *.o /usr/lib64/libpython2.7.so $(LIBS) -o bettermud
