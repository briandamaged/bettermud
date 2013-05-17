// MUD Programming
// Ron Penton
// (C)2003
// ThreadLibMutex.h - Header for the thread mutex class.

#ifndef THREADLIBMUTEX_H
#define THREADLIBMUTEX_H

// ============================================================================
//  Include Files for the threading libraries
// ============================================================================
#ifdef WIN32                // windows95 and above
    #include <windows.h>
#else                       // linux
    #include <pthread.h>
#endif

#include <string>

namespace ThreadLib
{

    class Mutex
    {
    public:
        // ====================================================================
        // Description: Initialize the mutex object
        // ====================================================================
        Mutex()
        {
            #ifdef WIN32
                // use critical sections in windows; much faster
                InitializeCriticalSection( &m_mutex );
            #else
                pthread_mutex_init( &m_mutex, 0 );
            #endif
        }

        // ====================================================================
        // Description: Destroy the mutex object
        // ====================================================================
        ~Mutex()
        {
            #ifdef WIN32
                DeleteCriticalSection( &m_mutex );
            #else
                pthread_mutex_destroy( &m_mutex );
            #endif
        }

        // ====================================================================
        // Description: Wait for a lock, then hold the lock
        // ====================================================================
        inline void Lock()
        {
            #ifdef WIN32
                EnterCriticalSection( &m_mutex );
            #else
                pthread_mutex_lock( &m_mutex );
            #endif
        }

        // ====================================================================
        // Description: release the lock
        // ====================================================================
        inline void Unlock()
        {
            #ifdef WIN32
                LeaveCriticalSection( &m_mutex );
            #else
                pthread_mutex_unlock( &m_mutex );
            #endif
        }

    protected:
    // define the base mutex types
    #ifdef WIN32
        CRITICAL_SECTION m_mutex;
    #else
        pthread_mutex_t m_mutex;
    #endif

    };  // end class Mutex


}   // end namespace ThreadLib

#endif
