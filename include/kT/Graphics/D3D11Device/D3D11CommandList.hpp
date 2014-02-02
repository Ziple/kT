#ifndef __KTD3D11COMMANDLIST_HPP__
#define __KTD3D11COMMANDLIST_HPP__

#include <kT/Core/Build.hpp>

struct ID3D11CommandList;

namespace kT
{
    class KT_API D3D11CommandList
    {
        public:

            D3D11CommandList( ID3D11CommandList* commandList ):
             myHandle( commandList )
            {}

            ~D3D11CommandList();

            inline ID3D11CommandList* GetHandle() {return myHandle;}

        protected:

            ID3D11CommandList* myHandle;
    };
}

#endif /* __KTD3D11COMMANDLIST_HPP__ */