#include <kT/Graphics/D3D11Device/D3D11SwapChain.hpp>
#include <kT/Graphics/D3D11Device/D3D11Device.hpp>
#include <kT/Graphics/D3D11Device/D3D11Texture.hpp>
#include <kT/Graphics/D3D11Device/D3D11Format.hpp>
#include <kT/Core/Exceptions.hpp>

#include <D3D11.h>
#include <DXGI.h>

#include <iostream>

namespace kT
{
	// Doens't support multisampling yet.
	KT_API D3D11SwapChain::D3D11SwapChain(D3D11Device* device,
		Window* window,
		PixelFormat::Format format,
		bool doublebuffer,
		Uint32 multisamplingLevel):
	SwapChain( window,
                format,
                window->GetSize().Width,
                window->GetSize().Height,
                doublebuffer,
                multisamplingLevel ),
     myDevice( device->GetHandle() ),
	 mySwapChain( 0 ),
	 myTexture( 0 )
    {
        CreateSwapChain( device->GetHandle(), window, format, doublebuffer, multisamplingLevel );
    }

    // Doens't support multisampling yet.
    KT_API D3D11SwapChain::D3D11SwapChain( ID3D11Device* device,
                                    Window* window,
                                    PixelFormat::Format format,
                                    bool doublebuffer,
                                    Uint32 multisamplingLevel ):
     SwapChain( window,
                format,
                window->GetSize().Width,
                window->GetSize().Height,
                doublebuffer,
                multisamplingLevel ),
     myDevice( device ),
	 mySwapChain( 0 ),
	 myTexture( 0 )
    {
        CreateSwapChain( device, window, format, doublebuffer, multisamplingLevel );
    }

    KT_API D3D11SwapChain::~D3D11SwapChain()
    {
        DontListenAnymore( myAssociatedWindow );
        mySwapChain->SetFullscreenState( FALSE, NULL );
		delete myTexture;
        mySwapChain->Release();
    }

    void KT_API D3D11SwapChain::Present( bool waitVSync )
    {
        mySwapChain->Present( waitVSync ? 1 : 0,0);
    }

    void D3D11SwapChain::OnEvent( const EventEmitter<GUIEvent>* emitter, const GUIEvent* event )
    {
        if( event->Type == kT::GUIEvent::Resized )
        {
            if( myTexture != NULL )
                delete myTexture;

            // Resize
            DXGI_SWAP_CHAIN_DESC swapChainDesc;
            mySwapChain->GetDesc( &swapChainDesc );

            HRESULT ret;
            ret = mySwapChain->ResizeBuffers(
                myDoubleBuffered ? 2 : 1,
                event->Size.Width,
                event->Size.Height,
                swapChainDesc.BufferDesc.Format,
                swapChainDesc.Flags );

            ID3D11Texture2D* backBuffer = 0;
		    // render target view creation
		    {
			    HRESULT hr = mySwapChain->GetBuffer( 0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer) );
			    if( FAILED(hr) )
				    kTLaunchException( kT::Exception, "Couldn't get the back buffer" );
		    }

            myTexture = new D3D11Texture( myDevice, backBuffer );
        }
    }

#if defined(KT_DEBUG)
    void D3D11SwapChain::SetName( const std::string& name )
    {
        myTexture->SetName( name );
        mySwapChain->SetPrivateData( WKPDID_D3DDebugObjectName, name.length(), name.c_str() );
    }
#endif

     void KT_API D3D11SwapChain::CreateSwapChain(
        ID3D11Device* device,
        Window* window,
        PixelFormat::Format format,
        bool doublebuffer,
        Uint32 multisamplingLevel )
    {
        Listen( window );

        IDXGIDevice1 * pDXGIDevice;
        HRESULT hr = device->QueryInterface(__uuidof(IDXGIDevice1), (void **)&pDXGIDevice);
        if( FAILED(hr) )
        {
            kTLaunchException( kT::Exception, "Error while getting the dxgi device" );
        }

        IDXGIAdapter1 * pDXGIAdapter;
        hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter1), (void **)&pDXGIAdapter);
        if( FAILED(hr) )
        {
            kTLaunchException( kT::Exception, "Error while getting the dxgi adapter" );
        }

        IDXGIFactory1 * dxgiFactory;
        pDXGIAdapter->GetParent(__uuidof(IDXGIFactory1), (void **)&dxgiFactory);
        if( FAILED(hr) )
        {
            kTLaunchException( kT::Exception, "Error while getting the dxgi factory" );
        }
        dxgiFactory->MakeWindowAssociation( window->GetWindowHandle(), 0 );

        DXGI_SWAP_CHAIN_DESC swapChainDesc;
        swapChainDesc.BufferDesc.Width = 0;//automatically get it from the window
        swapChainDesc.BufferDesc.Height = 0;
        swapChainDesc.BufferDesc.Format = D3D11Format::GetDXGIFormat( format );
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        swapChainDesc.BufferCount = doublebuffer ? 1 : 0;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        swapChainDesc.OutputWindow = window->GetWindowHandle();
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        swapChainDesc.Windowed = TRUE;

        if(window->GetStyle() == kT::Window::Fullscreen)
        {
            // We create a dummy swapchain so as to know which output
            // the real swapchain will be using, and then retrieve the
            // closest matching mode.
            kT::Window* dummyWindow = new kT::Window("", window->GetSize(), kT::Window::Fullscreen );

            DXGI_SWAP_CHAIN_DESC dummyDesc = swapChainDesc;
            dummyDesc.OutputWindow = dummyWindow->GetWindowHandle();

            IDXGISwapChain* dummySwapChain;
            hr = dxgiFactory->CreateSwapChain( device, &dummyDesc, &dummySwapChain );
            if( FAILED(hr) )
                kTLaunchException( kT::Exception, "Error while creating the dummy swapchain" );

            IDXGIOutput* output;
            dummySwapChain->GetContainingOutput( &output );

            DXGI_MODE_DESC closestMode;
            output->FindClosestMatchingMode( &swapChainDesc.BufferDesc, &closestMode, NULL );
            swapChainDesc.BufferDesc = closestMode;

            output->Release();
            dummySwapChain->Release();
            delete dummyWindow;
        }
        

        hr = dxgiFactory->CreateSwapChain( device, &swapChainDesc, &mySwapChain );
        if( FAILED(hr) )
            kTLaunchException( kT::Exception, "Error while creating the swapchain" );

        dxgiFactory->Release();
        pDXGIAdapter->Release();
        pDXGIDevice->Release();

		ID3D11Texture2D* backBuffer = 0;
		// render target view creation
		{
			HRESULT hr = mySwapChain->GetBuffer( 0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer) );
			if( FAILED(hr) )
				kTLaunchException( kT::Exception, "Couldn't get the back buffer" );
		}

		myTexture = new D3D11Texture( device, backBuffer );

        // dxgi automatically calls DispatchMessage(), so we must put this at the end.
        // otherwise, we should have remaining references to the swapchain
        if(window->GetStyle() == kT::Window::Fullscreen)
			mySwapChain->SetFullscreenState( TRUE, NULL );
    }
}