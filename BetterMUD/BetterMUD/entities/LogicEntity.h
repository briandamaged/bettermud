// MUD Programming
// Ron Penton
// (C)2003
// LogicEntity.h - This file contains the Logic Entity class, which
//                 is an entity subclass which defines actions upon it
//                 governed by logic modules
// 
// 


#ifndef BETTERMUDLOGICENTITY_H
#define BETTERMUDLOGICENTITY_H

#include "Entity.h"
#include "../scripts/LogicCollection.h"

namespace BetterMUD
{


class LogicEntity : public Entity
{
public:
    bool AddLogic( const std::string& p_logic )    // name of logic class
    {
        try
        {
            m_logic.Add( p_logic, m_id );
            return true;
        } catch( ... ) {}
        return false;
    }

    // add an existing logic module (entity assumes ownership)
    bool AddExistingLogic( Logic* p_logic )
    {
        try 
        { 
            m_logic.AddExisting( p_logic );
            return true;
        } catch( ... ) {}
        return false;
    }

    // delete a logic module
    bool DelLogic( const std::string& p_logic )
    {
        try
        {
            // go through all the hooks and unhook them
            ClearLogicHooks( p_logic );

            // delete the logic
            m_logic.Del( p_logic );
            return true;
        } catch( ... ) {}
        return false;
    }

    // get a pointer to an existing logic module
    Logic* GetLogic( const std::string& p_logic )
    {
        return m_logic.Get( p_logic );
    }

    // does this entity have a logic module named p_logic?
    bool HasLogic( const std::string& p_logic )
    {
        try 
        {
            return m_logic.Has( p_logic );
        }
        catch( ... ) {}
        return false;
    }

    // Report Actions:
    int DoAction( const Action& p_action )
    {
        return m_logic.DoAction( p_action );
    }

    int DoAction( 
        const std::string& p_act, 
        entityid p_data1 = 0, 
        entityid p_data2 = 0, 
        entityid p_data3 = 0, 
        entityid p_data4 = 0, 
        const std::string& p_data = "" )
    {
        return m_logic.DoAction( Action( p_act, p_data1, p_data2, p_data3, p_data4, p_data ) );
    }

    int GetLogicAttribute( 
        const std::string& p_logic,
        const std::string& p_attr )
    {
        return m_logic.Attribute( p_logic, p_attr );
    }

protected:
    LogicCollection m_logic;        // the logic module



// Hook system
public:
    typedef std::set<TimedAction*> actionhooks;
    typedef actionhooks::iterator hookitr;
    
    void AddHook( TimedAction* p_hook )     { m_hooks.insert( p_hook ); }
    void DelHook( TimedAction* p_hook )     { m_hooks.erase( p_hook ); }
    hookitr HooksBegin()                    { return m_hooks.begin(); }
    hookitr HooksEnd()                      { return m_hooks.end(); }
    size_t Hooks()                          { return m_hooks.size(); }


    void KillHook( const std::string& p_act, const std::string& p_stringdata )
    {
        using BasicLib::ParseWord;
        hookitr itr = HooksBegin();
        while( itr != HooksEnd() )
        {
            hookitr current = itr++;

            // unhook the event if it matches the parameters
            if( (*current)->actionevent.actiontype == p_act &&
                ParseWord( (*current)->actionevent.stringdata, 0 ) ==
                p_stringdata )
            {
                (*current)->Unhook();
            }
        }
    }

    // clear all the hooks
    void ClearHooks()
    {
        hookitr itr = HooksBegin();
        while( itr != HooksEnd() )
        {
            hookitr current = itr++;
            (*current)->Unhook();
        }
    }

    // this is called whenever a logic module is about to be destroyed,
    // which means that any actions hooked into this particular module must
    // be unhooked.
    void ClearLogicHooks( const std::string& p_logic )
    {
        // do a search to see if any actions operate on the given module
        hookitr itr = m_hooks.begin();
        while( itr != m_hooks.end() )
        {
            hookitr current = itr++;
            if( (*current)->actionevent.actiontype == "messagelogic" ||
                (*current)->actionevent.actiontype == "dellogic"  )
            {
                if( BasicLib::ParseWord( (*current)->actionevent.stringdata, 0 ) == p_logic )
                    // found a match, now unhook it.
                    (*current)->Unhook();
            }
        }
    }

protected:
    actionhooks m_hooks;

};  // end class LogicEntity



}   // end namespace BetterMUD


#endif
