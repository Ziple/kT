#ifndef __KTD3D11DEVICETYPES_HPP__
#define __KTD3D11DEVICETYPES_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Graphics/GraphicsDevice/ImplementationForwardDeclarations.hpp>

namespace kT
{
	class D3D11Device;
	class D3D11ImmediateContext;
	class D3D11HardwareBuffer;
	class D3D11Texture;
	class D3D11RenderTarget;
	class D3D11SwapChain;
	class D3D11DepthStencilTarget;
	class D3D11DeferredContext;
	class D3D11ImmediateContext;
	class D3D11InputLayout;
	class D3D11CommandList;
    class D3D11Shader;

	struct D3D11DeviceTypes
	{
		typedef D3D11Device Device;
		typedef D3D11ImmediateContext ImmediateContext;
		typedef D3D11HardwareBuffer HardwareBuffer;
		typedef D3D11Texture Texture;
		typedef D3D11RenderTarget RenderTarget;
		typedef D3D11SwapChain SwapChain;
		typedef D3D11DepthStencilTarget DepthStencilTarget;
		typedef D3D11DeferredContext DeferredContext;
		typedef D3D11ImmediateContext ImmediateContext;
		typedef D3D11InputLayout InputLayout;
		typedef D3D11CommandList CommandList;
        typedef D3D11Shader Shader;
	};
}

#define kTD3D11DeviceTemplateListLineTypes kTGraphicsDeviceTemplateListLineTypes(kT::D3D11DeviceTypes)

#endif /* __KTD3D11DEVICETYPES_HPP__ */