// MUD Programming
// Ron Penton
// (C)2003
// ThreadLibFunctions.h - Contains all of the functions for use within
// the threading library

#ifndef THREADLIBFUNCTIONS_H
#define THREADLIBFUNCTIONS_H

// ============================================================================
//  Include Files for the threading libraries
// ============================================================================
#ifdef WIN32                // windows95 and above
    #include <windows.h>
    #include <map>
#else                       // linux
    #include <pthread.h>
    #include <unistd.h>
#endif

#include "ThreadException.h"

namespace ThreadLib
{

    // ========================================================================
    // define the standard thread function format, which takes a void* as its
    // parameter, and returns nothing
    // ========================================================================
    typedef void (*ThreadFunc)(void*);

    // ========================================================================
    //  Define the standard ThreadID datatype, depending on the system
    // ========================================================================
    #ifdef WIN32                // windows95 and above
        typedef DWORD ThreadID;
        extern std::map< DWORD, HANDLE > g_handlemap;
    #else                       // linux
        typedef pthread_t ThreadID;
    #endif


    // ========================================================================
    // Description: This is a "dummy" class that will be used to
    //              transparently translate function pointers to whatever
    //              system the user is currently compiling on. It is meant to
    //              be passed into the DummyRun function.
    // ========================================================================
    class DummyData
    {
    public:
        ThreadFunc m_func;
        void* m_data;
    };

    // ========================================================================
    // Description: This is a "dummy" thread function that will be used to
    //              transparently translate function pointers to whatever
    //              system the user is currently compiling on.
    // ========================================================================
    #ifdef WIN32
        DWORD WINAPI DummyRun( void* p_data );
    #else
        void* DummyRun( void* p_data );
    #endif


    // ========================================================================
    // Description: Creates a thread and returns its ID.
    // ========================================================================
    inline ThreadID Create( ThreadFunc p_func, void* p_param )
    {
        ThreadID t;
        // create a new dummy data block
        DummyData* data = new DummyData;
        data->m_func = p_func;
        data->m_data = p_param;

        #ifdef WIN32    // create a Win32 thread
            HANDLE h;
            h = CreateThread( NULL, 0, DummyRun, data, 0, &t );
            if( h != 0 )
            {
                // insert the handle into the handlemap
                g_handlemap[t] = h;
            }
        #else           // create a linux thread
            pthread_create( &t, 0, DummyRun, data );
        #endif

        if( t == 0 )
        {
            // delete the data first
            delete data;

            // throw an error
            throw Exception( CreationFailure );
        }
        return t;
    }

    // ========================================================================
    // Description: Get the ID of the current thread
    // ========================================================================
    inline ThreadID GetID()
    {
        #ifdef WIN32
            return GetCurrentThreadId();
        #else
            return pthread_self();
        #endif
    }


    // ========================================================================
    // Description: This waits for a thread to finish executing before 
    //              returning.
    // ========================================================================
    inline void WaitForFinish( ThreadID p_thread )
    {
        #ifdef WIN32
            // look up the handle and wait for the thread to finish
            WaitForSingleObject( g_handlemap[p_thread], INFINITE );

            // close the handle of the thread
            CloseHandle( g_handlemap[p_thread] );

            // remove the handle from the map
            g_handlemap.erase( p_thread );
        #else
            // "join" the thread. This essentially transfers control over to
            // the thread and waits for it to finish.
            pthread_join( p_thread, NULL );
        #endif
    }


    // ========================================================================
    // Description: This forcefully terminates a thread. Don't do this unless
    //              it is absolutely neccessary.
    // ========================================================================
    inline void Kill( ThreadID& p_thread )
    {
        #ifdef WIN32
            // terminate the thread
            TerminateThread( g_handlemap[p_thread], 0 );

            // close the handle of the thread
            CloseHandle( g_handlemap[p_thread] );

            // remove the handle from the map
            g_handlemap.erase( p_thread );
        #else
            // cancel the thread.
            pthread_cancel( p_thread );
        #endif
    }


    // ========================================================================
    // Description: This yields the thread to the operating system, and gives
    //              up its current timeslice.
    // ========================================================================
    inline void YieldThread( int p_milliseconds = 1 )
    {
        #ifdef WIN32
            Sleep( p_milliseconds );
        #else
            usleep( p_milliseconds * 1000 );
        #endif
    }




}   // end namespace ThreadLib


#endif
