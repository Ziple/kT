#include <kT/Graphics/D3D11Device/D3D11UnorderedAccessResource.hpp>
#include <kT/Core/Exceptions.hpp>

#include <d3d11.h>

namespace kT
{
    D3D11UnorderedAccessResource::~D3D11UnorderedAccessResource()
    {
        if( myUnorderedView != 0 )
            myUnorderedView->Release();
    }

#if defined(KT_DEBUG)
    void KT_API D3D11UnorderedAccessResource::SetName( const std::string& name )
    {
        if( myUnorderedView != 0 )
            myUnorderedView->SetPrivateData( WKPDID_D3DDebugObjectName, name.length(), name.c_str() );
    }
#endif

    void D3D11UnorderedAccessResource::CreateUnorderedAccessView(
         ID3D11Device* device,
         ID3D11Resource* resHandle,
         D3D11_UNORDERED_ACCESS_VIEW_DESC* resDesc
        )
    {
        HRESULT hr = device->CreateUnorderedAccessView( resHandle, resDesc, &myUnorderedView );
		if( FAILED( hr ) )
			kTLaunchException( kT::Exception, "Failed to create the resource view" );
    }
}