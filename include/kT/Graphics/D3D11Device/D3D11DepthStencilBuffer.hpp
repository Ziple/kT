#ifndef __KTD3D11DEPTSTENCILBUFFER_HPP__
#define __KTD3D11DEPTSTENCILBUFFER_HPP__

#include <kT/Core/Build.hpp>
#include "D3D11Texture.hpp"

#include <kT/Math/Size.hpp>
#include <kT/Graphics/PixelFormat.hpp>

struct ID3D11Device;
struct IDXGIDepthStencilBuffer;

namespace kT
{
	class D3D11Device;

    class KT_API D3D11DepthStencilBuffer: public D3D11Texture
    {
        public:

			// doesn't have support for multisampling
			D3D11DepthStencilBuffer(
				D3D11Device* device,
				PixelFormat::Format format,
				const kT::Sizeui32& size
				) :
			 D3D11Texture(device, Texture::DepthStencilBuffer, format, size, 0, false)
			{}

			// doesn't have support for multisampling
            D3D11DepthStencilBuffer(
					ID3D11Device* device,
					PixelFormat::Format format,
					const kT::Sizeui32& size
					):
			 D3D11Texture(device, Texture::DepthStencilBuffer, format, size, 0, false )
			{}
    };
}

#endif /* __KTD3D11DEPTSTENCILBUFFER_HPP__ */