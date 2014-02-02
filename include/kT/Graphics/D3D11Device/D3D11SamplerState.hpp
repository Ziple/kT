#ifndef __KTD3D11SAMPLERSTATE_HPP__
#define __KTD3D11SAMPLERSTATE_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/NonCopyable.hpp>
#include <kT/Graphics/GraphicsDevice/TextureSampler.hpp>

#if defined(KT_DEBUG)
#include <string>
#endif

struct ID3D11Device;
struct ID3D11SamplerState;

namespace kT
{
    class KT_API D3D11SamplerState: public NonCopyable
	{
		public:

			D3D11SamplerState(
				ID3D11Device* device,
				const TextureSamplerDesc& desc );

			~D3D11SamplerState();

			inline ID3D11SamplerState* GetHandle() { return myHandle; }

#if defined(KT_DEBUG)
            void SetName( const std::string& name );
#endif

		protected:

			ID3D11SamplerState* myHandle;
	};
}

#endif /* __KTD3D11SAMPLERSTATE_HPP__ */