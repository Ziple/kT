/**
 * \file OGL3Device/OGL3HardwareBuffer.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/02/2009
 */
#ifndef __KTGLHARDWAREBUFFER_HPP__
#define __KTGLHARDWAREBUFFER_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/NonCopyable.hpp>
#include <kT/Graphics/GraphicsDevice/HardwareBuffer.hpp>
#include "OGL3DeviceTypes.hpp"

#if defined(KT_DEBUG)
#include <string>
#include <vector>
#endif

#include <GL/glew.h>

namespace kT
{
    class KT_API OGL3HardwareBuffer: public kT::HardwareBuffer< kTOGL3DeviceTemplateListLineTypes >
    {
        public:

            typedef kT::HardwareBuffer< kTOGL3DeviceTemplateListLineTypes > Base;

            /**
             * \brief Constructor.
             */
            OGL3HardwareBuffer(
                OGL3Device* device,
                Uint32 bindFlags,
                Usage usage,
                Uint32 cpuAccessRight,
                Uint32 elementSize,
                Uint32 numElements,
                const void* data );

            /**
             * \brief Destructor
             */
            ~OGL3HardwareBuffer();

            /**
             * \brief Returns the handle of the buffer.
             */
            GLuint GetHandle() const {return myBufferID;}

			/**
             * \brief Reads data from the buffer and copies it at the destination.
             */
            void ReadData( OGL3ImmediateContext* ctx,
				Uint32 offset,
				Uint32 size,
				void* dest );

            /**
             * \brief Writes data from memory to the buffer.
             */
            void WriteData( OGL3ImmediateContext* ctx,
				Uint32 offset,
				Uint32 size,
				const void* src );

            /**
             * \brief Copies data from another buffer into this one.
             */
            void CopyData( OGL3ImmediateContext* ctx,
				Uint32 offset,
				Uint32 size,
				Uint32 srcOffset,
				OGL3HardwareBuffer* src );

			/**
			 * \brief Copy the whole content of the source buffer.
			 */
			void CopyBuffer(
				OGL3ImmediateContext* ctx,
				OGL3HardwareBuffer* src
				);

			 /**
             * \brief Maps a range of the buffer.
             * \param lockMode an ORded combination of HardwareBufferLockModeFlag.
             * \param offset from the beginning of the buffer of the start of the range.
             * \param size in bytes of the mapped chunk.
             */
            void* Map( OGL3ImmediateContext* ctx,
					   Uint32 lockMode,
                       Uint32 offset,
                       Uint32 size );

			/**
			 * \brief Unmaps the previously mapped buffer.
			 */
			void Unmap( OGL3ImmediateContext* ctx );

			/**
			 * \return A new staging buffer with read access containing the data. 
			 */
			OGL3HardwareBuffer* GetBufferCopy( OGL3ImmediateContext* ctx );

#if defined(KT_DEBUG)
            void SetName( const std::string& name );
#endif


    protected:

        OGL3Device* myDevice;
        GLuint myBufferID;
        GLenum myTarget;
    };
}

#endif // __KTGLHARDWAREBUFFER_HPP__
