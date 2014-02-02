/**
 * \file Graphics/GraphicsDevice/InputLayout.hpp
 * \author Damien Hilloulin (ziple)
 * \date 28/02/2009
 * \brief Contains the definition of the kT::InputLayout class.
 */
#ifndef __KTINPUTLAYOUT_HPP__
#define __KTINPUTLAYOUT_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>

#include "../PixelFormat.hpp"

namespace kT
{
    /**
     * \ingroup ktgfxrenderer_module
     * \brief Tells wether or not the data is per instance or per vertex.
     */
    enum InputElementClass
    {
        PerVertex = 0,///< The data is per vertex.
        PerInstance = 1,  ///< The data is per instance.
    };

    /**
     * \ingroup ktgfxrenderer_module
     * \brief Describes a single element of the input.
     */
    struct InputElementDesc
    {
        Uint32 inputSlot;            ///< vertex buffer slot providing the element (between 0 and 15).
        const char* role;            ///< role of the element.
        Uint32 index;                ///< Index associated to the element role. Example Color0, Color1...
        PixelFormat::Format format;  ///< format of the element.
        Uint32 byteOffset;           ///< Offset (in bytes) between each element.
        InputElementClass inputClass;///< classification of the element.
        /**
         * number of instances to draw before stepping one unit forward in a vertex
         * buffer filled with instance data.
         */
        Uint32 instanceDataStepRate;
    };

    /**
     * \ingroup ktgfxrenderer_module
     * \brief Structure for describing an input layout.
     */
    struct InputLayoutDesc
    {
        size_t numElements;         ///< Number of elements in the input layout.
        InputElementDesc* inputDesc;///< Descriptions of the elements
    };

    /**
     * \ingroup ktgfxrenderer_module
     * \brief Interface for input layouts.
     *
     * An input layout describes the organization of input data so as to be bound
     * correctly in shaders. They are created and validated against a shader object.
     */
    class KT_API InputLayout
    {
        public:

            /**
             * \brief Constructor for a new input layout.
             * \param numElements Number of elements in the descritpion
             * \param inputDesc Array of elements describing the input. Can be deleted after the call.
             */
            InputLayout(
                const InputLayoutDesc& inputLayoutDesc
				);

            /**
             * \brief Destructor.
             */
            ~InputLayout() { delete[] myInputDescription; }

            /**
             * \brief Returns the number of elements in the input description.
             */
            size_t GetNumElements() const {return myNumInputElements; }

            /**
             * \brief Compute the strides for each vertex buffers.
             * \param stridesArray Array of 16 slots filled with the computed strides.
             */
            void ComputeStrides(
				size_t* stridesArray
				) const;

            /**
             * \brief Returns the description of the input layout.
             * \return The inner pointer of the descritpion. MUST NOT be deleted.
             */
            const InputElementDesc* GetDescription() const { return myInputDescription; }

			/**
			 * \brief Returns the index of the vertex buffer providing this input element.
			 */
			size_t FindSlotProvider(
				const char* role
				) const;

        protected:

            size_t myNumInputElements;
            InputElementDesc* myInputDescription;
    };
}

#endif /* __KTINPUTLAYOUT_HPP__ */
