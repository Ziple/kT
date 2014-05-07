#include <kT/Graphics/D3D11Device/D3D11HardwareBuffer.hpp>
#include <kT/Graphics/D3D11Device/D3D11Device.hpp>
#include <kT/Graphics/D3D11Device/D3D11ImmediateContext.hpp>
#include <kT/Core/Exceptions.hpp>

#include "D3D11.h"

namespace kT
{
	KT_API D3D11HardwareBuffer::D3D11HardwareBuffer(
		D3D11Device* device,
		Uint32 bindFlags,
		Usage usage,
		Uint32 cpuAccessRight,
		Uint32 elementSize,
		Uint32 numElements,
		const void* dataPtr):
	D3D11HardwareBuffer(
		device->GetHandle(),
		bindFlags,
		usage,
		cpuAccessRight,
		elementSize,
		numElements,
		dataPtr
		)
	{}

    KT_API D3D11HardwareBuffer::D3D11HardwareBuffer(
        ID3D11Device* device,
        Uint32 bindFlags,
        Usage usage,
        Uint32 cpuAccessRight,
        Uint32 elementSize,
        Uint32 numElements,
        const void* dataPtr ):
	 myDevice( device ),
	 kT::D3D11HardwareBuffer::Base( bindFlags, usage, cpuAccessRight, elementSize, numElements ) 
    {
            D3D11_USAGE bufferUsage[] = 
            {
                D3D11_USAGE_IMMUTABLE,
                D3D11_USAGE_DEFAULT,
                D3D11_USAGE_DYNAMIC,
				D3D11_USAGE_STAGING,
            };

            UINT cpuAccessFlag[] =
            {
                0,
                D3D11_CPU_ACCESS_READ,
                D3D11_CPU_ACCESS_WRITE,
                D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE,
            };

        D3D11_SUBRESOURCE_DATA data;
        data.pSysMem = dataPtr;
        data.SysMemPitch = 0;
        data.SysMemSlicePitch = 0;

        D3D11_BUFFER_DESC bd;
        bd.BindFlags = 0;
        bd.CPUAccessFlags = cpuAccessFlag[ cpuAccessRight ];
        bd.MiscFlags = 0;
        bd.ByteWidth = mySize;
        bd.StructureByteStride = elementSize;

        bd.Usage = bufferUsage[ usage ];
		if( usage != kT::D3D11HardwareBuffer::StagingBufferUsage )
        {
            if( (bindFlags & IndexBuffer) != 0 )
			    bd.BindFlags |= D3D11_BIND_INDEX_BUFFER;
            if( (bindFlags & VertexBuffer) != 0 )
			    bd.BindFlags |= D3D11_BIND_VERTEX_BUFFER;
            if( (bindFlags & ConstantBuffer) != 0 )
			    bd.BindFlags |= D3D11_BIND_CONSTANT_BUFFER;
            if( (bindFlags & ShaderResource) != 0 )
            {
			    bd.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
                bd.MiscFlags |= D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
            }
            if( (bindFlags & StreamOutput) != 0 )
                bd.BindFlags |= D3D11_BIND_STREAM_OUTPUT;
            if( (bindFlags & UnorderedAccess) != 0 )
            {
                bd.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
                bd.MiscFlags |= D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
            }
            if( (bindFlags & ArgumentBuffer) != 0 )
            {
                bd.MiscFlags |= D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS;
            }
        }

        HRESULT hr = device->CreateBuffer( &bd, dataPtr != NULL ? &data : NULL, &myBuffer );
        if( FAILED(hr) )
            kTLaunchException( kT::Exception, "Failed to create the buffer" );

        if( (bindFlags & ShaderResource) != 0 )
        {
            D3D11_SHADER_RESOURCE_VIEW_DESC resDesc;
            resDesc.Format = DXGI_FORMAT_UNKNOWN;
            resDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
            resDesc.Buffer.FirstElement = 0;
            resDesc.Buffer.NumElements = numElements;

            D3D11ShaderResource::CreateShaderResourceView( device, myBuffer, &resDesc );
        }

        if( (bindFlags & UnorderedAccess) != 0 )
        {
            D3D11_UNORDERED_ACCESS_VIEW_DESC resDesc;
            resDesc.Format = DXGI_FORMAT_UNKNOWN;
            resDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
            resDesc.Buffer.FirstElement = 0;
            resDesc.Buffer.NumElements = numElements;
            resDesc.Buffer.Flags = 0;

            D3D11UnorderedAccessResource::CreateUnorderedAccessView( device, myBuffer, &resDesc );
        }
    }

    KT_API D3D11HardwareBuffer::~D3D11HardwareBuffer()
    {
        myBuffer->Release();
    }

