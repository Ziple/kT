/**
 * \file OGL3Device/OGL3Texture.hpp
 * \author Damien Hilloulin (ziple)
 * \date 16/04/2009
 */
#ifndef __KTOGL3TEXTURE_HPP__
#define __KTOGL3TEXTURE_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/NonCopyable.hpp>
#include <kT/Core/Types.hpp>
#include <kT/Math/Size.hpp>
#include <kT/Graphics/GraphicsDevice/Texture.hpp>
#include <kT/Graphics/PixelFormat.hpp>

#include <GL/glew.h>

#if defined(KT_DEBUG)
#include <string>
#endif

namespace kT
{
    class OGL3Device;

    class KT_API OGL3Texture: public NonCopyable
	{
		public:

			OGL3Texture(
				OGL3Device* device,
                Uint32 bindFlags,
                PixelFormat::Format format,
				const kT::Sizeui32& size,
				const void* texDataPtr = 0,
				bool generateMipMapsCaps = true
			);

			~OGL3Texture();

			inline const kT::Sizeui32& GetSize() const {return mySize;}

			inline GLuint GetHandle() {return myHandle;}
			
		protected:

            GLuint myHandle;
            GLenum myTarget;

			kT::Sizeui32 mySize;
	};

}

#endif /* __KTOGL3TEXTURE_HPP__ */
