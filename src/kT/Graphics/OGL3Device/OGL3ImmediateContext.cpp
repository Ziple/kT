#include <kT/Graphics/OGL3Device/OGL3ImmediateContext.hpp>
#include <kT/Graphics/OGL3Device/OGL3Check.hpp>
#include <kT/Graphics/OGL3Device/OGL3InputLayout.hpp>
#include <kT/Graphics/OGL3Device/OGL3Shader.hpp>
#include <kT/Graphics/OGL3Device/OGL3Texture.hpp>
#include <kT/Core/Exceptions.hpp>

#include <kT/Graphics/OGL3Device/OGL.hpp>

#include <cstring>

namespace kT
{
    KT_API OGL3ImmediateContext::OGL3ImmediateContext( OGL3Context* context ):
     myContext( context ),
     myFBO( 0 ),
     myTopology( GL_TRIANGLES ),
     myInputLayout( 0 ),
     myIndexBuffer( 0 ),
     myIndicesOffset( 0 ),
     myIndicesSize( 0 ),
     myIndicesType( 0 )
    {
        memset( myVertexBuffers, 0, sizeof(OGL3HardwareBuffer*) * 16 );
        memset( myStrides, 0, sizeof(Uint32)*16 );
        memset( myOffsets, 0, sizeof(Uint32)*16 );

        glGenFramebuffers( 1, &myFBO );
    }

    KT_API OGL3ImmediateContext::~OGL3ImmediateContext()
    {
        glDeleteFramebuffers( 1, &myFBO );
    }

    void KT_API OGL3ImmediateContext::SetProgram( OGL3Program* prog )
    {
        glUseProgram( prog->GetProgramID() );
    }

    void KT_API OGL3ImmediateContext::DrawIndexed( Uint32 indexCount, Uint32 startIndex, Int32 baseVertexLocation )
    {
        ktOGL3Check(
            glDrawElementsBaseVertex(
                myTopology,
                indexCount,
                myIndicesType,
                reinterpret_cast<void*>((startIndex + myIndicesOffset) * myIndicesSize ), 
                baseVertexLocation )
        );
    }

    void KT_API OGL3ImmediateContext::DrawIndexedInstanced(
        Uint32 IndexCountPerInstance,
        Uint32 InstanceCount,
        Uint32 StartIndexLocation,
        Int32 BaseVertexLocation,
        Uint32 StartInstanceLocation
    )
    {
        ktOGL3Check(
            glDrawElementsInstancedBaseVertexBaseInstance(
                myTopology,
                IndexCountPerInstance,
                myIndicesType,
                reinterpret_cast<void*>((StartIndexLocation + myIndicesOffset) * myIndicesSize),
                InstanceCount,
                BaseVertexLocation,
                StartInstanceLocation
                )
            );
    }

    void KT_API OGL3ImmediateContext::DrawIndexedInstancedIndirect( OGL3HardwareBuffer* argsBuffer )
    {
        ktOGL3Check(
            glBindBuffer( GL_DRAW_INDIRECT_BUFFER, argsBuffer->GetHandle() )
            );

        ktOGL3Check(
            glDrawElementsIndirect(
                myTopology,
                myIndicesType,
                0
            )
        );
    }

    void KT_API OGL3ImmediateContext::EnableDepthTesting( bool test )
    {
        if ( test == true )
            ktOGL3Check( glEnable( GL_DEPTH_TEST ) );
        else
            ktOGL3Check( glDisable( GL_DEPTH_TEST ) );
    }

    void KT_API OGL3ImmediateContext::EnableDepthWrite( bool write )
    {
        ktOGL3Check( glDepthMask( write ? GL_TRUE : GL_FALSE ) );
    }

    void KT_API OGL3ImmediateContext::IASetInputLayout( OGL3InputLayout* layout )
    {
        myInputLayout = layout;
    }

