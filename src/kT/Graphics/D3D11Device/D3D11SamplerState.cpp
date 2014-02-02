#include <kT/Graphics/D3D11Device/D3D11SamplerState.hpp>
#include <kT/Core/Exceptions.hpp>

#include <d3d11.h>

namespace kT
{
	KT_API D3D11SamplerState::D3D11SamplerState(
		ID3D11Device* device,
		const TextureSamplerDesc& desc )
	{
		D3D11_SAMPLER_DESC rdesc;
		rdesc.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)desc.AddressU;
		rdesc.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)desc.AddressV;
		rdesc.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)desc.AddressW;
		memcpy( rdesc.BorderColor, &desc.BorderColor.x, sizeof(float) * 4 );
		rdesc.ComparisonFunc = (D3D11_COMPARISON_FUNC)desc.ComparisonFunc;
		rdesc.Filter = (D3D11_FILTER)desc.Filter;
		rdesc.MaxAnisotropy = desc.MaxAnisotropy;
		rdesc.MaxLOD = desc.MaxLOD;
		rdesc.MinLOD = desc.MinLOD;
		rdesc.MipLODBias = desc.MipLODBias;

		HRESULT hr = device->CreateSamplerState( &rdesc, &myHandle );
		if( FAILED( hr ) )
			kTLaunchException( kT::Exception, "Failed to create the sampler state" );
	}

	KT_API D3D11SamplerState::~D3D11SamplerState()
	{
		if( myHandle != 0 )
			myHandle->Release();
	}

#if defined(KT_DEBUG)
    void KT_API D3D11SamplerState::SetName( const std::string& name )
    {
        myHandle->SetPrivateData( WKPDID_D3DDebugObjectName, name.length(), name.c_str() );
    }
#endif
}