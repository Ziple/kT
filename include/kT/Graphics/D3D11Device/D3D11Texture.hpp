#ifndef __KTD3D11TEXTURE_HPP__
#define __KTD3D11TEXTURE_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/NonCopyable.hpp>
#include <kT/Core/Types.hpp>
#include <kT/Math/Size.hpp>
#include <kT/Graphics/GraphicsDevice/Texture.hpp>
#include <kT/Graphics/PixelFormat.hpp>

#include <kT/Graphics/D3D11Device/D3D11ShaderResource.hpp>

#if defined(KT_DEBUG)
#include <string>
#endif

struct ID3D11Device;
struct ID3D11Texture2D;
struct ID3D11ShaderResourceView;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;

namespace kT
{
	class D3D11Device;

    class KT_API D3D11Texture: public D3D11ShaderResource
	{
		public:

			D3D11Texture(
				D3D11Device* device,
				Uint32 bindFlags,
				PixelFormat::Format format,
				const kT::Sizeui32& size,
				const void* texDataPtr = 0,
				bool generateMipMapsCaps = true
				);

			D3D11Texture(
				ID3D11Device* device,
                Uint32 bindFlags,
                PixelFormat::Format format,
				const kT::Sizeui32& size,
				const void* texDataPtr = 0,
				bool generateMipMapsCaps = true
			);

			D3D11Texture(
				ID3D11Device* device,
				ID3D11Texture2D* texhandle );

			~D3D11Texture();

			inline const kT::Sizeui32& GetSize() const {return mySize;}

			inline ID3D11Texture2D* GetHandle() {return myHandle;}

			inline ID3D11RenderTargetView* GetRenderTargetView() {return myRenderTargetView;}

			inline ID3D11DepthStencilView* GetDepthStencilView() {return myDepthStencilView;}

#if defined(KT_DEBUG)
            void SetName( const std::string& name );
#endif
			
		protected:

            void CreateViews(
				ID3D11Device* device,
				ID3D11Texture2D* texhandle
				);

			ID3D11Texture2D* myHandle;
			ID3D11RenderTargetView* myRenderTargetView;
			ID3D11DepthStencilView* myDepthStencilView;

			kT::Sizeui32 mySize;
	};

}

#endif /* __KTD3D11TEXTURE_HPP__ */