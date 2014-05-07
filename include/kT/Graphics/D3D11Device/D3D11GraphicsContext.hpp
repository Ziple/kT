#ifndef __KTD3D11GRAPHICSCONTEXT_HPP__
#define __KTD3D11GRAPHICSCONTEXT_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>
#include <kT/Core/NonCopyable.hpp>
#include <kT/Graphics/PixelFormat.hpp>
#include <kT/Graphics/GraphicsDevice/PrimitiveTopology.hpp>
#include <kT/Math/Vector4.hpp>

#include <D3D11.h>

#if defined(KT_DEBUG)
#include <string>
#endif

namespace kT
{
    struct ViewportDesc;

	class D3D11HardwareBuffer;
	class D3D11BlendState;
	class D3D11RasterizerState;
    class D3D11SamplerState;
	class D3D11InputLayout;
	class D3D11Shader;
	class D3D11Texture;
    class D3D11ShaderResource;
    class D3D11UnorderedAccessResource;

	class KT_API D3D11GraphicsContext: public kT::NonCopyable
	{
		public:

			D3D11GraphicsContext( ID3D11DeviceContext* handle ):
			 myHandle( handle )
			{}

			~D3D11GraphicsContext();

			ID3D11DeviceContext* GetHandle() {return myHandle;}

            bool Begin();

            void End();

			void ClearState();

            void ClearDepthStencilBuffer(
                D3D11Texture* tex,
                Uint32 flags,
                float depth = 1.0f,
                Uint8 stencil = 0 );

            void ClearRenderTarget( D3D11Texture* tex, const kT::Vector4f32& color );

            void ClearUnorderedAccessResource( D3D11UnorderedAccessResource* res, const kT::Vector4ui32& v );

            void ClearUnorderedAccessResource( D3D11UnorderedAccessResource* res, const kT::Vector4f32& v );

			void GenerateMipMaps( D3D11Texture* tex );

			void DrawIndexed( Uint32 indexCount, Uint32 startIndex, Int32 baseVertexLocation );

            void DrawIndexedInstanced(
                Uint32 IndexCountPerInstance,
                Uint32 InstanceCount,
                Uint32 StartIndexLocation,
                Int32 BaseVertexLocation,
                Uint32 StartInstanceLocation
            );

            void DrawIndexedInstancedIndirect( D3D11HardwareBuffer* argsBuffer );

			void IASetIndexBuffer(
				D3D11HardwareBuffer* indexBuffer,
				PixelFormat::Format format,
				Uint32 offset );

			void IASetInputLayout( D3D11InputLayout* layout );

			void IASetVertexBuffers(
				Uint32 startSlot,
				Uint32 numSlots,
				D3D11HardwareBuffer* const* buffers,
				const Uint32* strides,
				const Uint32* offsets );

			void IASetPrimitiveTopology( kT::PrimitiveTopology::Topology topology );

            void OMSetRenderTargets( Uint32 num, kT::D3D11Texture* const* renderTargets, kT::D3D11Texture* depthStencilTarget );

			void OMSetBlendState( D3D11BlendState* state, const Vector4f32& blendFactors = Vector4f32(1.0f,1.0f,1.0f,1.0f), Uint32 sampleMask = 0xFFFFFFFF );

            void Dispatch( Uint32 groupCountX, Uint32 groupCountY, Uint32 groupCountZ );

            void CSSetConstantBuffers( Uint32 startSlot, Uint32 numSlots, D3D11HardwareBuffer* const* buffers );

			void CSSetShader( D3D11Shader* gs );

            void CSSetShaderResources( Uint32 startSlot, Uint32 numSlots, D3D11ShaderResource* const* resources );

            void CSSetSamplers( Uint32 startSlot, Uint32 numSlots, D3D11SamplerState* const* samplers );

            void CSSetUnorderedAccessResources( Uint32 startSlot, Uint32 numSlots, D3D11UnorderedAccessResource* const* resources );

            void GSSetConstantBuffers( Uint32 startSlot, Uint32 numSlots, D3D11HardwareBuffer* const* buffers );

			void GSSetShader( D3D11Shader* gs );

            void GSSetShaderResources( Uint32 startSlot, Uint32 numSlots, D3D11ShaderResource* const* resources );

            void GSSetSamplers( Uint32 startSlot, Uint32 numSlots, D3D11SamplerState* const* samplers );

			void PSSetConstantBuffers( Uint32 startSlot, Uint32 numSlots, D3D11HardwareBuffer* const* buffers );

			void PSSetShader( D3D11Shader* ps );

            void PSSetShaderResources( Uint32 startSlot, Uint32 numSlots, D3D11ShaderResource* const* resources );

            void PSSetSamplers( Uint32 startSlot, Uint32 numSlots, D3D11SamplerState* const* samplers );

			void RSSetState( D3D11RasterizerState* state );

            void RSSetViewports( Uint32 numViewports, const ViewportDesc* descs );

			void VSSetConstantBuffers( Uint32 startSlot, Uint32 numSlots, D3D11HardwareBuffer* const* buffers );

			void VSSetShader( D3D11Shader* vs );

            void VSSetShaderResources( Uint32 startSlot, Uint32 numSlots, D3D11ShaderResource* const* resources );

            void VSSetSamplers( Uint32 startSlot, Uint32 numSlots, D3D11SamplerState* const* samplers );

#if defined(KT_DEBUG)
            void SetName( const std::string& name );
#endif

		protected:

			ID3D11DeviceContext* myHandle;
	};

}

#endif /* __KTD3D11GRAPHICSCONTEXT_HPP__ */
