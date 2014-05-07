#ifndef __KTD3D11DEVICE_HPP__
#define __KTD3D11DEVICE_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/NonCopyable.hpp>
#include <kT/Graphics/GraphicsDevice/GraphicsDevice.hpp>
#include <kT/Math/Size.hpp>

#include "D3D11Shader.hpp"
#include "D3D11HardwareBuffer.hpp"
#include "D3D11InputLayout.hpp"
#include "D3D11DeviceTypes.hpp"

#if defined(KT_DEBUG)
#include <string>
#endif

struct ID3D11Device;

namespace kT
{
	class D3D11ImmediateContext;

    class KT_API D3D11Device: public kT::NonCopyable
    {
        public:

            D3D11Device(
				kT::GraphicsDevice<kTD3D11DeviceTemplateListLineTypes>::ProcessingMethod processingMethod = kT::GraphicsDevice<kTD3D11DeviceTemplateListLineTypes>::HardwareProcessing,
				bool debugFlag = false);

            ~D3D11Device();

            D3D11Texture* CreateTexture(
                Uint32 bindFlags,// Flagged combination of Texture::Type
                PixelFormat::Format format,
				const kT::Sizeui32& size,
				const void* texDataPtr = 0,
				bool generateMipMapsCaps = true
			);

            D3D11HardwareBuffer* CreateBuffer(
                kT::Uint32 bindFlags,// Flagged combination of HardwareBuffer::Type
                D3D11HardwareBuffer::Usage usage,
                Uint32 cpuAccessRight,
                Uint32 elementSize,
                Uint32 numElements,
                const void* data );

            D3D11Shader* CreateShader(
                D3D11Shader::ShaderType shaderType,
                D3D11Shader::ShaderProfile shaderProfile,
                void* shaderSource,
                size_t sourceSize,
                const char* entryPoint );

            D3D11InputLayout* CreateLayout(
                const D3D11Shader* vertexShader,
                const InputLayoutDesc& inputLayoutDesc );

            ID3D11Device* GetHandle() const {return myDevice;}

            UINT GetFeatureLevel() const { return myFeatureLevel; }

            kT::GraphicsDevice<kTD3D11DeviceTemplateListLineTypes>::ProcessingMethod GetProcessingMethod() const {return myProcessingMethod;}

            D3D11ImmediateContext* GetImmediateContext() const {return myImmediateContext;}

#if defined(KT_DEBUG)
            void SetName( const std::string& name );
#endif

        protected:

            ID3D11Device* myDevice;
            kT::GraphicsDevice<kTD3D11DeviceTemplateListLineTypes>::ProcessingMethod myProcessingMethod;

            D3D11ImmediateContext* myImmediateContext;
            UINT myFeatureLevel;
    };
}

#endif /* __KTD3D11DEVICE_HPP__ */