#ifndef __KTD3D11FORMAT_HPP__
#define __KTD3D11FORMAT_HPP__

#include <kT/Core/Build.hpp>

enum DXGI_FORMAT;

namespace kT
{
    namespace PixelFormat
    {
        enum Format;
    }

    class KT_API D3D11Format
    {
        public:

            static DXGI_FORMAT GetDXGIFormat( PixelFormat::Format format );
    };
}


#endif /* __KTD3D11FORMAT_HPP__ */