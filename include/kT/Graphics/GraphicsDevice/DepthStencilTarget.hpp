/**
 * \file Graphics/GraphicsDevice/DepthStencilTarget.hpp
 * \author Damien Hilloulin (ziple)
 * \date 01/03/2009
 * \brief Contains the definition of the kT::DepthStencilTarget interface.
 */
#ifndef __KTDEPTHSTENCILTARGET_HPP__
#define __KTDEPTHSTENCILTARGET_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>

namespace kT
{
    /**
        * \ingroup ktgfxrenderer_module
        * \brief Specifies the parts of the DepthStencilTarget to clear.
        */
    enum ClearFlag
    {
        ClearDepth = 1,  ///< Clear the depth part of the target.
        ClearStencil = 2,///< Clear the stencil part of the target.
    };

    /**
     * \ingroup ktgfxrenderer_module
     * \brief Interface for depth/stencil target.
     *
     * Depth/stencil targets are textures bound as depth/stencil buffers of the
     * framebuffer. It's not mandatory that the texture contain a stencil element
     * but stenciling won't be available in this case.
     */
    class KT_API DepthStencilTarget
    {
        public:

            /**
             * \brief Clear the depth-stencil target with the specified values.
             * \param clearFlag A combination of ClearFlag (ORed together).
             * \param depthValue The value to clear the depth buffer with.
             * \param stencilValue The value to clear the stencil buffer with.
             */
            virtual void Clear(
				Uint32 clearFlag,
				Float32 depthValue,
				Uint8 stencilValue
				) = 0;
    };
}
#endif /* __KTDEPTHSTENCILTARGET_HPP__ */
