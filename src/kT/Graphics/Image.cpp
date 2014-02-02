#include <kT/Graphics/Image.hpp>
#include <kT/Core/String.hpp>

#include "TGAImageHandler.hpp"

namespace kT
{
    Image* Image::LoadFromFile( const std::string& filename )
    {
        size_t pointPos = filename.find_last_of( '.' );
        if( pointPos != std::string::npos
            && pointPos + 1 <= filename.size() )
        {
            std::string fileExt = toUpper( filename.substr( pointPos + 1 ) );
            if( fileExt == std::string("BMP")
                || fileExt == std::string("DIB") )
                return 0;
            else if( fileExt == std::string("PNG") )
                return 0;
            else if( fileExt == std::string("TGA") )
                return TGAImageHandler::LoadFromFile( filename );
            else if( fileExt == std::string("JPG") )
                return 0;
            else
                return 0;
        }
        else
            return 0;
    }
}
