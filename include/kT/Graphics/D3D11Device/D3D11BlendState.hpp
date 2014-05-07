#ifndef __KTD3D11BLENDSTATE_HPP__
#define __KTD3D11BLENDSTATE_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/NonCopyable.hpp>
#include <kT/Graphics/GraphicsDevice/BlendState.hpp>

#if defined(KT_DEBUG)
#include <string>
#endif

struct ID3D11Device;
struct ID3D11BlendState;

namespace kT
{
	class D3D11Device;

	class KT_API D3D11BlendState: public NonCopyable
	{
	public:

		D3D11BlendState(
			D3D11Device* device,
			const BlendStateDesc& desc);

		D3D11BlendState(
			ID3D11Device* device,
			const BlendStateDesc& desc);

		~D3D11BlendState();

		inline ID3D11BlendState* GetHandle() { return myHandle; }

		static D3D11BlendState* CreateNoBlendingState(D3D11Device* device);

		static D3D11BlendState* CreateNoBlendingState(ID3D11Device* device);

		static D3D11BlendState* CreateAlphaBlendingState(D3D11Device* device);

		static D3D11BlendState* CreateAlphaBlendingState(ID3D11Device* device);

		static D3D11BlendState* CreateAdditiveBlendingState(D3D11Device* device);

		static D3D11BlendState* CreateAdditiveBlendingState(ID3D11Device* device);

#if defined(KT_DEBUG)
		void SetName(const std::string& name);
#endif

	protected:

		ID3D11BlendState* myHandle;
	};
}
#endif /*__KTD3D11BLENDSTATE_HPP__*/