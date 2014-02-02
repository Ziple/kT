#ifndef __KTOGL3IMMEDIATECONTEXT_HPP__
#define __KTOGL3IMMEDIATECONTEXT_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Graphics/GraphicsDevice/ImmediateContext.hpp>
#include <kT/Graphics/PixelFormat.hpp>
#include "OGL3Context.hpp"
#include "OGL3HardwareBuffer.hpp"

namespace kT
{
    class OGL3RenderTarget;
    class OGL3DepthStencilTarget;
    class OGL3HardwareBuffer;
    class OGL3InputLayout;
    class OGL3CommandList;
    class OGL3Program;

    /**
     * \ingroup ktogl3device_module
     * \todo Ajouter les RenderStates. S'occuper du Set des buffers. Faire les shaders. Faier la SwapChain, les textures, les pixel format...
     */
    class KT_API OGL3ImmediateContext
    {
        public:

            /**
             * \brief Constructor.
             */
            OGL3ImmediateContext( OGL3Context* myContext );

            ~OGL3ImmediateContext();

            /**
             * \brief Set the active shading program.
             */
            void SetProgram( OGL3Program* prog );

            /**
             * \brief Draws indexed primitives.
             * \param baseVertexLocation Index of the first vertex.
             * \param startIndex Index of the first index.
             * \param indexCountount Number of indices to draw.
             */
            void DrawIndexed( Uint32 indexCount, Uint32 startIndex, Int32 baseVertexLocation );

            /**
             * \brief Draw indexed and instanced primitives
             * \param IndexCountPerInstance Number of indices in one instance
             * \param InstanceCount Number of instances to draw
             * \param StartIndexLocation Offset to apply to the start of the index buffer
             * \param BaseVertexLocation Offset to apply to the beginning of the verttex buffer
             * \param StartInstanceLocation Ofset to apply to the beginning of the instance properties buffer
             */
            void DrawIndexedInstanced(
                Uint32 IndexCountPerInstance,
                Uint32 InstanceCount,
                Uint32 StartIndexLocation,
                Int32 BaseVertexLocation,
                Uint32 StartInstanceLocation
            );

            /**
             * \brief Performs a DrawIndexedInstanced but the arguments are provided in a buffer
             * \param argsBuffer Buffer containing the draw command.
             */
            void DrawIndexedInstancedIndirect( OGL3HardwareBuffer* argsBuffer );

            /**
             * \brief Enables/Disables depth-testing.
             * \param test Wether or not enable depth-testing.
             */
            void EnableDepthTesting( bool test = true );

            /**
             * \brief Enables/Disables depth-writing.
             * \param write Wether or not enable depth-writing.
             */
            void EnableDepthWrite( bool write = true );

            /**
             * \brief Sets the active input layout.
             */
            void IASetInputLayout( OGL3InputLayout* layout );

            /**
             * \brief Sets the active index buffer.
             */
            void IASetIndexBuffer(
                OGL3HardwareBuffer* indexBuffer,
                PixelFormat::Format componentType,
                Uint32 offset
            );

            /**
             * \brief Sets the active vertex buffer.
             */
            void IASetVertexBuffers(
                Uint32 startSlot,
                Uint32 numSLots,
                OGL3HardwareBuffer* const* vertexBuffers,
                const Uint32* strides,
                const Uint32* offsets
            );

            /**
             * \brief Sets the active primitive topology.
             */
            void IASetPrimitiveTopology( kT::PrimitiveTopology::Topology topology );

            void OMSetRenderTargets( Uint32 num, kT::OGL3Texture* const* renderTargets, kT::OGL3Texture* depthStencilTarget );

            /**
             * \brief Make the context active on this thread.
             */
            void MakeCurrent();

            /**
             * \brief Begin a new command list.
             * \return false if the rendering can NOT begin, true otherwise.
             *
             * If you are using a kT::DeferredContext, the pending commands will be lost.
             */
            bool Begin();

            /**
             * \brief Ends the command list.
             */
            void End();

            /**
             * \brief Executes the given command list.
             */
            void ExecuteCommands( OGL3CommandList* commands );

        private:

            OGL3Context* myContext;

            GLuint myFBO;

            Uint32 myTopology;
            OGL3InputLayout* myInputLayout;

            OGL3HardwareBuffer* myVertexBuffers[16];
            Uint32 myStrides[16];
            Uint32 myOffsets[16];

            OGL3HardwareBuffer* myIndexBuffer;
            Uint32 myIndicesOffset;
            GLenum myIndicesType;
            size_t myIndicesSize;
    };
}

#endif /* __KTOGL3IMMEDIATECONTEXT_HPP__ */