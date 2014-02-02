#include <kT/Graphics/D3D11Device/D3D11ShaderResource.hpp>
#include <kT/Core/Exceptions.hpp>

#include <d3d11.h>

namespace kT
{
    D3D11ShaderResource::~D3D11ShaderResource()
    {
        if( myView != 0 )
            myView->Release();
    }

#if defined(KT_DEBUG)
    void KT_API D3D11ShaderResource::SetName( const std::string& name )
    {
        if( myView != 0 )
            myView->SetPrivateData( WKPDID_D3DDebugObjectName, name.length(), name.c_str() );
    }
#endif

    void D3D11ShaderResource::CreateShaderResourceView(
         ID3D11Device* device,
         ID3D11Resource* resHandle,
         D3D11_SHADER_RESOURCE_VIEW_DESC* resDesc
        )
    {
        HRESULT hr = device->CreateShaderResourceView( resHandle, resDesc, &myView );
		if( FAILED( hr ) )
			kTLaunchException( kT::Exception, "Failed to create the resource view" );
    }
}