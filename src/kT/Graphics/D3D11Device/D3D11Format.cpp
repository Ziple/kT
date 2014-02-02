#include <kT/Graphics/D3D11Device/D3D11Format.hpp>
#include <kT/Graphics/PixelFormat.hpp>

#include <DXGI.h>


namespace kT
{
    DXGI_FORMAT KT_API D3D11Format::GetDXGIFormat( PixelFormat::Format format )
    {
        static DXGI_FORMAT lookupTable[] = {
            DXGI_FORMAT_UNKNOWN,
            DXGI_FORMAT_R32G32B32A32_FLOAT,
            DXGI_FORMAT_R32G32B32A32_SINT,
            DXGI_FORMAT_R32G32B32A32_UINT,
            //
            DXGI_FORMAT_R16G16B16A16_FLOAT,
            DXGI_FORMAT_R16G16B16A16_SINT,
            DXGI_FORMAT_R16G16B16A16_UINT,
            DXGI_FORMAT_R16G16B16A16_UNORM,
            //
            DXGI_FORMAT_R8G8B8A8_SINT,
            DXGI_FORMAT_R8G8B8A8_UINT,
            DXGI_FORMAT_R8G8B8A8_UNORM,
            //
            DXGI_FORMAT_R32G32B32_FLOAT,
            DXGI_FORMAT_R32G32B32_SINT,
            DXGI_FORMAT_R32G32B32_UINT,
            //
            DXGI_FORMAT_R32G32_FLOAT,
            DXGI_FORMAT_R32G32_SINT,
            DXGI_FORMAT_R32G32_UINT,
            //
            DXGI_FORMAT_R16G16_FLOAT,
            DXGI_FORMAT_R16G16_SINT,
            DXGI_FORMAT_R16G16_UINT,
            DXGI_FORMAT_R16G16_UNORM,
            //
            DXGI_FORMAT_R8G8_SINT,
            DXGI_FORMAT_R8G8_UINT,
            DXGI_FORMAT_R8G8_UNORM,
            //
            DXGI_FORMAT_R32_FLOAT,
            DXGI_FORMAT_R32_SINT,
            DXGI_FORMAT_R32_UINT,
            //
            DXGI_FORMAT_R16_FLOAT,
            DXGI_FORMAT_R16_SINT,
            DXGI_FORMAT_R16_UINT,
            DXGI_FORMAT_R16_UNORM,
            //
            DXGI_FORMAT_R8_SINT,
            DXGI_FORMAT_R8_UINT,
            DXGI_FORMAT_R8_UNORM,
            // depth-stencil textures formats
            DXGI_FORMAT_D32_FLOAT,
            DXGI_FORMAT_D24_UNORM_S8_UINT,
        };

        return lookupTable[ format ];
    }

}