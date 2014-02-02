/**
 * \file Graphics/GraphicsDevice/SwapChain.hpp
 * \author Damien Hilloulin (ziple)
 * \date 28/02/2009
 * \brief Contains the definition of the kT::SwapChain interface.
 */
#ifndef __KTSWAPCHAIN_HPP__
#define __KTSWAPCHAIN_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>

namespace kT
{
    class Window;
    namespace PixelFormat
    {
        enum Format;
    }

    /**
     * \ingroup ktgfxrenderer_module
     * \brief Definition of the SwapChain interface.
     */
    class KT_API SwapChain
    {
        public:

            SwapChain(
				Window* associatedWindow,
				PixelFormat::Format format,
				Uint32 width,
				Uint32 height,
				bool doubleBuffer,
				Uint32 multisamplingLevel
				):
             myAssociatedWindow( associatedWindow ),
             myFormat( format ),
             myWidth(width),
             myHeight(height),
             myDoubleBuffered( doubleBuffer ),
             myMultisamplingLevel( multisamplingLevel )
            {}

            /**
             * \brief Virtual destructor.
             */
            virtual ~SwapChain() {}

            /**
             * \brief Displays the content of the buffer and swap the buffers.
             * \param waitVSync true if you want to by synchronized with VBlank, false otherwise.
             */
            virtual void Present(
				bool waitVSync = false
				) = 0;

        protected:

            Window* myAssociatedWindow;
            PixelFormat::Format myFormat;
            Uint32 myWidth;
            Uint32 myHeight;
            bool myDoubleBuffered;
            Uint32 myMultisamplingLevel;
            
    };
}

#endif /* __KTSWAPCHAIN_HPP__ */