#include <kT/Graphics/OGL3Device/OGL3InputLayout.hpp>
#include <kT/Graphics/OGL3Device/OGL3Device.hpp>
#include <kT/Graphics/OGL3Device/OGL3Shader.hpp>
#include <kT/Graphics/OGL3Device/OGL3PixelFormat.hpp>

#include <cstring>

namespace kT
{
    KT_API OGL3InputLayout::OGL3InputLayout(
        OGL3Program* prog,
        const InputLayoutDesc& inputLayoutDesc
    ):
     InputLayout( inputLayoutDesc ),
     myNumberOfElements( inputLayoutDesc.numElements )
    {
        myElements = new OGL3InputElementDesc[myNumberOfElements];

        Uint32 bufferOffsets[16] = {0};

        for( unsigned i = 0; i < myNumberOfElements; i++ )
        {
            const PixelFormatDescriptor& formatDesc = PixelUtility::GetPixelFormatDescriptor( inputLayoutDesc.inputDesc[i].format );
            myElements[i].inputSlot = inputLayoutDesc.inputDesc[i].inputSlot;

            myElements[i].index = inputLayoutDesc.inputDesc[i].index;
            myElements[i].size = formatDesc.ComponentsNumber;
            myElements[i].type = OGL3Format::GetOGL3ComponentTypeFormat( formatDesc.ComponentsDescriptors[0].Type );
            myElements[i].inputClass = inputLayoutDesc.inputDesc[i].inputClass;
            myElements[i].stepRate = inputLayoutDesc.inputDesc[i].instanceDataStepRate;
            myElements[i].attribIndex = glGetAttribLocation( prog->GetProgramID(), inputLayoutDesc.inputDesc[i].role );
            myElements[i].offset = bufferOffsets[ myElements[i].inputSlot ];

            bufferOffsets[ myElements[i].inputSlot ] += formatDesc.GetSize();
        }
    }

    KT_API OGL3InputLayout::~OGL3InputLayout()
    {
        delete[] myElements;
    }

    KT_API OGL3InputElementDesc* OGL3InputLayout::GetElements() const
    {
        return myElements;
    }

    Uint32 KT_API OGL3InputLayout::GetNumberOfElements() const
    {
        return myNumberOfElements;
    }
}