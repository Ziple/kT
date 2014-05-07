#include <kT/Graphics/D3D11Device/D3D11BlendState.hpp>
#include <kT/Graphics/D3D11Device/D3D11Device.hpp>
#include <kT/Core/Exceptions.hpp>

#include <d3d11.h>

namespace kT
{
	static D3D11_RENDER_TARGET_BLEND_DESC ToD3D11RenderTargetDesc( const BlendModeDesc& desc )
	{
		D3D11_RENDER_TARGET_BLEND_DESC ddesc;
		ddesc.BlendEnable = desc.BlendEnable;
		ddesc.SrcBlend = static_cast<D3D11_BLEND>(desc.SrcBlend);
		ddesc.DestBlend = static_cast<D3D11_BLEND>(desc.DestBlend);
		ddesc.BlendOp = static_cast<D3D11_BLEND_OP>(desc.BlendOp);
		ddesc.SrcBlendAlpha = static_cast<D3D11_BLEND>(desc.SrcBlendAlpha);
		ddesc.DestBlendAlpha = static_cast<D3D11_BLEND>(desc.DestBlendAlpha);
		ddesc.BlendOpAlpha = static_cast<D3D11_BLEND_OP>(desc.BlendOpAlpha);
		ddesc.RenderTargetWriteMask = desc.RenderTargetWriteMask;

		return ddesc;
	}

	static D3D11_BLEND_DESC ToD3D11BlendDesc(const BlendStateDesc& desc)
	{
		D3D11_BLEND_DESC ddesc;
		ddesc.AlphaToCoverageEnable = desc.AlphaToCoverageEnable;
		ddesc.IndependentBlendEnable = desc.IndependentBlendEnable;

		for (size_t i = 0; i < 8; i++)
			ddesc.RenderTarget[i] = ToD3D11RenderTargetDesc(desc.RenderTarget[i]);

		return ddesc;
	}

	KT_API D3D11BlendState::D3D11BlendState(
		D3D11Device* device,
		const BlendStateDesc& desc):
		D3D11BlendState(device->GetHandle(), desc )
	{}

	KT_API D3D11BlendState::D3D11BlendState(
		ID3D11Device* dev,
		const BlendStateDesc& desc):
		myHandle(0)
	{
		D3D11_BLEND_DESC ddesc = ToD3D11BlendDesc(desc);

		HRESULT hr = dev->CreateBlendState(&ddesc, &myHandle);

		if (FAILED( hr ) )
			kTLaunchException(kT::Exception, "Failed to create the blend state");

	}

	KT_API D3D11BlendState::~D3D11BlendState()
	{
		if (myHandle != 0)
			myHandle->Release();
	}

	KT_API D3D11BlendState* D3D11BlendState::CreateNoBlendingState(D3D11Device* device)
	{
		return new D3D11BlendState(device, BlendStateDesc::NoBlendingState());
	}

	KT_API D3D11BlendState* D3D11BlendState::CreateNoBlendingState(ID3D11Device* device)
	{
		return new D3D11BlendState(device, BlendStateDesc::NoBlendingState());
	}

	KT_API D3D11BlendState* D3D11BlendState::CreateAlphaBlendingState(D3D11Device* device)
	{
		return new D3D11BlendState(device, BlendStateDesc::AlphaBlendingState());
	}

	KT_API D3D11BlendState* D3D11BlendState::CreateAlphaBlendingState(ID3D11Device* device)
	{
		return new D3D11BlendState(device, BlendStateDesc::AlphaBlendingState());
	}

	KT_API D3D11BlendState* D3D11BlendState::CreateAdditiveBlendingState(D3D11Device* device)
	{
		return new D3D11BlendState(device, BlendStateDesc::AdditiveBlendingState());
	}

	KT_API D3D11BlendState* D3D11BlendState::CreateAdditiveBlendingState(ID3D11Device* device)
	{
		return new D3D11BlendState(device, BlendStateDesc::AdditiveBlendingState());
	}

#if defined(KT_DEBUG)
	void KT_API D3D11BlendState::SetName(const std::string& name)
	{
		myHandle->SetPrivateData( WKPDID_D3DDebugObjectName, name.length(), name.c_str() );
	}
#endif

}