#ifndef __KTD3D11UNORDEREDACCESSRESOURCE_HPP__
#define __KTD3D11UNORDEREDACCESSRESOURCE_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/NonCopyable.hpp>
#include <kT/Core/Types.hpp>

#if defined(KT_DEBUG)
#include <string>
#endif

struct ID3D11Device;
struct ID3D11UnorderedAccessView;
struct ID3D11Resource;
struct D3D11_UNORDERED_ACCESS_VIEW_DESC;

namespace kT
{
    class KT_API D3D11UnorderedAccessResource: public NonCopyable
	{
		public:

			inline ID3D11UnorderedAccessView* GetUnorderedAccessView() {return myUnorderedView;}

#if defined(KT_DEBUG)
            void SetName( const std::string& name );
#endif
			
		protected:

            D3D11UnorderedAccessResource():
             myUnorderedView( 0 )
            {}

			~D3D11UnorderedAccessResource();

            void CreateUnorderedAccessView(
				ID3D11Device* device,
				ID3D11Resource* reshandle,
                D3D11_UNORDERED_ACCESS_VIEW_DESC* resDesc
				);

			ID3D11UnorderedAccessView* myUnorderedView;
	};

}

#endif /* __KTD3D11UNORDEREDACCESSRESOURCE_HPP__ */