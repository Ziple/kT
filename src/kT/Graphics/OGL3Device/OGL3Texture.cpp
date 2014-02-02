#include <kT/Graphics/OGL3Device/OGL3Texture.hpp>

#include <kT/Graphics/OGL3Device/OGL3PixelFormat.hpp>

namespace kT
{
    KT_API OGL3Texture::OGL3Texture(
				OGL3Device* device,
                Uint32 bindFlags,
                PixelFormat::Format format,
				const kT::Sizeui32& size,
				const void* texDataPtr,
				bool generateMipMapsCaps
			):
     myHandle(0),
     myTarget(0),
     mySize( size )
    {
        GLint oglFormat = OGL3Format::GetOGL3Format( format );

        if( size.Width == size.Height )
            myTarget = GL_TEXTURE_2D;
        else
            myTarget = GL_TEXTURE_RECTANGLE;

        glGenTextures( 1, &myHandle );
        glBindTexture( myTarget, myHandle );

        GLint dataFormat = OGL3Format::GetOGL3Format( format );
        auto formatdesc = PixelUtility::GetPixelFormatDescriptor(format);

        GLenum dataType = OGL3Format::GetOGL3ComponentTypeFormat( formatdesc.ComponentsDescriptors[0].Type );

        glTexImage2D( myTarget, 0, oglFormat, size.Width, size.Height, 0, dataFormat, dataType, texDataPtr );

        if( generateMipMapsCaps
            && (myTarget != GL_TEXTURE_RECTANGLE) )
            glGenerateMipmap( myTarget );
    }

    KT_API OGL3Texture::~OGL3Texture()
    {
        glDeleteTextures( 1, &myHandle );
    }
}