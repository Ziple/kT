#ifndef __KTGRAPHICSDEVICEFORWARDDECLARATIONS_HPP__
#define __KTGRAPHICSDEVICEFORWARDDECLARATIONS_HPP__

namespace kT
{
	template<typename Types>
    class GraphicsContext;

	template< typename T>
    class DeferredContext<T>;

	template<typename T>
    class ImmediateContext<T>;

	template<typename Types>
    class GraphicsDevice;

	template< typename Types >
    class HardwareBuffer;

	struct InputLayoutDesc;

	class InputLayout;

	struct RasterizerDesc;

	class RenderTarget;

	class SwapChain;

	class Texture;
}

#endif /* __KTGRAPHICSDEVICEFORWARDDECLARATIONS_HPP__ */