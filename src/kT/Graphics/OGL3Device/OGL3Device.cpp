#include <kT/Graphics/OGL3Device/OGL3Device.hpp>
#include <kT/Graphics/OGL3Device/OGL3HardwareBuffer.hpp>
#include <kT/Graphics/OGL3Device/OGL.hpp>
#include <kT/Core/Exceptions.hpp>

#define BUFFER_OFFSET( i ) ((char*)(0+ (i) ))

namespace kT
{
    KT_API OGL3Device::OGL3Device( GraphicsDevice::ProcessingMethod processingMethod ):
     myContext( 0 ),
     myImmediateContext( 0 )
    {
        myContext = new OGL3Context();
        myImmediateContext = new OGL3ImmediateContext( myContext );
    }

     KT_API OGL3Device::~OGL3Device()
     {
         delete myImmediateContext;
         delete myContext;
     }

    KT_API OGL3InputLayout* OGL3Device::CreateInputLayout(
        OGL3Program* prog,
        const InputLayoutDesc& desc )
    {
        return new OGL3InputLayout( prog, desc );
    };

    KT_API OGL3HardwareBuffer* OGL3Device::CreateBuffer( OGL3HardwareBuffer::Type type,
                                                                OGL3HardwareBuffer::Usage usage,
                                                                        Uint32 cpuRights,
                                                                        Uint32 elementSize,
                                                                        Uint32 numElements,
                                                                        const void *data
                                                                      )
    {
        return new OGL3HardwareBuffer( this, type, usage, cpuRights, elementSize, numElements, data );
    }

    OGL3Texture* OGL3Device::CreateTexture( Texture::Type textureType,
                                            Texture::Usage textureUsage,
                                            PixelFormat::Format format,
                                            Uint32 width,
                                            Uint32 height,
                                            Uint32 depth,
                                            const void* texels
                                            )
    {
        return 0;
    }

    OGL3RenderTarget* OGL3Device::CreateRenderTarget( OGL3Texture* texture,
                                                    Uint32 multisamplingLevel
                                                    )
    {
        return 0;
    }

    OGL3SwapChain* OGL3Device::CreateSwapChain( Window* associatedWindow,
        PixelFormat::Format format,
                                                Uint32 width,
                                                Uint32 height,
                                                bool doubleBuffer,
                                                Uint32 multisamplingLevel
                                                )
    {
        return 0;
    }

    OGL3DepthStencilTarget* OGL3Device::CreateDepthStencilTarget( OGL3Texture* texture )
    {
        return 0;
    }

    OGL3DeferredContext* OGL3Device::CreateDeferredContext()
    {
        return 0;
    }

    OGL3ImmediateContext* OGL3Device::GetImmediateContext()
    {
        return 0;
    }
}
