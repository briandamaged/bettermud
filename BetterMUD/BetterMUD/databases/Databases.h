// MUD Programming
// Ron Penton
// (C)2003
// Databases.h - This file contains the base database definitions
// 
// 


#ifndef BETTERMUDDATABASES_H
#define BETTERMUDDATABASES_H

#include <map>
#include <vector>
#include "../entities/Entity.h"
#include "../Exception.h"


namespace BetterMUD
{

template< typename entity, typename container  >
class Database
{
public:
    typename container::iterator begin()     { return m_container.begin(); }
    typename container::iterator end()       { return m_container.end(); }
    virtual entityid findname( const std::string& p_name ) = 0;

    virtual entity& get( entityid p_id ) = 0;
    virtual entity& create( entityid p_id ) = 0;

    size_t size() { return m_container.size() - 1; }

    entity& LoadEntity( std::istream& p_stream )
    {
        // load the ID first:
        entityid id;
        std::string temp;
        p_stream >> temp >> id;

        // create the entity
        // load or create the entity
        entity& e = create( id );

        // load it from the stream
        e.Load( p_stream );

        // eat up the whitespace
        p_stream >> std::ws;

        return e;
    }

    void SaveEntity( std::ostream& p_stream, entity& p_entity )
    {
        // save the ID first:
        p_stream << "[ID]                    " << p_entity.ID() << "\n";

        // save the entity and give extra space for the next one
        p_entity.Save( p_stream );
    }

    void LoadDirectory( const std::string& p_dir )
    {
        std::ifstream dir( std::string( p_dir + "manifest" ).c_str(), std::ios::binary );
        dir >> std::ws;

        std::string filename;
        // for each file in the directory
        while( dir.good() )
        {
            dir >> filename >> std::ws;
            LoadFile( p_dir + filename );
        }
    }

    void LoadFile( const std::string& p_file )
    {
        std::string filename = p_file + ".data";
        std::ifstream f( filename.c_str(), std::ios::binary );
        f >> std::ws;

        // load all entities in the file
        while( f.good() )
            LoadEntity( f );
    }


    void Purge() { m_container.clear(); }

protected:
    container m_container;
};  // end class Database














// ----------------------------------------------------------------------------
//  vector-based database for fast O(1) lookups.
// ----------------------------------------------------------------------------
template< typename entity >
class VectorDatabase : public Database< entity, std::vector<entity> >
{
public:
    typedef          std::vector<entity> container;
    typedef typename container::iterator iterator;

    bool isvalid( entityid p_id )
    {
        return p_id < this->m_container.size() && p_id != 0;
    }

    entity& get( entityid p_id )
    {
        if( p_id >= this->m_container.size() || p_id == 0 )
            throw Exception( "Out of bounds error in vector database" );

        if( this->m_container[p_id].ID() == 0 )
            throw Exception( "Invalid Item in vector database" );

        return this->m_container[p_id];
    }

    entity& create( entityid p_id )
    {
        if( this->m_container.size() <= p_id )
            this->m_container.resize( p_id + 1 );

        this->m_container[p_id].SetID( p_id );
        return this->m_container[p_id];
    }

    entityid findname( const std::string& p_name )
    {
        typename container::iterator itr = this->m_container.begin();
        stringmatchfull matcher( p_name );

        while( itr != this->m_container.end() )
        {
            if( matcher( itr->Name() ) )
                return itr->ID();
            ++itr;
        }
        return 0;
    }

};  // end class VectorDatabase


// ----------------------------------------------------------------------------
//  map-based database for fast O(log n) lookups.
// ----------------------------------------------------------------------------
template< typename entity >
class MapDatabase : public Database< entity, std::map<entityid, entity> >
{
public:
    typedef          std::map<entityid, entity> container;
    typedef typename container::iterator        iterator;

    typename container::iterator begin()     { return this->m_container.begin(); }
    typename container::iterator end()       { return this->m_container.end(); }

    bool isvalid( entityid p_id )
    {
        return this->m_container.find( p_id ) != this->m_container.end();
    }

    entity& get( entityid p_id )
    {
        typename container::iterator itr = this->m_container.find( p_id );
        if( itr == this->m_container.end() )
            throw Exception( "Out of bounds error in map database" );

        return itr->second;
    }

