// MUD Programming
// Ron Penton
// (C)2003
// BasicLibTypes.h - This file contains the basic types


#ifndef BASICLIBTYPES_H
#define BASICLIBTYPES_H
#include <iostream>
#include <fstream>
#include <string>


namespace BasicLib
{

#ifdef WIN32
    #if _MSC_VER >= 1300
        #define GOODCOMPILER
    #else
        #define CRAPPYCOMPILER
    #endif
#endif

#ifdef __GNUC__
    #define GOODCOMPILER
#endif


// ============================================================
//  This defines the 64 bit datatype
// ============================================================

// ------------------------------
//  LINUX
// ------------------------------
#ifdef __GNUC__
    typedef long long int sint64;
    typedef unsigned long long int uint64;
#endif


// ------------------------------
//  Visual C++
// ------------------------------
#ifdef WIN32
    typedef __int64 sint64;
    typedef unsigned __int64 uint64;
#endif


typedef signed long int sint32;
typedef unsigned long int uint32;
typedef signed short int sint16;
typedef unsigned short int uint16;
typedef signed char sint8;
typedef unsigned char uint8;


const double pi = 3.1415926535897932384626433832795;







} // end namespace BasicLib


#endif

