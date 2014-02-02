#include <kT/Core/FileLogger.hpp>
#include <kT/Core/Exceptions.hpp>

namespace kT
{
    KT_API FileLogger::FileLogger( const std::string& file ):
     outputFile( file.c_str() )
    {
        if( !outputFile )
            kTLaunchException( kT::Exception, "Can't open the file!" );
    }

    KT_API FileLogger::~FileLogger()
    {
        outputFile.close();
    }

    void KT_API FileLogger::Log( Logger::MessageType msgType, const char* msg )
    {
        const char* prefixes[] = {"Info: ",
                            "Warning: ",
                            "Error: ",
                            "Critical error: ",
                            ""
                           };

        outputFile<<prefixes[msgType]<<msg<<std::endl;
    }
}