    void KT_API OGL3ImmediateContext::IASetIndexBuffer(
        OGL3HardwareBuffer* indexBuffer,
        PixelFormat::Format format,
        Uint32 offset )
    {
        myIndexBuffer = indexBuffer;
        myIndicesOffset = offset;

        if( format == PixelFormat::R16_UINT )
        {
            myIndicesSize = 2;
            myIndicesType = GL_UNSIGNED_SHORT;
        }
        else if( format == PixelFormat::R32_UINT )
        {
            myIndicesSize = 4;
            myIndicesType = GL_UNSIGNED_INT;
        }

        ktOGL3Check(
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer->GetHandle() )
        );
    }

    void KT_API OGL3ImmediateContext::IASetVertexBuffers(
        Uint32 startSlot,
        Uint32 numSLots,
        OGL3HardwareBuffer* const* vertexBuffers,
        const Uint32* strides,
        const Uint32* offsets
    )
    {
        memcpy( myVertexBuffers+startSlot, vertexBuffers, sizeof(OGL3HardwareBuffer*)*numSLots );
        memcpy( myStrides+startSlot, strides, sizeof(Uint32)*numSLots );
        memcpy( myOffsets+startSlot, offsets, sizeof(Uint32)*numSLots );

        OGL3InputElementDesc* elements = myInputLayout->GetElements();
        for( size_t i = 0; i < myInputLayout->GetNumElements(); i++ )
        {
            const OGL3HardwareBuffer* buff = myVertexBuffers[ elements[i].inputSlot ];

            if( buff != 0 )
            {
                ktOGL3Check(
                    glBindBuffer( GL_ARRAY_BUFFER, buff->GetHandle() )
                );

                ktOGL3Check(
                    glVertexAttribPointer(
                    elements[i].attribIndex,
                    elements[i].size,
                    elements[i].type,
                    GL_FALSE,
                    myStrides[ elements[i].inputSlot ],
                    (void*)( myOffsets[ elements[i].inputSlot ] + elements[i].offset ) )
                );

                ktOGL3Check(
                    glEnableVertexAttribArray( elements[i].attribIndex )
                );

                if( elements[i].inputClass == kT::InputElementClass::PerInstance )
                    ktOGL3Check( glVertexAttribDivisorARB( elements[i].attribIndex, elements[i].stepRate ) );
            }
        }
    }

    void KT_API OGL3ImmediateContext::IASetPrimitiveTopology( kT::PrimitiveTopology::Topology topology )
    {
        static GLenum look[] = {
            GL_POINTS,
            GL_TRIANGLES,
            GL_TRIANGLE_STRIP,
            GL_LINES,
            GL_LINE_STRIP
        };
        myTopology = look[ topology ];
    }

    void KT_API OGL3ImmediateContext::OMSetRenderTargets(
        Uint32 num,
        kT::OGL3Texture* const* renderTargets,
        kT::OGL3Texture* depthStencilTarget )
    {
        ktOGL3Check( glBindFramebuffer( GL_FRAMEBUFFER, myFBO ) );

        for( size_t i = 0; i < num; i++ )
        {
            ktOGL3Check(
                glFramebufferTexture2D(
                    GL_FRAMEBUFFER,
                    GL_COLOR_ATTACHMENT0 + i,
                    GL_TEXTURE_RECTANGLE,
                    renderTargets[i]->GetHandle(),
                    0
                )
            );
        }

        if( depthStencilTarget != 0 )
            ktOGL3Check(
                glFramebufferTexture2D(
                    GL_FRAMEBUFFER,
                    GL_DEPTH_STENCIL_ATTACHMENT,
                    GL_TEXTURE_RECTANGLE,
                    depthStencilTarget->GetHandle(),
                    0
                )
            );

        static GLenum buffers[] = {
            GL_COLOR_ATTACHMENT0,
            GL_COLOR_ATTACHMENT1,
            GL_COLOR_ATTACHMENT2,
            GL_COLOR_ATTACHMENT3,
            GL_COLOR_ATTACHMENT4,
            GL_COLOR_ATTACHMENT5,
            GL_COLOR_ATTACHMENT6,
            GL_COLOR_ATTACHMENT7,
            GL_COLOR_ATTACHMENT8,
            GL_COLOR_ATTACHMENT9,
            GL_COLOR_ATTACHMENT10,
            GL_COLOR_ATTACHMENT11,
            GL_COLOR_ATTACHMENT12,
            GL_COLOR_ATTACHMENT13,
            GL_COLOR_ATTACHMENT14,
            GL_COLOR_ATTACHMENT15
        };

        ktOGL3Check( glDrawBuffers( num, buffers ) );
    }

    void KT_API OGL3ImmediateContext::MakeCurrent()
    {
        myContext->MakeCurrent();
    }

    bool KT_API OGL3ImmediateContext::Begin()
    {
        return true;
    }

    void KT_API OGL3ImmediateContext::End()
    {
    }

    void KT_API OGL3ImmediateContext::ExecuteCommands( OGL3CommandList* commands )
    {
    }
}
