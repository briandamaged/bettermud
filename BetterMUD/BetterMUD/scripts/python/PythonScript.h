// MUD Programming
// Ron Penton
// (C)2003
// PythonScript.h - This file contains python related helpers for implementing
//                  BetterMUD scripts
// 
// 


#ifndef BETTERMUDPYTHONSCRIPT_H
#define BETTERMUDPYTHONSCRIPT_H

#include <list>
#include "../Script.h"

#include "PythonHelpers.h"


namespace BetterMUD
{

class PythonCallable
{
public:
    PythonCallable() : m_module( 0 ) {}
    PythonCallable( PythonObject& p_object ) : m_module( p_object ) {}

    // These are the call functions, which can accept from 0-4 python object 
    // parameters. I used overloading here because some systems don't support 
    // variable arguments at all, or poorly, etc. Lots of problems. Anyway,
    // if you need more than 4 arguments, feel free to just copy+paste, and add
    // another argument. Ah, the hacks we make for the sake of portability =)
    PythonObject Call( std::string p_name );
    PythonObject Call( std::string p_name, const PythonObject& p_arg1 );
    PythonObject Call( std::string p_name, const PythonObject& p_arg1, const PythonObject& p_arg2 );
    PythonObject Call( std::string p_name, const PythonObject& p_arg1, const PythonObject& p_arg2, const PythonObject& p_arg3 );
    PythonObject Call( std::string p_name, const PythonObject& p_arg1, const PythonObject& p_arg2, const PythonObject& p_arg3, const PythonObject& p_arg4 );
    PythonObject Call( std::string p_name, const PythonObject& p_arg1, const PythonObject& p_arg2, const PythonObject& p_arg3, const PythonObject& p_arg4, const PythonObject& p_arg5 );
    PythonObject Call( std::string p_name, const PythonObject& p_arg1, const PythonObject& p_arg2, const PythonObject& p_arg3, const PythonObject& p_arg4, const PythonObject& p_arg5, const PythonObject& p_arg6 );

    bool Has( const std::string& p_name ) const { return m_module.Has( p_name ); }
    PyObject* get() const { return m_module.get(); } 

protected:
    PythonObject m_module;
};




class PythonInstance;

// -----------------------------------------------------------------------
// This is a python script module, which will load up modules and return
// classes when needed. It is not safe to copy this class after you have 
// started creating class instances of it; and it this *is* a class 
// instance, do *NOT* copy it.
// -----------------------------------------------------------------------
class PythonModule : public PythonCallable
{
public:
    PythonModule() {};
    std::string Name() { return m_module.GetName(); }

    void Load( const std::string& p_module );
    void Reload( SCRIPTRELOADMODE p_mode );


    PythonInstance* SpawnNew( const std::string p_str );
    void DeleteChild( PythonInstance* p_instance );

// hide the copy constructor and the operator=, 
// so that nothing can copy this class.
private:
    PythonModule( const PythonModule& );
    PythonModule& operator=( const PythonModule& );

protected:
    typedef std::list<PythonInstance*> spawnlist;
    spawnlist m_spawns;
};




class PythonInstance : public PythonCallable
{
public:
    PythonInstance( 
        PythonObject p_instance,        // instance object 
        PythonModule* p_parent )        // pointer to parent
    : PythonCallable( p_instance ),
      m_parent( p_parent )  {}

    ~PythonInstance();
    std::string Name() { return m_module.GetNameOfClass(); }
        
    void Reload();

    // calls to load and save the script to disk
    // Load will automatically eat up any closing </DATA> tag
    // Save will automatically insert a closing </DATA> tag
    void Load( std::istream& p_stream );
    void Save( std::ostream& p_stream );


// hide the copy constructor and the operator=, 
// so that nothing can copy this class.
private:
    PythonInstance( const PythonInstance& );
    PythonInstance& operator=( const PythonInstance& );

protected:
    PythonModule* m_parent;
};



class PythonDatabase
{
public:
    PythonDatabase( const std::string& p_directory ) : m_directory( p_directory ) {}
    ~PythonDatabase();
    void Load();
    void AddModule( const std::string& p_module );
    void Reload( const std::string& p_module, SCRIPTRELOADMODE p_mode );
    PythonInstance* SpawnNew( const std::string p_str );

protected:
    void Load( const std::string& p_module );
    typedef std::list<PythonModule*> modules;
    modules m_modules;
    std::string m_directory;
};





}   // end namespace BetterMUD


#endif
