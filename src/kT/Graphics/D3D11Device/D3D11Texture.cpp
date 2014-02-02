#include <kT/Graphics/D3D11Device/D3D11Texture.hpp>

#include <kT/Core/Exceptions.hpp>
#include <kT/Graphics/PixelFormat.hpp>
#include <kT/Graphics/D3D11Device/D3D11Format.hpp>

#include <D3D11.h>

namespace kT
{
	KT_API D3D11Texture::D3D11Texture(
		ID3D11Device* device,
        Uint32 bindFlags,
        PixelFormat::Format format,
		const kT::Sizeui32& size,
		const void* texDataPtr,
		bool generateMipMaps
		):
	 myRenderTargetView( 0 ),
	 myHandle( 0 ),
	 myDepthStencilView( 0 )
	{
		D3D11_TEXTURE2D_DESC texDesc;
		texDesc.Width = size.Width;
		texDesc.Height = size.Height;
		texDesc.MipLevels = generateMipMaps ? 0 : 1;
		texDesc.ArraySize = 1;
		texDesc.Format = D3D11Format::GetDXGIFormat( format );
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.BindFlags = 0;
		
		if( ((bindFlags & Texture::ShaderInput) != 0 )
			|| (generateMipMaps == true) )
			texDesc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
		if( ((bindFlags & Texture::RenderTarget) != 0)
			|| (generateMipMaps == true) )
			texDesc.BindFlags |= D3D11_BIND_RENDER_TARGET;
		if( (bindFlags & Texture::DepthStencilBuffer) != 0 )
			texDesc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;

		texDesc.CPUAccessFlags = 0;
		texDesc.MiscFlags = generateMipMaps? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0;

		size_t formatsize = PixelUtility::GetPixelFormatDescriptor(format).GetSize();
		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = texDataPtr;
		data.SysMemPitch = size.Width * formatsize;
		data.SysMemSlicePitch = 0;
		

		HRESULT hr = device->CreateTexture2D( &texDesc, (generateMipMaps || (texDataPtr == 0))? 0 : &data, &myHandle );
		if( FAILED( hr ) )
			kTLaunchException( kT::Exception, "Failed to create the texture" );

		// We provide the initial data if we generate the mipmaps.
		if( generateMipMaps )
		{
			ID3D11DeviceContext* imContext;
			device->GetImmediateContext(&imContext);
			D3D11_BOX box;
			box.left = 0;
			box.top = 0;
			box.bottom = size.Height;
			box.right = size.Width;
			box.front = 0;
			box.back = 1;

			imContext->UpdateSubresource( myHandle, 0, &box, texDataPtr, size.Width * formatsize, 0 );
			imContext->Release();
		}

		// We then create the views and if necessary, the mipmaps
		CreateViews( device, myHandle );
	}

	KT_API D3D11Texture::D3D11Texture(
		ID3D11Device* device,
		ID3D11Texture2D* texhandle
		):
	 myHandle( 0 ),
	 myRenderTargetView( 0 ),
	 myDepthStencilView(0)
	{CreateViews( device, texhandle );}

	void KT_API D3D11Texture::CreateViews(
		ID3D11Device* device,
		ID3D11Texture2D* texhandle
		)
	{
		myHandle = texhandle;

		D3D11_TEXTURE2D_DESC texDesc;
		myHandle->GetDesc(&texDesc);

		mySize.Width = texDesc.Width;
		mySize.Height = texDesc.Height;

		bool generateMipMaps = ((texDesc.MiscFlags & D3D11_RESOURCE_MISC_GENERATE_MIPS) != 0) ? true : false;

		HRESULT hr;
		if( (texDesc.BindFlags & D3D11_BIND_SHADER_RESOURCE) != 0 )
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC resDesc;
			resDesc.Format = texDesc.Format;
			resDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			resDesc.Texture2D.MostDetailedMip = 0;
			resDesc.Texture2D.MipLevels = texDesc.MipLevels;

            D3D11ShaderResource::CreateShaderResourceView( device, myHandle, &resDesc );

			// We generate the mipmaps.
			if( generateMipMaps )
			{
				ID3D11DeviceContext* imContext;
				device->GetImmediateContext(&imContext);
				imContext->GenerateMips( myView );
				imContext->Release();
			}
		}

		if((texDesc.BindFlags & D3D11_BIND_RENDER_TARGET) != 0)
		{
			// Création de la render target view
			hr = device->CreateRenderTargetView( myHandle, 0, &myRenderTargetView );
			if( FAILED(hr) )
				kTLaunchException( kT::Exception, "Couldn't create the render target view" );
		}

		if( (texDesc.BindFlags & D3D11_BIND_DEPTH_STENCIL) != 0 )
		{
			// Création de la render target view
			hr = device->CreateDepthStencilView( myHandle, 0, &myDepthStencilView );
			if( FAILED(hr) )
				kTLaunchException( kT::Exception, "Couldn't create the depth stencil view" );
		}
	}

	KT_API D3D11Texture::~D3D11Texture()
	{
		if( myRenderTargetView != 0 )
			myRenderTargetView->Release();
		if( myDepthStencilView != 0 )
			myDepthStencilView->Release();

		myHandle->Release();
	}

#if defined(KT_DEBUG)
    void KT_API D3D11Texture::SetName( const std::string& name )
    {
        myHandle->SetPrivateData( WKPDID_D3DDebugObjectName, name.length(), name.c_str() );

        if( myRenderTargetView != 0 )
        {
            std::string str = name + std::string(" RTV");
			myRenderTargetView->SetPrivateData( WKPDID_D3DDebugObjectName, str.length(), str.c_str() );
        }
		if( myDepthStencilView != 0 )
        {
            std::string str = name + std::string(" DSV");
			myDepthStencilView->SetPrivateData( WKPDID_D3DDebugObjectName, str.length(), str.c_str() );
        }

        D3D11ShaderResource::SetName( name + std::string(" SRV") );
    }
#endif
}