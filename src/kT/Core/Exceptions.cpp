#include <kT/Core/Exceptions.hpp>

#include <sstream>

namespace kT
{
    KT_API Exception::Exception( const std::string& description,
                                          const std::string& source,
                                          const std::string& file,
                                          unsigned int line )
    {
        std::ostringstream s1;
        s1<<line;
        std::string lineString = s1.str();

        myFullDescription = std::string( "Exception launched by " )
                            + source
                            + std::string( " at line " )
                            + lineString
                            + std::string( ": " )
                            + description;
    }
}