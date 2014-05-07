#ifndef __KTD3D11HARDWARE_BUFFER__
#define __KTD3D11HARDWARE_BUFFER__

#include <kT/Core/Build.hpp>
#include <kT/Core/NonCopyable.hpp>
#include <kT/Graphics/GraphicsDevice/HardwareBuffer.hpp>
#include "D3D11DeviceTypes.hpp"
#include "D3D11ShaderResource.hpp"
#include "D3D11UnorderedAccessResource.hpp"

#if defined(KT_DEBUG)
#include <string>
#include <vector>
#endif

struct ID3D11Device;
struct ID3D11Buffer;

namespace kT
{
	class D3D11Device;
	class D3D11ImmediateContext;

    class KT_API D3D11HardwareBuffer: public kT::HardwareBuffer< kTD3D11DeviceTemplateListLineTypes >,
                                      public D3D11ShaderResource,
                                      public D3D11UnorderedAccessResource
    {
        public:

			typedef kT::HardwareBuffer< kTD3D11DeviceTemplateListLineTypes > Base;

#if defined(KT_DEBUG)
            template< typename T >
            std::vector<T> DebugBuffer( D3D11Device* dev, D3D11ImmediateContext* ctx )
            {
                D3D11HardwareBuffer* readBackBuff = dev->CreateBuffer(
                    kT::D3D11HardwareBuffer::ProxyBuffer,
                    kT::D3D11HardwareBuffer::StagingBuffer,
                    kT::D3D11HardwareBuffer::ReadAccess,
                    sizeof(T),
                    this->GetSize()/sizeof(T),
                    NULL );
                readBackBuff->CopyBuffer( ctx, this );

                std::vector<T> data( this->GetSize()/sizeof(T) );
                void* ptr = readBackBuff->Map( ctx, kT::D3D11HardwareBuffer::ReadLock, 0, this->GetSize() );
                memcpy( &data[0], ptr, this->GetSize() );
                readBackBuff->Unmap( ctx );
                return data;
            }
#endif

			D3D11HardwareBuffer(D3D11Device* device,
				Uint32 bindFlags,
				Usage usage,
				Uint32 cpuAccessRight,
				Uint32 elementSize,
				Uint32 numElements,
				const void* data);

            D3D11HardwareBuffer( ID3D11Device* device,
                                  Uint32 bindFlags,
                                  Usage usage,
                                  Uint32 cpuAccessRight,
                                  Uint32 elementSize,
                                  Uint32 numElements,
                                  const void* data );

            ~D3D11HardwareBuffer();

            ID3D11Buffer* GetHandle() const {return myBuffer;}

			/**
             * \brief Reads data from the buffer and copies it at the destination.
             */
            void ReadData( D3D11ImmediateContext* ctx,
				Uint32 offset,
				Uint32 size,
				void* dest );

            /**
             * \brief Writes data from memory to the buffer.
             */
            void WriteData( D3D11ImmediateContext* ctx,
				Uint32 offset,
				Uint32 size,
				const void* src );

            /**
             * \brief Copies data from another buffer into this one.
             */
            void CopyData( D3D11ImmediateContext* ctx,
				Uint32 offset,
				Uint32 size,
				Uint32 srcOffset,
				D3D11HardwareBuffer* src );

			/**
			 * \brief Copy the whole content of the source buffer.
			 */
			void CopyBuffer(
				D3D11ImmediateContext* ctx,
				D3D11HardwareBuffer* src
				);

			 /**
             * \brief Maps a range of the buffer.
             * \param lockMode an ORded combination of HardwareBufferLockModeFlag.
             * \param offset from the beginning of the buffer of the start of the range.
             * \param size in bytes of the mapped chunk.
             */
            void* Map( D3D11ImmediateContext* ctx,
					   Uint32 lockMode,
                       Uint32 offset,
                       Uint32 size );

			/**
			 * \brief Unmaps the previously mapped buffer.
			 */
			void Unmap( D3D11ImmediateContext* ctx );

			/**
			 * \return A new staging buffer with read access containing the data. 
			 */
			D3D11HardwareBuffer* GetBufferCopy( D3D11ImmediateContext* ctx );

#if defined(KT_DEBUG)
            void SetName( const std::string& name );
#endif

        protected:

			ID3D11Device* myDevice;
            ID3D11Buffer* myBuffer;
    };
}

#endif /* __KTD3D11HARDWARE_BUFFER__ */