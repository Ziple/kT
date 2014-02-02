/**
 * \file Graphics/GraphicsDevice/DeferredContext.hpp
 * \author Damien Hilloulin (ziple)
 * \date 28/02/2009
 * \brief Contains the definition of the kT::DeferredContext interface.
 */
#ifndef __KTDEFERREDCONTEXT_HPP__
#define __KTDEFERREDCONTEXT_HPP__

#include <kT/Core/Build.hpp>
#include "GraphicsContext.hpp"
#include "HardwareBuffer.hpp"
#include "RenderTarget.hpp"
#include "DepthStencilTarget.hpp"
#include "InputLayout.hpp"
#include "PrimitiveTopology.hpp"
#include "../PixelFormat.hpp"
#include "ImplementationForwardDeclarations.hpp"

namespace kT
{
    /**
     * \ingroup ktgfxrenderer_module
     * \brief Interface for deferred contexts.
     *
     * Unlike immediate context, you can record GPU commands
     * with a deffered context to avoid to lose too much performance.
     */
	kTGraphicsDeviceTemplateListDef
	class KT_API DeferredContext: kT::GraphicsContext< kTGraphicsDeviceTemplateList >
    {
        public:

            /**
             * Return a copy of the current command list.
             */
            virtual ImplCommandList* GetCommandList() = 0;
    };
}

#endif  /* __KTDEFERREDCONTEXT_HPP__ */