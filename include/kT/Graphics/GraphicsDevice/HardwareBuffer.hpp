/**
 * \file Graphics/GraphicsDevice/HardwareBuffer.hpp
 * \author Damien Hilloulin (ziple)
 * \date 28/02/2009
 * \brief Contains the definition of the kT::HardwareBuffer interface.
 */
#ifndef __KTHARDWAREBUFFER_HPP__
#define __KTHARDWAREBUFFER_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>
#include "ImmediateContext.hpp"
#include "ImplementationForwardDeclarations.hpp"

namespace kT
{

    /**
     * \ingroup ktgfxrenderer_module
     * \brief Base class for buffers which contains their data in VRAM.
     *
     * Hardware buffers are buffers stored in VRAM. They can be vertex buffers,
     * index buffers or pixel buffers.
     */
	kTGraphicsDeviceTemplateListDef
    class KT_API HardwareBuffer
    {
        public:
            /**
             * \ingroup ktgfxrenderer_module
             * \brief Enum identifying the type of the hardware buffer.
             */
            enum Type
            {
                IndexBuffer = 1,///< The buffer stores indices and will be an index buffer.
                VertexBuffer = 2,  ///< The buffer is a vertex buffer and stores vertices.
                ConstantBuffer = 4,  ///< The buffer is a constant buffer and stores the constants of a shader.
                ShaderResource = 8,///< The buffer can be mapped as an input to a shader.
                StreamOutput = 16,///< The buffer can receive the output of a stream.
                UnorderedAccess = 32,///< The buffer can be read and written during the same shader stage.
				ProxyBuffer = 64, ///< The buffer is to be used as a copy buffer (staging use)
                ArgumentBuffer = 128//< The buffer will receive the arguments for DrawSomethingIndirect call.
            };

            /**
             * \ingroup ktgfxrenderer_module
             * \brief Enum identifying the usage of the hardware buffer.
             */
            enum Usage
            {
                ImmutableBufferUsage = 0,///< The data is provided once and never change.
                DefaultBufferUsage = 1,  ///< The data is infrequently changed (1- per frame).
                DynamicBufferUsage = 2,  ///< The data is frequently changed (1+ per frame).
				StagingBufferUsage = 3,  //< The buffer is used to copy data from others buffers or to.
            };

            /**
             * \ingroup ktgfxrenderer_module
             * \brief Specifies the types of CPU access allowed for the hardware buffer.
             */
            enum CPUAccessFlag
            {
                CPUReadAccess = 1,         ///< CPU can read the buffer.
                CPUWriteAccess = 2,     ///< CPU can write into the buffer.
                CPUReadWriteAccess = 3,///< CPU can do both.
            };

            /**
             * \ingroup ktgfxrenderer_module
             * \brief Enum determining the different locking modes when mapping.
             */
            enum LockModeFlag
            {
                ReadLock = 1,             ///< Ask for read access.
                WriteLock = 2,         ///< Ask for write access.
                DiscardRangeLock = 4, ///< The mapped range is discarded.
                DiscardBufferLock = 8,///< The whole buffer is discarded.
                NoOverwriteLock = 16, ///< Assure that data used isn't overwrote.
            };


            /**
             * \brief Needed constructor.
             */
            HardwareBuffer() {}

            /**
             * \brief Constructor.
             */
            HardwareBuffer(
				Uint32 bindFlags,
				Usage usage,
				Uint32 cpuAccessRight,
				Uint32 elementSize,
                Uint32 numElements ):
             myType( bindFlags ),
             myUsage( usage ),
             myCPUAccessRights( cpuAccessRight ),
             mySize( elementSize * numElements )
            {}

            /**
             * \brief Virtual destructor.
             */
            virtual ~HardwareBuffer() {}

            /**
             * \brief Reads data from the buffer and copies it at the destination.
             */
            virtual void ReadData(
				ImplImmediateContext* ctx,
				Uint32 offset,
                Uint32 size,
                void* dest
				) = 0;

            /**
             * \brief Writes data from memory to the buffer.
             */
            virtual void WriteData(
				ImplImmediateContext* ctx,
				Uint32 offset,
                Uint32 size,
                const void* src
				) = 0;

            /**
             * \brief Copies data from another buffer into this one.
             */
            virtual void CopyData(
				ImplImmediateContext* ctx,
				Uint32 offset,
                Uint32 size,
                Uint32 srcOffset,
                ImplHardwareBuffer* src
				) = 0;

			/**
			 * \brief Copy the whole content of the source buffer.
			 */
			virtual void CopyBuffer(
				ImplImmediateContext* ctx,
				ImplHardwareBuffer* src
				) = 0;

			/**
			 * \return A new staging buffer with read access containing the data. 
			 */
			virtual ImplHardwareBuffer* GetBufferCopy(
				ImplImmediateContext* ctx
				) = 0;

            /**
             * \brief Maps a range of the buffer.
             * \param lockMode an ORded combination of HardwareBufferLockModeFlag.
             * \param offset from the beginning of the buffer of the start of the range.
             * \param size in bytes of the mapped chunk.
             */
            virtual void* Map( 
				ImplImmediateContext* ctx,
				Uint32 lockMode,
                Uint32 offset,
                Uint32 size
				) = 0;

            /**
             * \brief Unmaps the buffer.
             */
            virtual void Unmap(
				ImplImmediateContext* ctx
				) = 0;

            /**
             * \brief Retrieves the buffer size.
             * \return the size of the buffer (in bytes).
             */
            inline Uint32 GetSize() const {return mySize;}

        protected:

            Uint32 myType;///< Type of the buffer (index/vertex/constant buffer).
            Usage myUsage;///< Usage of the buffer.
            Uint32 myCPUAccessRights;   ///< CPU rights (read/write/read-write).
            Uint32 mySize;               ///< Size of the buffer in bytes.
    };
}

#endif /* __KTHARDWAREBUFFER_HPP__ */