	/**
	 * \brief Reads data from the buffer and copies it at the destination.
	 */
	void KT_API D3D11HardwareBuffer::ReadData(
		D3D11ImmediateContext* ctx,
		Uint32 offset,
		Uint32 size,
		void* dest )
	{
		if( (myCPUAccessRights & kT::D3D11HardwareBuffer::CPUReadAccess) != 0 )
		{
			memcpy( dest, Map( ctx, kT::D3D11HardwareBuffer::ReadLock, offset, size ), size );
			Unmap( ctx );
		}
		else
		{
			D3D11HardwareBuffer* copy = GetBufferCopy(ctx);
			memcpy( dest, copy->Map( ctx, D3D11HardwareBuffer::ReadLock, offset, size ), size );
			copy->Unmap( ctx );
			delete copy;
		}
	}

	/**
	 * \brief Writes data from memory to the buffer.
	 */
	void KT_API D3D11HardwareBuffer::WriteData(
		D3D11ImmediateContext* ctx,
		Uint32 offset,
		Uint32 size,
		const void* src )
	{
        if( (myType & ConstantBuffer) == 0 )
        {
		    D3D11_BOX dstBox;
		    dstBox.left = offset;
		    dstBox.top = 0;
		    dstBox.bottom = 1;
		    dstBox.right = offset + size;
		    dstBox.back = 1;
		    dstBox.front = 0;
		    ctx->GetHandle()->UpdateSubresource( GetHandle(), 0, &dstBox, src, 0, 0 );
        }
        else
            ctx->GetHandle()->UpdateSubresource( GetHandle(), 0, NULL, src, 0, 0 );
	}

	/**
	 * \brief Copies data from another buffer into this one.
	 */
	void KT_API D3D11HardwareBuffer::CopyData(
		D3D11ImmediateContext* ctx,
		Uint32 offset,
		Uint32 size,
		Uint32 srcOffset,
		D3D11HardwareBuffer* src )
	{
		D3D11_BOX srcBox;
		srcBox.left = srcOffset;
		srcBox.top = 0;
		srcBox.bottom = 1;
		srcBox.right = srcOffset + size;
		srcBox.back = 1;
		srcBox.front = 0;

		ctx->GetHandle()->CopySubresourceRegion( GetHandle(), 0, offset, 0, 0, src->GetHandle(), 0, &srcBox );
	}

	void KT_API D3D11HardwareBuffer::CopyBuffer(
		D3D11ImmediateContext* ctx,
		D3D11HardwareBuffer* src )
	{
		ctx->GetHandle()->CopyResource( GetHandle(), src->GetHandle() );
	}

	KT_API void* D3D11HardwareBuffer::Map(
		D3D11ImmediateContext* ctx,
		Uint32 lockMode,
		Uint32 offset,
		Uint32 size )
	{
		D3D11_MAP mapType;

		if( (lockMode & kT::D3D11HardwareBuffer::NoOverwriteLock) != 0 )
			mapType = D3D11_MAP_WRITE_NO_OVERWRITE;
		else if( (lockMode & kT::D3D11HardwareBuffer::DiscardBufferLock) != 0 )
			mapType = D3D11_MAP_WRITE_DISCARD;
		else if( (lockMode & kT::D3D11HardwareBuffer::WriteLock) != 0 )
		{
			if( (lockMode & kT::D3D11HardwareBuffer::ReadLock) != 0 )
				mapType = D3D11_MAP_READ_WRITE;
			else
				mapType = D3D11_MAP_WRITE;
		}
		else
			mapType = D3D11_MAP_READ;

		D3D11_MAPPED_SUBRESOURCE sub;
		ctx->GetHandle()->Map( myBuffer, 0, mapType, 0, &sub );

		return reinterpret_cast<Uint8*>( sub.pData ) + offset;
	}

	void KT_API D3D11HardwareBuffer::Unmap( D3D11ImmediateContext* ctx )
	{
		ctx->GetHandle()->Unmap( myBuffer, 0 );
	}

	/**
	* \brief Returns the copy of a part of a buffer.
	* \return A pointer to the copy of the buffer (must be deleted afterward)
	*/
	KT_API D3D11HardwareBuffer* D3D11HardwareBuffer::GetBufferCopy( D3D11ImmediateContext* ctx )
	{
		D3D11HardwareBuffer* copyBuff = new D3D11HardwareBuffer(
			myDevice,
			kT::D3D11HardwareBuffer::ProxyBuffer,
			kT::D3D11HardwareBuffer::StagingBufferUsage,
			kT::D3D11HardwareBuffer::CPUReadAccess,
			mySize,
            1,
			0 );
		ctx->GetHandle()->CopyResource( copyBuff->GetHandle(), myBuffer );
		return copyBuff;
	}

#if defined(KT_DEBUG)
    void KT_API D3D11HardwareBuffer::SetName( const std::string& name )
    {
        myBuffer->SetPrivateData( WKPDID_D3DDebugObjectName, name.length(), name.c_str() );
        D3D11ShaderResource::SetName( name + std::string(" SRV") );
        D3D11UnorderedAccessResource::SetName( name + std::string(" UAV") );
    }
#endif
}