/**
 * \file Graphics/Image.hpp
 * \author Damien Hilloulin (ziple)
 * \date 07/08/2011
 * \brief Contains the definition of kT::Image providing image loading support.
 */
#ifndef __KTIMAGE_HPP__
#define __KTIMAGE_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>

#include "PixelFormat.hpp"

#include <string>

namespace kT
{
    /**
     * \ingroup ktgfxrenderer_module
     * \brief Provides image handling support. Loads *bmp, *.tga, *.png, *.jpg files.
     */
    class KT_API Image
    {
        public:

            /**
             * \brief Constructor.
             * \param format Format of the pixels in data.
             * \param width Width of the image in pixels.
             * \param height Height of the image in pixels.
             * \param data Pointer to the data (must NOT be deleted after: the data isn't copied!)
             */
            Image(
				PixelFormat::Format format = PixelFormat::Unknown,
				Uint32 width = 0,
				Uint32 height = 0 ,
				Uint8* data = 0 ):
             Format( format ),
             Width( width ),
             Height( height ),
             Data( data )
            {}

            /**
             * \brief Destructor.
             */
            ~Image()
            {
                delete[] Data;
            }

            /**
             * \brief Loads an image from file by using the according image handler.
             * \return A pointer to the created image.
             */
            static Image* LoadFromFile(
				const std::string& filename
				);

            PixelFormat::Format Format;///< Format of the image.
            Uint32 Width, Height;///< Height of the image.
            Uint8* Data;///< Data of the image.
    };
}

#endif /* __KTIMAGE_HPP__ */
