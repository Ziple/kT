#include <kT/Graphics/OGL3Device/OGL3PixelFormat.hpp>

#include <kT/Graphics/PixelFormat.hpp>

namespace kT
{
    GLint OGL3Format::GetOGL3Format( PixelFormat::Format format )
    {
        static GLint lookupTable[] = {
            0,
            GL_RGBA32F,
            GL_RGBA32I,
            GL_RGBA32UI,
            //
            GL_RGBA16F,
            GL_RGBA16I,
            GL_RGBA16UI,
            GL_RGBA16UI,
            //
            GL_RGBA8I,
            GL_RGBA8UI,
            GL_RGBA8UI,
            //
            GL_RGB32F,
            GL_RGB32I,
            GL_RGB32UI,
            //
            GL_RG32F,
            GL_RG32I,
            GL_RG32UI,
            //
            GL_RG16F,
            GL_RG16I,
            GL_RG16UI,
            GL_RG16UI,
            //
            GL_RG8I,
            GL_RG8UI,
            GL_RG8UI,
            //
            GL_R32F,
            GL_R32I,
            GL_R32UI,
            //
            GL_R16F,
            GL_R16I,
            GL_R16UI,
            GL_R16UI,
            //
            GL_R8I,
            GL_R8UI,
            GL_R8UI,
            //
            GL_DEPTH_COMPONENT,
            GL_DEPTH_STENCIL
        };

        return lookupTable[ format ];
    }

    GLint OGL3Format::GetOGL3InternalFormat( PixelFormat::Format format )
    {
        static GLenum lookupTable[] = {
            0,
            GL_RGBA,
            GL_RGBA,
            GL_RGBA,
            //
            GL_RGBA,
            GL_RGBA,
            GL_RGBA,
            GL_RGBA,
            //
            GL_RGBA,
            GL_RGBA,
            GL_RGBA,
            //
            GL_RGB,
            GL_RGB,
            GL_RGB,
            //
            GL_RG,
            GL_RG,
            GL_RG,
            //
            GL_RG,
            GL_RG,
            GL_RG,
            GL_RG,
            //
            GL_RG,
            GL_RG,
            GL_RG,
            //
            GL_RED,
            GL_RED,
            GL_RED,
            //
            GL_RED,
            GL_RED,
            GL_RED,
            GL_RED,
            //
            GL_RED,
            GL_RED,
            GL_RED,
            //
            GL_DEPTH_COMPONENT,
            GL_DEPTH_STENCIL
        };

        return lookupTable[ format ];
    }

    GLint OGL3Format::GetOGL3ComponentTypeFormat( PixelFormat::ComponentType comp )
    {
        static GLint lookupTable[] = {
            GL_BYTE,
            GL_UNSIGNED_BYTE,
            GL_SHORT,
            GL_UNSIGNED_SHORT,
            GL_INT,
            GL_UNSIGNED_INT,
            GL_HALF_FLOAT,
            GL_FLOAT,
            GL_DEPTH
        };

        return lookupTable[ comp ];
    }
}