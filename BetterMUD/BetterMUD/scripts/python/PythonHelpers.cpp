// MUD Programming
// Ron Penton
// (C)2003
// PythonHelpers.cpp - This file has several helper functions for use with
//                     python scripts.
// 
// 


#include "PythonHelpers.h"

namespace BetterMUD
{


std::string PythonObject::GetNameOfClass()
{
    PythonObject cls = PyObject_GetAttrString( m_object, "__class__" );
    PythonObject name = PyObject_GetAttrString( cls.get(), "__name__" );
    return StringFromPy( name );
}

std::string PythonObject::GetName()
{
    PythonObject name = PyObject_GetAttrString( m_object, "__name__" );
    return StringFromPy( name );
}


}   // end namespace BetterMUD

