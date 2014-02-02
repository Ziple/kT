#include <kT/Graphics/D3D11Device/D3D11Device.hpp>
#include <kT/Graphics/D3D11Device/D3D11Shader.hpp>
#include <kT/Graphics/D3D11Device/D3D11ImmediateContext.hpp>
#include <kT/Graphics/D3D11Device/D3D11Texture.hpp>

#include <kT/Core/Exceptions.hpp>

namespace kT
{
    KT_API D3D11Device::D3D11Device(
		kT::GraphicsDevice<kTD3D11DeviceTemplateListLineTypes>::ProcessingMethod processingMethod,
		bool debugFlag ):
     myDevice( 0 ),
     myProcessingMethod( processingMethod ),
     myImmediateContext( 0 )
    {
        D3D_DRIVER_TYPE driverTypes[] = {
            D3D_DRIVER_TYPE_HARDWARE,
            D3D_DRIVER_TYPE_WARP,
            D3D_DRIVER_TYPE_REFERENCE
        };

		UINT flags = debugFlag ? D3D11_CREATE_DEVICE_DEBUG : 0;
		ID3D11DeviceContext* imDev = 0;

		HRESULT hr = 0;
		for( size_t i = 0; i < 3; i++ )
		{
			hr = D3D11CreateDevice( NULL, driverTypes[i], NULL, flags, NULL, 0, D3D11_SDK_VERSION, &myDevice, &myFeatureLevel, &imDev );
			if( !FAILED(hr) )
				break;
		}

        if( FAILED(hr) )
            kTLaunchException( kT::Exception, "Error while trying to create the D3D11 device" );

		myImmediateContext = new D3D11ImmediateContext( imDev );
    }

    KT_API D3D11Device::~D3D11Device()
    {
        delete myImmediateContext;
        myDevice->Release();
    }

    KT_API D3D11Texture* D3D11Device::CreateTexture(
        Uint32 bindFlags,
        PixelFormat::Format format,
		const kT::Sizeui32& size,
		const void* texDataPtr,
		bool generateMipMapsCaps )
    {
        return new D3D11Texture( myDevice, bindFlags, format, size, texDataPtr, generateMipMapsCaps );
    }

    KT_API  D3D11HardwareBuffer* D3D11Device::CreateBuffer(
        kT::Uint32 type,
        D3D11HardwareBuffer::Usage usage,
        Uint32 cpuAccessRight,
        Uint32 elementSize,
        Uint32 numElements,
        const void* data )
    {
        return new D3D11HardwareBuffer( myDevice, type, usage, cpuAccessRight, elementSize, numElements, data );
    }

    KT_API D3D11Shader* D3D11Device::CreateShader( D3D11Shader::ShaderType shaderType,
                                       D3D11Shader::ShaderProfile shaderProfile,
                                       void* shaderSource,
                                       size_t sourceSize,
                                       const char* entryPoint )
    {
        return new D3D11Shader( myDevice, shaderType, shaderProfile, shaderSource, sourceSize, entryPoint );
    }

    KT_API D3D11InputLayout* D3D11Device::CreateLayout(
                const D3D11Shader* vertexShader,
                const InputLayoutDesc& inputLayoutDesc )
    {
        return new D3D11InputLayout(
            myDevice,
            vertexShader->GetShaderByteCode()->GetBufferPointer(),
            vertexShader->GetShaderByteCode()->GetBufferSize(),
            inputLayoutDesc );
    }

#if defined(KT_DEBUG)
    void KT_API D3D11Device::SetName( const std::string& name )
    {
        myDevice->SetPrivateData( WKPDID_D3DDebugObjectName, name.length(), name.c_str() );
    }
#endif
}