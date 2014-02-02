/**
 * \file Graphics/PixelFormat.hpp
 * \author Damien Hilloulin (ziple)
 * \date 28/02/2009
 * \brief Contains the definition of the kT::PixelFormat and helpers about pixel formats.
 */
#ifndef __KTPIXELFORMAT_HPP__
#define __KTPIXELFORMAT_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>

#include <cstddef>

namespace kT
{
    namespace PixelFormat
    {
        /**
         * \ingroup ktgfxrenderer_module
         * \brief Enumerates all the possible pixel formats.
         *
         * These formats can be used in the creation of textures or framebuffers,
         * but not all the formats can be used for every usage. For example a compressed
         * format can't be used in a logical buffer of a framebuffer, nor
         * _RGBA32_FLOAT for a depth-stencil texture.
         */
        enum Format
        {
            Unknown = 0,
            RGBA32_FLOAT,
            RGBA32_INT,
            RGBA32_UINT,
            //
            RGBA16_FLOAT,
            RGBA16_INT,
            RGBA16_UINT,
            RGBA16_UNORM,
            //
            RGBA8_INT,
            RGBA8_UINT,
            RGBA8_UNORM,
            //
            RGB32_FLOAT,
            RGB32_INT,
            RGB32_UINT,
            //
            RG32_FLOAT,
            RG32_INT,
            RG32_UINT,
            //
            RG16_FLOAT,
            RG16_INT,
            RG16_UINT,
            RG16_UNORM,
            //
            RG8_INT,
            RG8_UINT,
            RG8_UNORM,
            //
            R32_FLOAT,
            R32_INT,
            R32_UINT,
            //
            R16_FLOAT,
            R16_INT,
            R16_UINT,
            R16_UNORM,
            //
            R8_INT,
            R8_UINT,
            R8_UNORM,
            // depth-stencil textures formats
            DEPTH,
            DEPTH_STENCIL,

            COUNT
        };

        /**
         * \ingroup ktgfxrenderer_module
         * \brief Flags defining some on/off properties of pixel formats.
         */
        enum Flags
        {
            Alpha = 1,    ///< The pixel format contains an alpha channel.
            Depth = 4,        ///< Correct format for a depth texture.
            DepthStencil = 8,///< Correct format for a depth-stencil texture.
            Compressed = 16,   ///< Compressed pixel format.
            Float = 32,         ///< This is a floating point format.
            Norm = 64,///< The data is interpreted in shaders as in the range of [0,1] for unsigned types or [-1,1] for signed types.
        };

        /**
         * \ingroup ktgfxrenderer_module
         * \brief Describes the type of a component.
         */
        enum ComponentType
        {
            ByteComponent = 0,         ///< The component is one byte (8 bits).
            UnsignedByteComponent = 1, ///< The component is one unsigned byte.
            ShortComponent = 2,        ///< The component is one short integer (16 bits).
            UnsignedShortComponent = 3,///< The component is one unsigned short integer (16 bits).
            IntComponent = 4,          ///< The component is one integer (32 bits).
            UnsignedComponent = 5,     ///< The component is one unsigned integer (32 bits).
            Float16Component = 6,      ///< The format is composed of half floats (16 bits).
            Float32Component = 7,      ///< The format is composed of floats (32 bits).
            Depth24Component = 8       ///< The component is a depth component ie a 24 bits normalised float 
        };
    }

    /**
     * \ingroup ktgfxrenderer_module
     * \brief Describes a pixel component.
     */
    struct KT_API PixelComponentFormatDescriptor
    {
        const char* Name;
        PixelFormat::ComponentType Type;

        /**
         * \return the size of the coomponent given its type.
         */
        size_t GetComponentSize() const;
    };

    /**
     * \ingroup ktgfxrenderer_module
     * \brief Describes a pixel format (components, total size etc...).
     */
    struct KT_API PixelFormatDescriptor
    {
        PixelFormat::Format DescribedFormat;
        Uint8 Capacities;
        size_t ComponentsNumber;
        const PixelComponentFormatDescriptor* ComponentsDescriptors;

        /**
         * \brief Returns the size of one pixel in bytes.
         */
        size_t GetSize() const;
    };

    /**
     * \ingroup ktgfxrenderer_module
     * \brief Some utility fonctions for managing pixels.
     *
     * Provides some functions for packing/unpacking pixels, getting niformations about it
     */
    class KT_API PixelUtility
    {
        public:

            static const PixelFormatDescriptor& GetPixelFormatDescriptor(
				PixelFormat::Format format
				);

        protected:

            static PixelFormatDescriptor ourDescriptors[ PixelFormat::COUNT ];
    };
}

#endif /* __KTPIXELFOMAT_HPP__ */
