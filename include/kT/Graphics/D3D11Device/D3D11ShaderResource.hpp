#ifndef __KTD3D11SHADERRESOURCE_HPP__
#define __KTD3D11SHADERRESOURCE_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>
#include <kT/Core/NonCopyable.hpp>

#if defined(KT_DEBUG)
#include <string>
#endif

struct ID3D11Device;
struct ID3D11Texture2D;
struct ID3D11ShaderResourceView;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct ID3D11Resource;
struct D3D11_SHADER_RESOURCE_VIEW_DESC;

namespace kT
{
    class KT_API D3D11ShaderResource: public NonCopyable
	{
		public:

			D3D11ShaderResource():
             myView( 0 )
            {}

			~D3D11ShaderResource();

			inline ID3D11ShaderResourceView* GetShaderResourceView() {return myView;}

#if defined(KT_DEBUG)
            void SetName( const std::string& name );
#endif
			
		protected:

            void CreateShaderResourceView(
				ID3D11Device* device,
				ID3D11Resource* reshandle,
                D3D11_SHADER_RESOURCE_VIEW_DESC* resDesc
				);

			ID3D11ShaderResourceView* myView;
	};

}

#endif /* __KTD3D11SHADERRESOURCE_HPP__ */