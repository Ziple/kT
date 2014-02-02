#ifndef __KTIMPLFORWARDDECLARATIONS_HPP__
#define __KTIMPLFORWARDDECLARATIONS_HPP__

#define kTGraphicsDeviceTemplateList \
	 ImplDevice,\
	 ImplImmediateContext,\
	 ImplHardwareBuffer,\
	 ImplTexture,\
	 ImplRenderTarget,\
	 ImplSwapChain,\
	 ImplDepthStencilTarget,\
	 ImplDeferredContext,\
	 ImplInputLayout,\
	 ImplCommandList,\
     ImplShader

#define kTGraphicsDeviceTemplateListDef template< \
	typename ImplDevice,\
	typename ImplImmediateContext,\
	typename ImplHardwareBuffer,\
	typename ImplTexture,\
	typename ImplRenderTarget,\
	typename ImplSwapChain,\
	typename ImplDepthStencilTarget,\
	typename ImplDeferredContext,\
	typename ImplInputLayout,\
	typename ImplCommandList,\
    typename ImplShader >

#define kTGraphicsDeviceTemplateListLineTypes( Types ) \
	Types::Device,\
	Types::ImmediateContext,\
	Types::HardwareBuffer,\
	Types::Texture,\
	Types::RenderTarget,\
	Types::SwapChain,\
	Types::DepthStencilTarget,\
	Types::DeferredContext,\
	Types::InputLayout,\
	Types::CommandList,\
    Types::Shader

#endif /* __KTIMPLFORWARDDECLARATIONS_HPP__ */