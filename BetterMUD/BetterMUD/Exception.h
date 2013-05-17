// MUD Programming
// Ron Penton
// (C)2003
// Exception.h - This is the exception class, due to certain compilers not 
//               supporting string messages properly
// 
// 


#ifndef BETTERMUDEXCEPTION_H
#define BETTERMUDEXCEPTION_H

#include <stdexcept>
#include <string>

namespace BetterMUD
{

class Exception : public std::exception
{
public:
    Exception( std::string p_err = "UNDEFINED ERROR" )
        : m_err( p_err ) {}

    ~Exception() throw() {}

    std::string GetError()      { return m_err; }

protected:
    std::string m_err;
};


}   // end namespace BetterMUD


#endif
