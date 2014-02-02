/**
 * \file Core/Strings.hpp
 * \author Damien Hilloulin (ziple)
 * \date 07/08/2011
 * \brief Contains helpers functions to manipulate strings.
 */
#ifndef __KTSTRINGS_HPP__
#define __KTSTRINGS_HPP__

#include <kT/Core/Build.hpp>

#include <string>
#include <sstream>  

namespace kT
{
    template<typename T>
    std::string toString( const T & Value )
    {
        std::ostringstream oss;
        oss << Value;
        return oss.str();
    }

    std::string KT_API toUpper( const std::string& str );

    std::string KT_API toLower( const std::string& str );
}

#endif /* __KTSTRINGS_HPP__ */