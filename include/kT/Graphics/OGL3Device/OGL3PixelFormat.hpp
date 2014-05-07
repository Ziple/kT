#ifndef __KTOGL3PIXELFORMAT_HPP__
#define __KTOGL3PIXELFORMAT_HPP__

#include <kT/Core/Build.hpp>

#include <GL/glew.h>

namespace kT
{
    namespace PixelFormat
    {
        enum Format;
        enum ComponentType;
    }

    class KT_API OGL3Format
    {
        public:

            static GLint GetOGL3DataFormat( PixelFormat::Format format );

            static GLint GetOGL3InternalFormat( PixelFormat::Format format );

            static GLint GetOGL3ComponentTypeFormat( PixelFormat::ComponentType comp ); 
    };
}

#endif /* __KTOGL3PIXELFORMAT_HPP__ */