    entity& create( entityid p_id )
    {
        entity& e = this->m_container[p_id];
        e.SetID( p_id );
        return e;
    }

    void erase( entityid p_id )
    {
        typename container::iterator itr = this->m_container.find( p_id );
        this->m_container.erase( itr );
    }

    entityid FindOpenID()
    {
        if( this->m_container.size() == 0 )
            return 1;

        if( this->m_container.size() == this->m_container.rbegin()->first )
            return this->m_container.size() + 1;

        entityid openid = 0;
        entityid previous = 0;
        typename container::iterator itr = this->m_container.begin();

        while( !openid )
        {
            if( itr->first != previous + 1 )
                openid = previous + 1;
            else
                previous = itr->first;
            ++itr;
        }

        return openid;
    }


    entityid findname( const std::string& p_name )
    {
        typename container::iterator itr = this->m_container.begin();
        stringmatchfull matcher( p_name );

        while( itr != this->m_container.end() )
        {
            if( matcher( itr->second.Name() ) )
                return itr->first;

            ++itr;
        }

        return 0;
    }


};  // end class MapDatabase




// ----------------------------------------------------------------------------
//  This is a dual template/instance database that keeps a vector of templates
//  and a map of instances.
// ----------------------------------------------------------------------------
template< typename entity, typename templateentity >
class TemplateInstanceDatabase
{
public:
    typedef VectorDatabase<templateentity> templates;
    typedef MapDatabase<entity> instances;
    typedef typename std::set<entityid> cleanup;

    typename instances::iterator begin()     { return m_instances.begin(); }
    typename instances::iterator end()       { return m_instances.end(); }
    typename templates::iterator begintemplates()     { return m_templates.begin(); }
    typename templates::iterator endtemplates()       { return m_templates.end(); }

    entity& get( entityid p_id )
    {
        if( m_cleanup.find( p_id ) != m_cleanup.end() )
            throw Exception( "Template Instance Database: Cleaned Up Item Reference!" );
        return m_instances.get( p_id );
    }

    size_t size()   { return m_instances.size(); }
    size_t sizetemplates() { return m_templates.size(); }

    templateentity& gettemplate( entityid p_id )
    {
        return m_templates.get( p_id );
    }

    entityid generate( entityid p_template )
    {
        // find an open ID, and create an entity at that ID
        entityid id = m_instances.FindOpenID();
        entity& e = m_instances.create(id);

        // copy the template over into the new item
        e.LoadTemplate( m_templates.get( p_template ) );
        return id;
    }

    void erase( entityid p_id )
    {
        m_cleanup.insert( p_id );
    }

    void Cleanup()
    {
        typename cleanup::iterator itr = m_cleanup.begin();
        while( itr != m_cleanup.end() )
        {
            cleanup::iterator current = itr++;
            entity& e = m_instances.get( *current );
            //if( e.Ref() == 0 )
            //{
                m_instances.erase( *current );
                m_cleanup.erase( current );
            //}
        }
    }

    entityid findname( const std::string& p_name )
    {
        return m_instances.findname( p_name );
    }


    void LoadEntityTemplate( std::istream& p_stream )
    {
        m_templates.LoadEntity( p_stream );
    }

    void SaveEntityTemplate( std::ostream& p_stream, entity& p_entity )
    {
        m_templates.SaveEntity( p_stream, p_entity );
    }

    void LoadEntity( std::istream& p_stream )
    {
        m_instances.LoadEntity( p_stream );
    }

    void SaveEntity( std::ostream& p_stream, entity& p_entity )
    {
        m_instances.SaveEntity( p_stream, p_entity );
    }

    void Purge() 
    { 
        m_templates.Purge(); 
        m_instances.Purge();
    }

    void LoadFile( const std::string& p_file )
    {
        m_instances.LoadFile( p_file );
    }

    bool isvalid( entityid p_id )
    {
        return (m_cleanup.find( p_id ) == m_cleanup.end()) &&
                m_instances.isvalid( p_id );
    }

protected:
    templates m_templates;
    instances m_instances;
    cleanup m_cleanup;
};  // end class TemplateInstanceDatabase


}   // end namespace BetterMUD


#endif
