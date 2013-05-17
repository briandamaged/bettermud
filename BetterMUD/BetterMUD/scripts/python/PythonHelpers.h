// MUD Programming
// Ron Penton
// (C)2003
// PythonHelpers.h - This file has several helper functions for use with
//                   python scripts.
// 
// 


#ifndef BETTERMUDPYTHONHELPERS_H
#define BETTERMUDPYTHONHELPERS_H

#include "../../Exception.h"
#include "../../entities/Entity.h"
#include "Python.h"
#include "PythonWrappers.h"

namespace BetterMUD
{

inline void InitPython()
{
    Py_Initialize();

    // import "" into the system path, because on some system's it's not there
    // by default (*boggle*)
    PyRun_SimpleString( "import sys\n"
                        "sys.path.append(\'\')\n" );

    // initialize the BetterMUD accessors now
    InitPythonAccessors();
}

class PythonObject
{
public:
    PythonObject( PyObject* p_object = 0 ) : m_object( p_object ) {}
    PythonObject( const PythonObject& p_object ) : m_object( p_object.m_object ) 
    {
        Py_XINCREF( m_object );
    }
    ~PythonObject() 
    {  
        Py_XDECREF( m_object ); 
    }
    
    PythonObject& operator=( const PythonObject& p_object )
    {
        Py_XDECREF( m_object );
        m_object = p_object.m_object;
        Py_XINCREF( m_object );
        return *this;
    }

    PythonObject& operator=( PyObject* p_object )
    {
        Py_XDECREF( m_object );
        m_object = p_object;
        return *this;
    }

    PyObject* get() const { return m_object; }

    bool Has( const std::string& p_name ) const 
    {
        return (bool)PyObject_HasAttrString( m_object, const_cast<char*>(p_name.c_str()) );
    }

    std::string GetNameOfClass();
    std::string GetName();

protected:
    PyObject* m_object;
};




inline PythonObject IntToPy( int p_obj )            { return PyInt_FromLong( p_obj ); }
inline PythonObject LongToPy( long p_obj )          { return PyInt_FromLong( p_obj ); }
inline PythonObject EntityToPy( entityid p_obj )    { return PyInt_FromLong( p_obj ); }
inline PythonObject LongLongToPy( BasicLib::sint64 p_obj ) { return PyLong_FromLongLong( p_obj ); }
inline PythonObject DoubleToPy( double p_obj )      { return PyFloat_FromDouble( p_obj ); }
inline PythonObject FloatToPy( float p_obj )        { return PyFloat_FromDouble( p_obj ); }
inline PythonObject StringToPy( std::string p_obj ) { return PyString_FromString( const_cast<char*>(p_obj.c_str()) ); }

inline long LongFromPy( const PythonObject& p_obj )       { return PyInt_AsLong( p_obj.get() ); }
inline entityid EntityFromPy( const PythonObject& p_obj ) { return PyInt_AsLong( p_obj.get() ); }
inline BasicLib::sint64 LongLongFromPy( const PythonObject& p_obj ) { return PyLong_AsLongLong( p_obj.get() ); }
inline double DoubleFromPy( const PythonObject& p_obj )   { return PyFloat_AsDouble( p_obj.get() ); }
inline std::string StringFromPy( const PythonObject& p_obj ) { return PyString_AsString( p_obj.get() ); }


}   // end namespace BetterMUD

#endif

