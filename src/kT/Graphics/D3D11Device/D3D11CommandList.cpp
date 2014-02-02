#include <kT/Graphics/D3D11Device/D3D11CommandList.hpp>

#include <d3d11.h>

namespace kT
{
    KT_API D3D11CommandList::~D3D11CommandList()
    {
        myHandle->Release();
    }
}