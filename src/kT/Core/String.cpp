#include <kT/Core/String.hpp>

#include <cctype>

namespace kT
{
    std::string KT_API toUpper( const std::string& str )
    {
        std::string ret = str;
        for( std::string::iterator it = ret.begin(); it != ret.end(); it++ )
            *it = toupper( *it );

        return ret;
    }

    std::string KT_API toLower( const std::string& str )
    {
        std::string ret = str;
        for( std::string::iterator it = ret.begin(); it != ret.end(); it++ )
            *it = tolower( *it );

        return ret;
    }
}