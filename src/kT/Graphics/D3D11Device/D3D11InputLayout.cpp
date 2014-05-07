#include <kT/Graphics/D3D11Device/D3D11InputLayout.hpp>
#include <kT/Graphics/D3D11Device/D3D11Device.hpp>
#include <kT/Graphics/D3D11Device/D3D11Format.hpp>
#include <kT/Graphics/D3D11Device/D3D11Shader.hpp>
#include <kT/Core/Exceptions.hpp>

#include <D3D11.h>

namespace kT
{
	KT_API D3D11InputLayout::D3D11InputLayout(
		D3D11Device* device,
		D3D11Shader* shader,
		const InputLayoutDesc& inputLayoutDesc):
		D3D11InputLayout(
			device->GetHandle(),
			shader->GetShaderByteCode()->GetBufferPointer(),
			shader->GetShaderByteCode()->GetBufferSize(),
			inputLayoutDesc
		)
	{
	}

    KT_API D3D11InputLayout::D3D11InputLayout(
        ID3D11Device* device,
        const void* shaderCode,
        size_t shaderCodeSize,
        const InputLayoutDesc& inputLayoutDesc ):
     InputLayout( inputLayoutDesc ),
     myInputLayout( 0 )
    {
        D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[ inputLayoutDesc.numElements ];
        for( size_t i = 0; i < inputLayoutDesc.numElements; i++ )
        {
            layout[i].InputSlot = inputLayoutDesc.inputDesc[i].inputSlot;
            layout[i].SemanticName = inputLayoutDesc.inputDesc[i].role;
            layout[i].Format = kT::D3D11Format::GetDXGIFormat( inputLayoutDesc.inputDesc[i].format );
            layout[i].InputSlotClass = static_cast< D3D11_INPUT_CLASSIFICATION >( inputLayoutDesc.inputDesc[i].inputClass );
            layout[i].InstanceDataStepRate = inputLayoutDesc.inputDesc[i].instanceDataStepRate;
            layout[i].SemanticIndex = inputLayoutDesc.inputDesc[i].index;
            layout[i].AlignedByteOffset = inputLayoutDesc.inputDesc[i].byteOffset;
        }

        HRESULT hr = device->CreateInputLayout(
            layout,
            inputLayoutDesc.numElements,
            shaderCode,
            shaderCodeSize,
            &myInputLayout );

        delete[] layout;

        if( FAILED(hr) )
            kTLaunchException( kT::Exception, "Can't create the input layout" );
    }

    KT_API D3D11InputLayout::~D3D11InputLayout()
    {
        myInputLayout->Release();
    }

#if defined(KT_DEBUG)
    void KT_API D3D11InputLayout::SetName( const std::string& name )
    {
        myInputLayout->SetPrivateData( WKPDID_D3DDebugObjectName, name.length(), name.c_str() );
    }
#endif
}
