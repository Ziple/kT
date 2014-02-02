#ifndef __KTD3D11INPUTLAYOUT_HPP__
#define __KTD3D11INPUTLAYOUT_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/NonCopyable.hpp>
#include <kT/Graphics/GraphicsDevice/InputLayout.hpp>

#if defined(KT_DEBUG)
#include <string>
#endif

struct ID3D11Device;
struct ID3D11InputLayout;

namespace kT
{
    class KT_API D3D11InputLayout: public InputLayout,
                                   public NonCopyable
    {
        public:

            D3D11InputLayout(
                ID3D11Device* device,
                const void* shaderCode,
                size_t shaderCodeSize,
                const InputLayoutDesc& inputDesc);

            ~D3D11InputLayout();

            ID3D11InputLayout* GetHandle() { return myInputLayout; }

#if defined(KT_DEBUG)
            void SetName( const std::string& name );
#endif

        private:

            ID3D11InputLayout* myInputLayout;
    };
}

#endif /* __KTD3D11INPUTLAYOUT_HPP__ */