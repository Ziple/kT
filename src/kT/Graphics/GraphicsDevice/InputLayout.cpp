#include <kT/Graphics/GraphicsDevice/InputLayout.hpp>

#include <cstring>

namespace kT
{
	KT_API InputLayout::InputLayout(
        const InputLayoutDesc& inputLayoutDesc )
	{
		myNumInputElements = inputLayoutDesc.numElements;
		myInputDescription = new InputElementDesc[ myNumInputElements ];
		for( size_t i = 0; i < myNumInputElements; i++ )
			myInputDescription[ i ] = inputLayoutDesc.inputDesc[ i ];
	}

	void KT_API InputLayout::ComputeStrides( size_t* stridesArray ) const
	{
        memset( stridesArray, 0, sizeof(size_t)*16);

		for( size_t i = 0; i < this->myNumInputElements; i++ )
        {
            kT::Uint32 slot = this->myInputDescription[ i ].inputSlot;
            const kT::PixelFormatDescriptor& formatdesc = PixelUtility::GetPixelFormatDescriptor( this->myInputDescription[ i ].format );
			stridesArray[ slot ] += formatdesc.GetSize();
        }
	}

	size_t KT_API InputLayout::FindSlotProvider( const char* role ) const
	{
		size_t i = 0;

		for( ; i < myNumInputElements; i++ )
		{
			if( strcmp(myInputDescription[i].role, role) == 0 )
				break;
		}

		return myInputDescription[i].inputSlot;
	}
}