#ifndef __KTD3D11RASTERIZERSTATE_HPP__
#define __KTD3D11RASTERIZERSTATE_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/NonCopyable.hpp>
#include <kT/Graphics/GraphicsDevice/RasterizerState.hpp>

#if defined(KT_DEBUG)
#include <string>
#endif

struct ID3D11Device;
struct ID3D11RasterizerState;

namespace kT
{
    class KT_API D3D11RasterizerState: public NonCopyable
	{
		public:

			D3D11RasterizerState(
				ID3D11Device* device,
				const RasterizerDesc& desc );

			~D3D11RasterizerState();

			inline ID3D11RasterizerState* GetHandle() { return myHandle; }

#if defined(KT_DEBUG)
            void SetName( const std::string& name );
#endif

		protected:

			ID3D11RasterizerState* myHandle;
	};
}

#endif /* __KTD3D11RASTERIZERSTATE_HPP__ */