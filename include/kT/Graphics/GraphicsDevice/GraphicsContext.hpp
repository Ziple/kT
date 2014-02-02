/**
 * \file Graphics/GraphicsDevice/GraphicsContext.hpp
 * \author Damien Hilloulin (ziple)
 * \date 28/02/2009
 * \brief Contains the definition of the kT::GraphicsContext interface.
 */
#ifndef __KTGRAPHICSCONTEXT_HPP__
#define __KTGRAPHICSCONTEXT_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>
#include "PrimitiveTopology.hpp"
#include "../PixelFormat.hpp"
#include "ImplementationForwardDeclarations.hpp"

namespace kT
{
    /**
     * \ingroup ktgfxrenderer_module
     * \brief Interface for generic graphics contexts.
     *
     * base class for all types of graphics context.
     */
	kTGraphicsDeviceTemplateListDef
    class KT_API GraphicsContext
    {
        public:

            /**
             * \brief Draws to screen using the current vertex buffer.
             * \param first Index of the first vertex.
             * \param count Number of vertices to draw.
             */
            virtual void Draw(
				Uint32 first, Uint32 count
				) = 0;

            /**
             * \brief Draws index but not instanced primitives.
             * \param firstVertex Index of the first vertex.
             * \param firstIndex Index of the first index.
             * \param count Number of indices to draw.
             */
            virtual void DrawIndexed(
				Uint32 firstVertex,
				Uint32 firstIndex,
				Uint32 count
				) = 0;

            /**
             * \brief Enables/Disables depth-testing.
             * \param test Wether or not enable depth-testing.
             */
            virtual void EnableDepthTesting(
				bool test = true
				) = 0;

            /**
             * \brief Enables/Disables depth-writing.
             * \param write Wether or not enable depth-writing.
             */
            virtual void EnableDepthWrite(
				bool write = true
				) = 0;

            /**
             * \brief Sets the render targets.
             * \param n Number of render targets in the array.
             * \param renderTargets Array of the render targets.
             */
            virtual void SetRenderTargets(
				Uint32 n,
				ImplRenderTarget** renderTargets
				) = 0;
            /**
             * \brief Sets the depth/stencil target.
             * \param target The depth/stencil target to bound.
             */
            virtual void SetDepthStencilTarget(
				ImplDepthStencilTarget* target
				) = 0;

            /**
             * \brief Sets the active input layout.
             */
            virtual void SetInputLayout(
				ImplInputLayout* layout
				) = 0;

            /**
             * \brief Sets the active index buffer.
             */
            virtual void SetIndexBuffer(
				ImplHardwareBuffer* indexBuffer,
                PixelFormat::Format componentType
				) = 0;

            /**
             * \brief Sets the active vertex buffer.
             */
            virtual void SetVertexBuffers(
				Uint32 startSlot,
				Uint32 n,
				ImplHardwareBuffer** vertexBuffers
				) = 0;

            /**
             * \brief Sets the active primitive topology.
             */
            virtual void SetPrimitiveTopology(
				kT::PrimitiveTopology::Topology topology
				) = 0;

            /**
             * \brief Make the context active on this thread.
             */
            virtual void MakeCurrent() = 0;

            /**
             * \brief Begin a new command list.
             * \return false if the rendering can NOT begin, true otherwise.
             *
             * If you are using a kT::DeferredContext, the pending commands will be lost.
             */
            virtual bool Begin() = 0;

            /**
             * \brief Ends the command list.
             */
            virtual void End() = 0;
    };
}

#endif /* __KTGRAPHICSCONTEXT_HPP__ */