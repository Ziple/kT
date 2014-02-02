#include <kT/Graphics/D3D11Device/D3D11RasterizerState.hpp>
#include <kT/Core/Exceptions.hpp>

#include <D3D11.h>

namespace kT
{
	KT_API D3D11RasterizerState::D3D11RasterizerState(
				ID3D11Device* device,
				const RasterizerDesc& desc )
	{
		D3D11_RASTERIZER_DESC rdesc;
		rdesc.FillMode = (D3D11_FILL_MODE)desc.fillMode;
		rdesc.CullMode = (D3D11_CULL_MODE)desc.cullMode;
		rdesc.DepthBias = desc.depthBias;
		rdesc.DepthBiasClamp = desc.depthBiasClamp;
		rdesc.DepthClipEnable = (BOOL)desc.depthClipEnable;
		rdesc.FrontCounterClockwise = (BOOL)desc.frontCounterClockwise;
		rdesc.ScissorEnable = (BOOL)desc.scissorEnable;
		rdesc.SlopeScaledDepthBias = desc.slopeScaledDepthBias;
		rdesc.MultisampleEnable = (BOOL)desc.multisampleEnable;
		rdesc.AntialiasedLineEnable = (BOOL)desc.antialiasedLineEnable;

		HRESULT hr = device->CreateRasterizerState( &rdesc, &myHandle );
		if( FAILED( hr ) )
			kTLaunchException( kT::Exception, "Failed to create the rasterizer state" );
	}

	KT_API D3D11RasterizerState::~D3D11RasterizerState()
	{
		if( myHandle != 0 )
			myHandle->Release();
	}

#if defined(KT_DEBUG)
    void KT_API D3D11RasterizerState::SetName( const std::string& name )
    {
        myHandle->SetPrivateData( WKPDID_D3DDebugObjectName, name.length(), name.c_str() );
    }
#endif
}