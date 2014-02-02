#include <kT/Graphics/OGL3Device/OGL3Context.hpp>
#include <kT/Graphics/OGL3Device/OGL.hpp>
#include <kT/Core/Exceptions.hpp>

#include <cstring>

namespace kT
{
    KT_API OGL3Context::OGL3Context(
                                    Window* window,
                                    OGL3Context* sharedWith,
                                    unsigned redBits,
                                    unsigned greenBits,
                                    unsigned blueBits,
                                    unsigned alphaBits,
                                    unsigned depth,
                                    unsigned stencil ):
     OGL3ContextImpl( window, sharedWith, redBits, greenBits, blueBits, alphaBits, depth, stencil )
    {
        MakeCurrent();
        if( glewInit() != GLEW_OK )
            kTLaunchException( Exception, "Unable to init Glew" );
    }

    bool KT_API OGL3Context::IsExtensionPresent( const char* extensionName ) const
    {
        const char *exts = (const char*)glGetString(GL_EXTENSIONS);

        while( *exts )
        {
            size_t len = strcspn( exts, " " );
            if( strlen( extensionName) == len && strncmp( extensionName, exts, len) == 0)
                return true;
            exts += len+1;
        }

        return false;
    }

}
