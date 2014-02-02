#include <kT/Graphics/OGL3Device/OGL3HardwareBuffer.hpp>
#include <kT/Graphics/OGL3Device/OGL3Check.hpp>
#include <kT/Core/Exceptions.hpp>

#include <cstring>


namespace kT
{
    KT_API OGL3HardwareBuffer::OGL3HardwareBuffer(
                OGL3Device* device,
                Uint32 bindFlags,
                Usage usage,
                Uint32 cpuAccessRight,
                Uint32 elementSize,
                Uint32 numElements,
                const void* data ):
     Base( bindFlags, usage, cpuAccessRight, elementSize, numElements ),
     myDevice( device ),
     myBufferID(0),
     myTarget(0)
    {
        if( (bindFlags & IndexBuffer) != 0 )
			myTarget = GL_ELEMENT_ARRAY_BUFFER;
        else if( (bindFlags & VertexBuffer) != 0 )
            myTarget = GL_ARRAY_BUFFER;
        else if( (bindFlags & ConstantBuffer) != 0 )
            myTarget = GL_UNIFORM_BUFFER;
        else if( (bindFlags & ShaderResource) != 0 )
            myTarget = GL_TEXTURE_BUFFER;
        else if( (bindFlags & StreamOutput) != 0 )
            myTarget = GL_TRANSFORM_FEEDBACK_BUFFER;
        else if( (bindFlags & UnorderedAccess) != 0 )
            myTarget = GL_SHADER_STORAGE_BUFFER;
        else if( (bindFlags & ProxyBuffer) != 0 )
            myTarget = GL_READ_BUFFER;
        else if( (bindFlags & ArgumentBuffer) != 0 )
            myTarget = GL_DRAW_INDIRECT_BUFFER;

        GLenum usageLookupTable[] = {
            GL_STATIC_DRAW,
            GL_STREAM_DRAW,
            GL_DYNAMIC_DRAW,
            GL_DYNAMIC_COPY
        };

        glGenBuffers( 1, &myBufferID );
        glBindBuffer( myTarget, myBufferID );
        glBufferData( myTarget, elementSize*numElements, data, usageLookupTable[ usage ] );
    }

    KT_API OGL3HardwareBuffer::~OGL3HardwareBuffer()
    {
        glDeleteBuffers(1, &myBufferID);
    }

    void KT_API OGL3HardwareBuffer::ReadData(
        OGL3ImmediateContext* ctx,
        Uint32 offset,
        Uint32 size,
        void* dest )
    {
        glBindBuffer( GL_COPY_READ_BUFFER, myBufferID );
        glGetBufferSubData( GL_COPY_READ_BUFFER, offset, size, dest );
    }

    void KT_API OGL3HardwareBuffer::WriteData(
        OGL3ImmediateContext* ctx,
        Uint32 offset,
        Uint32 size,
        const void* src )
    {
        glBindBuffer( GL_COPY_WRITE_BUFFER, myBufferID );
        glBufferSubData( GL_COPY_WRITE_BUFFER, offset, size, src );
    }

    void KT_API OGL3HardwareBuffer::CopyData(
        OGL3ImmediateContext* ctx,
		Uint32 offset,
		Uint32 size,
		Uint32 srcOffset,
		OGL3HardwareBuffer* src )
    {
        glBindBuffer( GL_COPY_READ_BUFFER, src->GetHandle() );
        glBindBuffer( GL_COPY_WRITE_BUFFER, myBufferID );
        glCopyBufferSubData( GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, srcOffset, offset, size );
    }

    void KT_API OGL3HardwareBuffer::CopyBuffer(
        OGL3ImmediateContext* ctx,
        OGL3HardwareBuffer* src )
    {
        Uint32 msize = GetSize();
        Uint32 osize = src->GetSize();
        Uint32 size = msize < osize ? msize : osize;

        CopyData( ctx, 0, size, 0, src );
    }

    KT_API void* OGL3HardwareBuffer::Map(
        OGL3ImmediateContext* ctx,
        Uint32 lockMode,
        Uint32 offset,
        Uint32 size )
    {
        GLuint access = 0;

        access |= (lockMode & ReadLock) ? GL_MAP_READ_BIT : 0;
        access |= (lockMode & WriteLock) ? GL_MAP_WRITE_BIT : 0;
        access |= (lockMode & DiscardRangeLock) ? GL_MAP_INVALIDATE_RANGE_BIT : 0;
        access |= (lockMode & DiscardBufferLock) ? GL_MAP_INVALIDATE_BUFFER_BIT : 0;
        access |= (lockMode & NoOverwriteLock) ? GL_MAP_UNSYNCHRONIZED_BIT : 0;

        glBindBuffer( GL_COPY_READ_BUFFER, myBufferID );
        return glMapBufferRange( GL_COPY_READ_BUFFER, offset, size, access );
    }

    void KT_API OGL3HardwareBuffer::Unmap( OGL3ImmediateContext* ctx )
    {
        glBindBuffer( GL_COPY_READ_BUFFER, myBufferID );
        glUnmapBuffer( GL_COPY_READ_BUFFER );
    }

    KT_API OGL3HardwareBuffer* OGL3HardwareBuffer::GetBufferCopy( OGL3ImmediateContext* ctx )
    {
        OGL3HardwareBuffer* ret = new OGL3HardwareBuffer(
            myDevice,
            kT::OGL3HardwareBuffer::ProxyBuffer,
			kT::OGL3HardwareBuffer::StagingBufferUsage,
			kT::OGL3HardwareBuffer::CPUReadAccess,
			mySize,
            1,
			0 );

        ret->CopyBuffer( ctx, this );
        return ret;
    }
}