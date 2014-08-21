#ifndef __KTD3D11SWAPCHAIN_HPP__
#define __KTD3D11SWAPCHAIN_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/NonCopyable.hpp>
#include <kT/Math/Size.hpp>
#include <kT/Graphics/GraphicsDevice/SwapChain.hpp>
#include <kT/Window/Window.hpp>
#include <kT/Graphics/PixelFormat.hpp>

#if defined(KT_DEBUG)
#include <string>
#endif

struct ID3D11Device;
struct IDXGISwapChain;

namespace kT
{
	class D3D11Device;
	class D3D11Texture;

    class KT_API D3D11SwapChain: public SwapChain,
                                 public NonCopyable,
                                 protected EventListener<GUIEvent>
    {
        public:

			// doesn't have really support for multisampling
			D3D11SwapChain(D3D11Device* device,
				Window* associatedWindow,
				PixelFormat::Format format,
				bool doubleBuffer,
				Uint32 multisamplingLevel);

			// doesn't have really support for multisampling
            D3D11SwapChain( ID3D11Device* device,
                            Window* associatedWindow,
                            PixelFormat::Format format,
                            bool doubleBuffer,
                            Uint32 multisamplingLevel );

            ~D3D11SwapChain();

            void Present( bool waitVSync = false );

            IDXGISwapChain* GetHandle() const {return mySwapChain;}

			D3D11Texture* GetTexture() const {return myTexture;}

#if defined(KT_DEBUG)
            void SetName( const std::string& name );
#endif

        protected:

            void CreateSwapChain( ID3D11Device* device,
                            Window* associatedWindow,
                            PixelFormat::Format format,
                            bool doubleBuffer,
                            Uint32 multisamplingLevel );

            /**
             * \brief Let us resize properly the swapchain
             */
            void OnEvent( const EventEmitter<GUIEvent>* emitter, const GUIEvent* event );

            ID3D11Device* myDevice;
            IDXGISwapChain* mySwapChain;
			D3D11Texture* myTexture;
    };
}

#endif /* __KTD3D11SWAPCHAIN_HPP__ */
