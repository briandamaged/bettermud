// MUD Programming
// Ron Penton
// (C)2003
// PythonWrappers.cpp - This file contains the python interfaces for bettermud accessors
// 
// 


#include "PythonWrappers.h"
#include "../../accessors/Accessors.h"

namespace BetterMUD
{

// include the SWIG-generated wrapper here, inside the namespace BetterMUD
#include "BetterMUD_wrap.cxx"

void InitPythonAccessors()
{
    init_BetterMUD();
}
    
}   // end namespace BetterMUD

