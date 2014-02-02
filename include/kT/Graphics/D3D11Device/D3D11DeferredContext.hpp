#ifndef __KTD3D11DEFERREDCONTEXT_HPP__
#define __KTD3D11DEFERREDCONTEXT_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>
#include <kT/Core/NonCopyable.hpp>
#include <kT/Graphics/D3D11Device/D3D11GraphicsContext.hpp>
#include <kT/Graphics/PixelFormat.hpp>
#include <kT/Graphics/GraphicsDevice/PrimitiveTopology.hpp>
#include <kT/Math/Vector4.hpp>

#include <D3D11.h>

#if defined(KT_DEBUG)
#include <string>
#endif

namespace kT
{
    struct ViewportDesc;

	class D3D11HardwareBuffer;
	class D3D11RasterizerState;
    class D3D11SamplerState;
	class D3D11InputLayout;
	class D3D11Shader;
	class D3D11Texture;
    class D3D11ShaderResource;
    class D3D11UnorderedAccessResource;

	class KT_API D3D11DeferredContext: public kT::D3D11GraphicsContext
	{
		public:

			D3D11DeferredContext( ID3D11DeviceContext* handle ):
			 kT::D3D11GraphicsContext( handle )
			{}
	};

}

#endif /* __KTD3D11DEFERREDCONTEXT_HPP__ */
