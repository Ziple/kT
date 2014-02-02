/**
 * \file Graphics/GraphicsDevice/RenderTarget.hpp
 * \author Damien Hilloulin (ziple)
 * \date 28/02/2009
 * \brief Contains the definition of the kT::RenderTarget interface.
 */
#ifndef __KTRENDERTARGET_HPP__
#define __KTRENDERTARGET_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>

#include <kT/Math/Color.hpp>

namespace kT
{
    /**
     * \ingroup ktgfxrenderer_module
     * \brief Base class for render targets.
     *
     * This class defines the interface which must be implmented by the render
     * targets . The render targets are the color
     * buffers of the framebuffer.
     */
    class KT_API RenderTarget
    {
        public:

            /**
             * \brief Clear the target with the specified color.
             */
            virtual void Clear(
				const Colorf32& color
				) = 0;
    };
}

#endif /* __KTRENDERTARGET_HPP__ */
