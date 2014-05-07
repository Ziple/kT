#include <kT/Graphics/OGL3Device/OGL3Texture.hpp>

#include <kT/Graphics/OGL3Device/OGL3PixelFormat.hpp>
#include <kT/Graphics/OGL3Device/OGL3Check.hpp>

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
        GLint oglFormat = OGL3Format::GetOGL3InternalFormat( format );

        if( size.Width == size.Height )
            myTarget = GL_TEXTURE_2D;
        else
            myTarget = GL_TEXTURE_RECTANGLE;

		ktOGL3Check( glGenTextures(1, &myHandle) );
		ktOGL3Check( glBindTexture(myTarget, myHandle) );

        GLint dataFormat = OGL3Format::GetOGL3DataFormat( format );
        auto formatdesc = PixelUtility::GetPixelFormatDescriptor(format);

        GLenum dataType = OGL3Format::GetOGL3ComponentTypeFormat( formatdesc.ComponentsDescriptors[0].Type );

		if (format == PixelFormat::DEPTH)
			dataType = GL_UNSIGNED_BYTE;
		else if (format == PixelFormat::DEPTH_STENCIL)
			dataType = GL_UNSIGNED_BYTE;

		// it seems that AMD drivers don't support sized types
		ktOGL3Check(glTexImage2D(myTarget, 0, dataFormat, size.Width, size.Height, 0, dataFormat, dataType, texDataPtr));

        if( generateMipMapsCaps
            && (myTarget != GL_TEXTURE_RECTANGLE) )
			ktOGL3Check( glGenerateMipmap(myTarget) );
    }

    KT_API OGL3Texture::~OGL3Texture()
    {
		ktOGL3Check( glDeleteTextures(1, &myHandle) );
    }
}