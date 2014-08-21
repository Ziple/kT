#ifndef __KTOGL3PIXELFORMAT_HPP__
#define __KTOGL3PIXELFORMAT_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Graphics/PixelFormat.hpp>

#include <GL/glew.h>

namespace kT
{
    class KT_API OGL3Format
    {
        public:

            static GLint GetOGL3DataFormat( PixelFormat::Format format );

            static GLint GetOGL3InternalFormat( PixelFormat::Format format );

            static GLint GetOGL3ComponentTypeFormat( PixelFormat::ComponentType comp ); 
    };
}

#endif /* __KTOGL3PIXELFORMAT_HPP__ */