// MUD Programming
// Ron Penton
// (C)2003
// ThreadLib.cpp - Main code file for the thread library.
// This holds all of the main threading functions and structures, and includes
// the other synchronization object headers.


#include "ThreadLib.h"

namespace ThreadLib
{

    // ========================================================================
    //  This is the handle-map global, only used in Win32.
    // ========================================================================
    #ifdef WIN32
        std::map< DWORD, HANDLE > g_handlemap;
    #endif


    // ========================================================================
    // Description: This is a "dummy" thread function that will be used to
    //              transparently translate function pointers to whatever
    //              system the user is currently compiling on.
    // ========================================================================
    #ifdef WIN32
        DWORD WINAPI DummyRun( void* p_data )
    #else
        void* DummyRun( void* p_data )
    #endif
        {
            // convert the dummy data
            DummyData* data = (DummyData*)p_data;

            // run the function with the given data
            data->m_func( data->m_data );

            // now delete the data
            delete data;

            // and return 0.
            return 0;
        }


}   // end namespace ThreadLib
