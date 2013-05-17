// MUD Programming
// Ron Penton
// (C)2003
// SocketSet.h - This file defines a socket set, which will be used for
//               polling many sockets at the same time for activity.
//               It is essentially a select() wrapper.

#ifndef SOCKETSET_H
#define SOCKETSET_H


#include "BasicLib/BasicLib.h"
#include "SocketLibTypes.h"
#include "SocketLibSocket.h"
#include <set>

namespace SocketLib
{
    
    const int MAX = FD_SETSIZE;

    class SocketSet
    {
    public:
        SocketSet();
        void AddSocket( const Socket& p_sock );
        void RemoveSocket( const Socket& p_sock );
        
        inline int Poll( long p_time = 0 )
        {
            // this is the time value structure. It will determine how long
            // the select function will wait.
            struct timeval t = { 0, p_time * 1000 };

            // copy the set over into the activity set.
            m_activityset = m_set;

            // now run select() on the sockets.
            #ifdef WIN32
                return select( 0, &m_activityset, 0, 0, &t );
            #else
                if( m_socketdescs.size() == 0 ) return 0;
                return select( *(m_socketdescs.rbegin()) + 1, &m_activityset, 0, 0, &t );
            #endif
        }

        inline bool HasActivity( const Socket& p_sock )
        {
            return FD_ISSET( p_sock.GetSock(), &m_activityset ) != 0;
        }


    protected:

        // a set representing the socket descriptors.
        fd_set m_set;

        // this set will represent all the sockets that have activity on them.
        fd_set m_activityset;

        // this is only used for linux, since select() requires the largest
        // descriptor +1 passed into it. BLAH!
        #ifndef WIN32
            std::set<sock> m_socketdescs;
        #endif
    };

}   // end namespace SocketLib



#endif
