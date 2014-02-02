/**
 * \file Graphics/GraphicsDevice/ImmediateContext.hpp
 * \author Damien Hilloulin (ziple)
 * \date 28/02/2009
 * \brief Contains the definition of the kT::ImmediateContext interface.
 */
#ifndef __KTIMMEDIATECONTEXT_HPP__
#define __KTIMMEDIATECONTEXT_HPP__

#include <kT/Core/Build.hpp>
#include "GraphicsContext.hpp"
#include "DeferredContext.hpp"
#include "PrimitiveTopology.hpp"
#include "ImplementationForwardDeclarations.hpp"

namespace kT
{
    /**
     * \ingroup ktgfxrenderer_module
     * \brief Interface for immediate contexts.
     *
     * Unlike deferred context, immediate contexts immediately
     * send the draw commands to the GPU and so the performance
     * penalty can be big if not carefully mesaured.
     * You can send batchs of command recorded with a deffered contex though
     * with kT::ImmediateContext::ExecuteCommands()
     */
	kTGraphicsDeviceTemplateListDef
	class KT_API ImmediateContext: kT::GraphicsContext< kTGraphicsDeviceTemplateList >
    {
        public:

            /**
             * \brief Executes the commands in the list.
             */
            virtual void ExecuteCommands(
				ImplCommandList* commands
				) = 0;
    };
}

#endif  /* __KTIMMEDIATECONTEXT_HPP__ */