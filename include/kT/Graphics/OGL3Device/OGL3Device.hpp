#ifndef __KTOGL3DEVICE_HPP__
#define __KTOGL3DEVICE_HPP__

/**
 * \defgroup ktogl3device_module OGL3Device
 * \brief This module implements the OpenGL3 graphics renderer.
 */

#include <kT/Core/Build.hpp>
#include <kT/Graphics/GraphicsDevice/GraphicsDevice.hpp>

#include "OGL3Context.hpp"
#include "OGL3ImmediateContext.hpp"
#include "OGL3Texture.hpp"
#include "OGL3HardwareBuffer.hpp"
#include "OGL3InputLayout.hpp"
#include "OGL3DeviceTypes.hpp"

namespace kT
{
    class OGL3DeferredContext {};
    class OGL3SwapChain {};
    class OGL3RenderTarget {};
    class OGL3DepthStencilTarget {};
    class OGL3Program;

    /**
     * \ingroup ktogl3device_module
     */
	class KT_API OGL3Device: public kT::GraphicsDevice< kTOGL3DeviceTemplateListLineTypes >
    {
        public:

			typedef kT::GraphicsDevice<kTOGL3DeviceTemplateListLineTypes> Base;

            /**
             * \brief Constructor.
             */
            OGL3Device( OGL3Device::ProcessingMethod processingMethod = OGL3Device::HardwareProcessing );

            /**
             * \brief Destructor.
             */
            ~OGL3Device();

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
            OGL3Texture* CreateTexture( Texture::Type textureType,
                                               Texture::Usage textureUsage,
                                               PixelFormat::Format format,
                                               Uint32 width,
                                               Uint32 height,
                                               Uint32 depth,
                                               const void* texels
                                             );

            /**
             * \brief Creates a render target from a texture.
             * \return A pointer to the texture target or NULL if error.
             *
             * The texture must be in a suitable format (not a depth/stencil
             * texture), and have the RenderTextureUsage usage.
             */
            OGL3RenderTarget* CreateRenderTarget( OGL3Texture* texture,
                                                           Uint32 multisamplingLevel
                                                         );

            /**
             * \brief Creates a kT::SwapChain.
             * \return A pointer to the texture target or NULL if error.
             *
             * The texture must be in a suitable format (not a depth/stencil
             * texture), and have the RenderTextureUsage usage.
             */
            OGL3SwapChain* CreateSwapChain( Window* associatedWindow,
                PixelFormat::Format format,
                                                Uint32 width,
                                                Uint32 height,
                                                bool doubleBuffer = true,
                                                Uint32 multisamplingLevel = 0
                                              );

            /**
             * \brief Creates a depth/stencil target from a texture.
             * \return A pointer to the depth/stencil target or NULL if error.
             *
             * The texture must have a suitable format ( a depth/stencil compatible one).
             */
            OGL3DepthStencilTarget* CreateDepthStencilTarget( OGL3Texture* texture );

            /**
             * \brief Creates an new input layout.
             * \return NULL if the layout can't be validated against the active shader.
             */
            OGL3InputLayout* CreateInputLayout(
                OGL3Program* prog,
                const InputLayoutDesc& layoutDesc
                                                      );

            /**
             * \brief Creates a new index buffer.
             * \param type Type of buffer (constant/vertex/index buffer).
             * \param usage Usage of the buffer.
             * \param cpuRights CPU-access rights to give.
             * \param size Size in bytes of the buffer.
             * \param data Data to fill the buffer with.
             * \return NULL if a new index buffer can't be allocated.
             */
            OGL3HardwareBuffer* CreateBuffer( OGL3HardwareBuffer::Type type,
                                                  OGL3HardwareBuffer::Usage usage,
                                                       Uint32 cpuRights,
                                                       Uint32 elementSize,
                                                       Uint32 numElements,
                                                       const void* data
                                                      );

            /**
             * \brief Creates a new deferred context.
             */
            OGL3DeferredContext* CreateDeferredContext();

            /**
             * \brief Returns the immediate context.
             */
            OGL3ImmediateContext* GetImmediateContext();

        private:

            OGL3Context* myContext;
            OGL3ImmediateContext* myImmediateContext;
    };
}

#endif /* __KTOGL3DEVICE_HPP__ */
