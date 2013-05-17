// MUD Programming
// Ron Penton
// (C)2003
// PythonScript.h - This file contains python related helpers for implementing
//                  BetterMUD scripts
// 
// 


#include "PythonScript.h"

namespace BetterMUD
{



// ============================================================================
//  PythonCallable Functions
// ============================================================================
// This is a helper macro that will make the following Call functions easier to 
// use. It wraps around a call to something that returns a PyObject, and handles
// exceptions thrown within.
#define PYTHONCALL( CALL )                                                  \
    PythonObject r;                                                         \
    try{ r = CALL }                                                         \
    catch( ... ) {                                                          \
        PyErr_Print();                                                      \
        throw Exception( "Python Function Call Failed" );                   \
    }                                                                       \
    if( r.get() == 0 ) {                                                    \
        PyErr_Print();                                                      \
        throw Exception( "Python Function Call Failed" );                   \
    }                                                                       \
    return r;


PythonObject PythonCallable::Call( std::string p_name )
{
    PYTHONCALL( PyObject_CallMethodObjArgs( m_module.get(), StringToPy( p_name ).get(), NULL ); )
}

PythonObject PythonCallable::Call( std::string p_name, const PythonObject& p_arg1 )
{
    PYTHONCALL( PyObject_CallMethodObjArgs( m_module.get(), StringToPy( p_name ).get(), p_arg1.get(), NULL ); )
}

PythonObject PythonCallable::Call( std::string p_name, const PythonObject& p_arg1, const PythonObject& p_arg2 )
{
    PYTHONCALL( PyObject_CallMethodObjArgs( m_module.get(), StringToPy( p_name ).get(), p_arg1.get(), p_arg2.get(), NULL ); )
}

PythonObject PythonCallable::Call( std::string p_name, const PythonObject& p_arg1, const PythonObject& p_arg2, const PythonObject& p_arg3 )
{
    PYTHONCALL( PyObject_CallMethodObjArgs( m_module.get(), StringToPy( p_name ).get(), p_arg1.get(), p_arg2.get(), p_arg3.get(), NULL ); )
}

PythonObject PythonCallable::Call( std::string p_name, const PythonObject& p_arg1, const PythonObject& p_arg2, const PythonObject& p_arg3, const PythonObject& p_arg4 )
{
    PYTHONCALL( PyObject_CallMethodObjArgs( m_module.get(), StringToPy( p_name ).get(), p_arg1.get(), p_arg2.get(), p_arg3.get(), p_arg4.get(), NULL ); )
}

PythonObject PythonCallable::Call( std::string p_name, const PythonObject& p_arg1, const PythonObject& p_arg2, const PythonObject& p_arg3, const PythonObject& p_arg4, const PythonObject& p_arg5 )
{
    PYTHONCALL( PyObject_CallMethodObjArgs( m_module.get(), StringToPy( p_name ).get(), p_arg1.get(), p_arg2.get(), p_arg3.get(), p_arg4.get(), p_arg5.get(), NULL ); )
}

PythonObject PythonCallable::Call( std::string p_name, const PythonObject& p_arg1, const PythonObject& p_arg2, const PythonObject& p_arg3, const PythonObject& p_arg4, const PythonObject& p_arg5, const PythonObject& p_arg6 )
{
    PYTHONCALL( PyObject_CallMethodObjArgs( m_module.get(), StringToPy( p_name ).get(), p_arg1.get(), p_arg2.get(), p_arg3.get(), p_arg4.get(), p_arg5.get(), p_arg6.get(), NULL ); )
}




// ============================================================================
//  PythonModule Functions
// ============================================================================

void PythonModule::Load( const std::string& p_module )
{
    // load the module
    PythonObject p = PyImport_ImportModule( const_cast<char*>( p_module.c_str() ) );
    if( p.get() == 0 )
        throw Exception( "Couldn't load python module: " + p_module );

    m_module = p;
}

void PythonModule::Reload( SCRIPTRELOADMODE p_mode )
{
    // reload the module
    m_module = PyImport_ReloadModule( m_module.get() );

    // simply return if you want to leave the existing scripts as they are,
    // without actually updating them
    if( p_mode == LEAVEEXISTING )
        return;

    spawnlist::iterator itr = m_spawns.begin();
    while( itr != m_spawns.end() )
    {
        (*itr)->Reload();
        ++itr;
    }
}





PythonInstance* PythonModule::SpawnNew( const std::string p_str )
{
    try
    {
    // Get the class from the module:
    PythonObject c = PyObject_GetAttrString( m_module.get(), const_cast<char*>(p_str.c_str()) );
    
    // no good, throw an exception
    if( c.get() == 0 )
        throw Exception( "Could not find python class: " + p_str );

    // grab an instance of that class now:
    PythonObject i = PyInstance_New( c.get(), NULL, NULL );

    if( i.get() == 0 )
        throw Exception( "Could not create python class instance: " + p_str );

    PythonInstance* mod = new PythonInstance( i, this );

    if( !mod )  throw Exception( "Error allocating memory for python module" );

    // set the modules instance and parent pointer, and add it to my list.
    m_spawns.push_back( mod );

    return mod;
    }
    catch( Exception& e ) { throw; }
    catch( ... )        // catch any extra errors we didn't grab before
    {
        PyErr_Print();
        throw Exception( "Unknown error attempting to create class instance: " + p_str );
    }
}


void PythonModule::DeleteChild( PythonInstance* p_instance )
{
    m_spawns.erase( std::find( m_spawns.begin(), m_spawns.end(), p_instance ) );
}



// ============================================================================
//  PythonInstance Functions
// ============================================================================
PythonInstance::~PythonInstance()
{
    if( m_parent )
        m_parent->DeleteChild( this );
}

void PythonInstance::Reload()
{
    // get the name of the class you want to reload
    std::string clsname = m_module.GetNameOfClass();

    // get a new class object from the parent module
    PythonObject cls = PyObject_GetAttrString( 
        m_parent->get(), 
        const_cast<char*>(clsname.c_str()) );

    if( cls.get() == 0 )
        throw Exception( "Could not find python class: " + clsname );

    // set my class attribute to point to the new class functions (but not data)
    PyObject_SetAttrString( m_module.get(), "__class__", cls.get() );
}


void PythonInstance::Load( std::istream& p_stream )
{
    std::string str;
    std::string temp;
    bool done = false;

    // read in the "[DATA] tag:
    std::getline( p_stream, temp );

    // loop until you hit "[/DATA]"
    while( !done )
    {
        std::getline( p_stream, temp );
        if( temp == "[/DATA]" )
            done = true;
        else
            str += temp + "\n";
    }

    // send everything inbetween to the script
    Call( "LoadScript", StringToPy( str ) );
}

void PythonInstance::Save( std::ostream& p_stream )
{
    p_stream << "[DATA]\n";
    p_stream << StringFromPy( Call( "SaveScript" ) );
    p_stream << "[/DATA]\n";
}



// ============================================================================
//  PythonDatabase Functions
// ============================================================================
PythonDatabase::~PythonDatabase()
{
    modules::iterator itr = m_modules.begin();
    while( itr != m_modules.end() )
    {
        delete *itr;
        ++itr;
    }
}


void PythonDatabase::Load()
{
    std::string filename = m_directory + "manifest";
    std::ifstream manifest( filename.c_str(), std::ios::binary );
    manifest >> std::ws;

    while( manifest.good() )
    {
        std::string modulename;
        manifest >> modulename >> std::ws;
        Load( modulename );
    }
}


void PythonDatabase::AddModule( const std::string& p_module )
{
    Load( p_module );

    // write the new module name out to the manifest
    std::string filename = m_directory + "manifest";
    std::ofstream manifest( filename.c_str(), std::ios::binary | std::ios::app );
    manifest << "\n" << p_module << "\n";
}



void PythonDatabase::Load( const std::string& p_module )
{
    std::string modname = m_directory + p_module;

    // convert "/" or "\" to "." for proper module loading
    modname = BasicLib::SearchAndReplace( modname, "/", "." );
    modname = BasicLib::SearchAndReplace( modname, "\\", "." );

    PythonModule* mod = new PythonModule();
    if( !mod )  throw Exception( "Not enough memory to load python module" );

    try
    {
        mod->Load( modname );
        m_modules.push_back( mod );
    }
    catch( ... )
    {
        delete mod;
        throw;
    }
}

void PythonDatabase::Reload( const std::string& p_module, SCRIPTRELOADMODE p_mode )
{
    modules::iterator itr = m_modules.begin();
    while( itr != m_modules.end() )
    {
        if( (*itr)->Name() == p_module )
        {
            (*itr)->Reload( p_mode );
            return;
        }
        ++itr;
    }   

    // if we got this far, then the module doesn't exist, so load it
    Load( p_module );
}

PythonInstance* PythonDatabase::SpawnNew( const std::string p_str )
{
    modules::iterator itr = m_modules.begin();
    while( itr != m_modules.end() )
    {
        if( (*itr)->Has( p_str ) )
            return (*itr)->SpawnNew( p_str );
        ++itr;
    }   

    throw Exception( "Error: Cannot load module: " + p_str );
}


}   // end namespace BetterMUD