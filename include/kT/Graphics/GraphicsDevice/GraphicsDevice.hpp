/**
 * \file Graphics/GraphicsDevice/GraphicsDevice.hpp
 * \author Damien Hilloulin (ziple)
 * \date 28/02/2009
 * \brief Contains the definition of the kT::GraphicsDevice interface.
 */
#ifndef __KTGRAPHICSDEVICE_HPP__
#define __KTGRAPHICSDEVICE_HPP__

/**
 * \defgroup ktgfxrenderer_module kT::GraphicsDevice
 * \brief This module contains the interface of graphics renderers.
 */

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>
#include <kT/Math/Size.hpp>

#include "../PixelFormat.hpp"
#include "Texture.hpp"
#include "HardwareBuffer.hpp"
#include "Shader.hpp"
#include "ImplementationForwardDeclarations.hpp"

namespace kT
{
    //forward declarations
    class Window;
    //

    /**
     * \ingroup ktgfxrenderer_module
     * \brief Defines the fonctionnality implemented by all the devices.
     *
     * A GraphicsDevice just take care of creation of the resources. To make
     * draw operations see kT::GraphicsContext .
     */
	kTGraphicsDeviceTemplateListDef
    class KT_API GraphicsDevice
    {
        public:

            /**
             * \ingroup ktgfxrenderer_module
             * \brief Rendering input processing method.
             */
            enum ProcessingMethod
            {
                HardwareProcessing = 0,///< Full hardware acceleration
                SoftwareProcessing = 1,///< Software processing.
                GenericDriverProcessing  = 2 ///< Uses a reference driver.
            };

            /**
             * \brief Creates a texture.
             * \param textureType The type of texture to create.
             * \param textureUsage Texture usage.
             * \param format Texel format of the texture.
             * \param width Width of the texture.
             * \param height Texture height.
             * \param depth Depth of the 3D texture, not used for other textures
             * types.
             * \param texels A pointer to the texels (a NULL pointer will just result
             * in the allocation of the required memory).
             * \return a pointer to the texture or NULL if error.
             */
            virtual ImplTexture* CreateTexture(
				Uint32 bindFlags,// Flagged combination of Texture::Type
                PixelFormat::Format format,
				const kT::Sizeui32& size,
				const void* texDataPtr = 0,
				bool generateMipMapsCaps = true
				) = 0;

            /**
             * \brief Creates a new index buffer.
             * \param type Type of buffer (constant/vertex/index buffer).
             * \param usage Usage of the buffer.
             * \param cpuRights CPU-access rights to give.
             * \param size Size in bytes of the buffer.
             * \param data Data to fill the buffer with.
             * \return NULL if a new index buffer can't be allocated.
             */
			virtual ImplHardwareBuffer* CreateBuffer(
				kT::Uint32 bindFlags,
                typename HardwareBuffer<kTGraphicsDeviceTemplateList>::Usage usage,
                Uint32 cpuRights,
                Uint32 elementSize,
                Uint32 numElements,
                const void* data
                ) = 0;

            virtual ImplShader* CreateShader(
                typename Shader<kTGraphicsDeviceTemplateList>::ShaderType shaderType,
                typename Shader<kTGraphicsDeviceTemplateList>::ShaderProfile shaderProfile,
                void* shaderSource,
                size_t sourceSize,
                const char* entryPoint );

            /**
             * \brief Creates an new input layout.
             * \param elements The elements composing the input layout.
             * \param n Number of elements composing the input layout.
             * \return NULL if the layout can't be validated against the active shader.
             */
            virtual ImplInputLayout* CreateInputLayout(
				const ImplShader* vertexShader,
                const InputLayoutDesc& inputLayoutDesc
				) = 0;

            /**
             * \brief Creates a new deferred context.
             */
            virtual ImplDeferredContext* CreateDeferredContext() = 0;

            /**
             * \brief Returns the immediate context.
             */
            virtual ImplImmediateContext* GetImmediateContext() = 0;
    };
}

#endif /* __KTGRAPHICSDEVICE_HPP__ */
