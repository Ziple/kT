#ifndef __KTOGL3DEVICETYPES_HPP__
#define __KTOGL3DEVICETYPES_HPP__

#include <kT/Graphics/GraphicsDevice/ImplementationForwardDeclarations.hpp>

namespace kT
{
	class OGL3Device;
	class OGL3ImmediateContext;
	class OGL3HardwareBuffer;
	class OGL3Texture;
	class OGL3RenderTarget;
	class OGL3SwapChain;
	class OGL3DepthStencilTarget;
	class OGL3DeferredContext;
	class OGL3ImmediateContext;
	class OGL3InputLayout;
	class OGL3CommandList;

	struct OGL3DeviceTypes
	{
		typedef OGL3Device Device;
		typedef OGL3ImmediateContext ImmediateContext;
		typedef OGL3HardwareBuffer HardwareBuffer;
		typedef OGL3Texture Texture;
		typedef OGL3RenderTarget RenderTarget;
		typedef OGL3SwapChain SwapChain;
		typedef OGL3DepthStencilTarget DepthStencilTarget;
		typedef OGL3DeferredContext DeferredContext;
		typedef OGL3ImmediateContext ImmediateContext;
		typedef OGL3InputLayout InputLayout;
		typedef OGL3CommandList CommandList;
        typedef void* Shader;
	};
}

#define kTOGL3DeviceTemplateListLineTypes kTGraphicsDeviceTemplateListLineTypes(OGL3DeviceTypes)

#endif /* __KTOGL3DEVICETYPES_HPP__ */