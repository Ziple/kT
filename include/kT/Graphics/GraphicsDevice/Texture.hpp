/**
 * \file Graphics/GraphicsDevice/Texture.hpp
 * \author Damien Hilloulin (ziple)
 * \date 28/02/2009
 * \brief Contains the definition of the kT::Texture interface.
 */
#ifndef __KTTEXTURE_HPP__
#define __KTTEXTURE_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>

#include "../PixelFormat.hpp"

namespace kT
{
    /**
     * \ingroup ktgfxrenderer_module
     * \brief Interface for textures.
     *
     * A texture can be used for texturing but also to be a render-target.
     * There are several types of textures: 1D ones, 2D ones, cube maps (just 6 2D
     * textures), and 3D ones.
     */
    class KT_API Texture
    {
        public:

		/**
		 * \ingroup ktgfxrenderer_module
		 * \brief Enum identifying how the texture can be used: as a rendertarget or shader input
		 *
		 * Those are flags.
		 */
		enum Type
		{
			/**
			 * \brief The texture can be bound as an input of a shader
			 */
			ShaderInput = 1,

			/**
			 * \brief The texture can be used as a rendertarget.
			 */
			RenderTarget = 2,

			/**
			 * \brief The texture can be used as a depth stencil buffer
			 */
			DepthStencilBuffer = 4
		};

		/**
		 * \ingroup ktgfxrenderer_module
		 * \brief Enum identifying the usage of the texture.
		 */
		enum Usage
		{
			/**
			 * The texture is provided once.
			 * The CPU can't write into but can read from it.
			 */
			StaticUsage = 1,

			/**
			 * The texture is infrequently specified.
			 * The CPU can both read from and write into the texture.
			 */
			StreamUsage = 2,

			/**
			 * The texture is specified once or more times per frame.
			 * The CPU can read from and write into the texture.
			 */
			DynamicUsage = 3,
		};

		/**
		 * \ingroup ktgfxrenderer_module
		 * \brief Enum identifying the texture topology: wether it is a 1D texture or 2D, 3D, cubemap etc.
		 */
		enum Dimension
		{
			Texture1D = 1,      ///< A 1D texture.
			Texture2D = 2,      ///< A 2D texture.
			Texture3D = 3,      ///< A 3D texture.
			TextureCubeMap = 4,///< A cube map texture.
		};

            /**
             * \brief Detailed constructor.
             */
            Texture(
				Type textureType,
				Usage textureUsage,
                Dimension dimension,
				PixelFormat::Format pixelFormat,
				Uint32 width,
				Uint32 height,
				Uint32 depth,
				Uint32 numMipmaps
                      ):
             myTextureType( textureType ),
             myTextureUsage( textureUsage ),
             myDimension( dimension ),
             myPixelFormat( pixelFormat ),
             myWidth( width ),
             myHeight( height ),
             myDepth( depth ),
             myNumMipMaps( numMipmaps )
            {}

            /**
             * \brief Retrieves the pixel format of the texture.
             */
            inline PixelFormat::Format GetPixelFormat() const {return myPixelFormat;};

            /**
             * \brief Retrieves the type of texture the texture is.
             */
            inline Type GetTextureType() const {return myTextureType;}

            /**
             * \brief Retrieves the usage of the texture.
             */
            inline Usage GetTextureUsage() const {return myTextureUsage;}

            /**
             * \brief Retrieves the width of the texture.
             */
            inline Uint32 GetWidth() const {return myWidth;};

            /**
             * \brief Retrieves the height of the texture.
             */
            inline Uint32 GetHeight() const {return myHeight;};

            /**
             * \brief Retrieves the depth of the texture.
             * \return depth of the 3D texture, 1 for others textures, 0 if not created.
             */
            inline Uint32 GetDepth() const {return myDepth;};

            /**
             * \brief Retrives the number of faces composing the texture.
             * \return 6 for cubemaps textures, 1 for the others.
             */
            inline Uint32 GetNumberOfFaces() const { return myDimension == TextureCubeMap ? 6 : 1 ;};

            /**
             * \brief Returns the number of mipmaps for the texture.
             */
            inline Uint32 GetNumberOfMipmaps() const {return myNumMipMaps;};

            /**
             * \brief Generates n mipmaps for the texture.
             */
            virtual void GenerateMipMaps() = 0;

        protected:

            Type myTextureType;
            Usage myTextureUsage;
            Dimension myDimension;
            PixelFormat::Format myPixelFormat;
            Uint32 myWidth, myHeight, myDepth;
            Uint32 myNumMipMaps;
    };
}

#endif /* __KTTEXTURE_HPP__ */
