#include <kT/Graphics/D3D11Device/D3D11GraphicsContext.hpp>
#include <kT/Graphics/D3D11Device/D3D11BlendState.hpp>
#include <kT/Graphics/D3D11Device/D3D11RasterizerState.hpp>
#include <kT/Graphics/D3D11Device/D3D11SamplerState.hpp>
#include <kT/Graphics/D3D11Device/D3D11InputLayout.hpp>
#include <kT/Graphics/D3D11Device/D3D11HardwareBuffer.hpp>
#include <kT/Graphics/D3D11Device/D3D11Shader.hpp>
#include <kT/Graphics/D3D11Device/D3D11Texture.hpp>
#include <kT/Graphics/D3D11Device/D3D11Format.hpp>

namespace kT
{
	KT_API D3D11GraphicsContext::~D3D11GraphicsContext()
	{
		if( myHandle != 0 )
			myHandle->Release();
	}

    bool KT_API D3D11GraphicsContext::Begin()
    {
        myHandle->Begin(NULL);
        return true;
    }

    void KT_API D3D11GraphicsContext::End()
    {
        myHandle->End(NULL);
    }

	void KT_API D3D11GraphicsContext::ClearState()
	{
		myHandle->ClearState();
	}

    void KT_API D3D11GraphicsContext::ClearDepthStencilBuffer(
                D3D11Texture* tex,
                Uint32 flags,
                float depth,
                Uint8 stencil )
    {
        myHandle->ClearDepthStencilView( tex->GetDepthStencilView(), flags, depth, stencil );
    }

    void KT_API D3D11GraphicsContext::ClearRenderTarget(
        D3D11Texture* tex,
        const kT::Vector4f32& color )
    {
        myHandle->ClearRenderTargetView( tex->GetRenderTargetView(), &color.x );
    }

    void KT_API D3D11GraphicsContext::ClearUnorderedAccessResource( D3D11UnorderedAccessResource* res, const kT::Vector4f32& v )
    {
        myHandle->ClearUnorderedAccessViewFloat( res->GetUnorderedAccessView(), &v.x );
    }

    void KT_API D3D11GraphicsContext::ClearUnorderedAccessResource( D3D11UnorderedAccessResource* res, const kT::Vector4ui32& v )
    {
        myHandle->ClearUnorderedAccessViewUint( res->GetUnorderedAccessView(), &v.x );
    }

    void KT_API D3D11GraphicsContext::DrawIndexedInstanced(
                Uint32 IndexCountPerInstance,
                Uint32 InstanceCount,
                Uint32 StartIndexLocation,
                Int32 BaseVertexLocation,
                Uint32 StartInstanceLocation
            )
    {
        myHandle->DrawIndexedInstanced( IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation );
    }

    void KT_API D3D11GraphicsContext::DrawIndexedInstancedIndirect( D3D11HardwareBuffer* argsBuffer )
    {
        myHandle->DrawIndexedInstancedIndirect( argsBuffer->GetHandle(), 0 );
    }

	void KT_API D3D11GraphicsContext::GenerateMipMaps( D3D11Texture* tex )
	{
		myHandle->GenerateMips( tex->GetShaderResourceView() );
	}

	void KT_API D3D11GraphicsContext::IASetIndexBuffer(
				D3D11HardwareBuffer* indexBuffer,
				PixelFormat::Format format,
				Uint32 offset )
	{
		if( indexBuffer != 0 )
			myHandle->IASetIndexBuffer( indexBuffer->GetHandle(), D3D11Format::GetDXGIFormat( format ), offset );
		else
			myHandle->IASetIndexBuffer( 0, DXGI_FORMAT_UNKNOWN, 0 );
	}

	void KT_API D3D11GraphicsContext::DrawIndexed( Uint32 indexCount, Uint32 startIndex, Int32 baseVertexLocation )
	{
		myHandle->DrawIndexed( indexCount, startIndex, baseVertexLocation );
	}

	void KT_API D3D11GraphicsContext::IASetInputLayout( D3D11InputLayout* layout )
	{
		if( layout != 0 )
			myHandle->IASetInputLayout( layout->GetHandle() );
		else
			myHandle->IASetInputLayout( 0 );
	}

	void KT_API D3D11GraphicsContext::IASetPrimitiveTopology( kT::PrimitiveTopology::Topology topology )
	{
		myHandle->IASetPrimitiveTopology( (D3D11_PRIMITIVE_TOPOLOGY)topology );
	}

	void KT_API D3D11GraphicsContext::IASetVertexBuffers(
				Uint32 startSlot,
				Uint32 numSlots,
				D3D11HardwareBuffer* const* buffers,
				const Uint32* strides,
				const Uint32* offsets )
	{
		const size_t maxSlotCount = D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;

		ID3D11Buffer* tempBuff[ maxSlotCount ];

        if( buffers != NULL )
		    for( size_t i = 0; i < numSlots; i++ )
		    {
			    if( buffers[i] != 0 )
				    tempBuff[i] = buffers[i]->GetHandle();
			    else
				    tempBuff[i] = 0;
		    }

		myHandle->IASetVertexBuffers(
            startSlot,
            numSlots,
            (buffers != NULL) ? tempBuff : NULL,
            strides,
            offsets );
	}

    void KT_API D3D11GraphicsContext::OMSetRenderTargets(
        Uint32 num,
        kT::D3D11Texture* const* renderTargets,
        kT::D3D11Texture* depthStencilTarget )
    {
        const size_t maxSlotCount = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;

        ID3D11RenderTargetView* tempBuff[ maxSlotCount ];

        if( renderTargets != NULL )
            for( size_t i = 0; i < num; i++ )
                if( renderTargets[i] != 0 )
                    tempBuff[i] = renderTargets[i]->GetRenderTargetView();
                else
                    tempBuff[i] = 0;

        myHandle->OMSetRenderTargets(
            num,
            (renderTargets != NULL) ? tempBuff : NULL,
            (depthStencilTarget != NULL) ? depthStencilTarget->GetDepthStencilView() : NULL );
    }

	void KT_API D3D11GraphicsContext::OMSetBlendState(D3D11BlendState* state, const Vector4f32& blendFactors, Uint32 sampleMask)
	{
		myHandle->OMSetBlendState(state->GetHandle(), &blendFactors.x, sampleMask);
	}

    void KT_API D3D11GraphicsContext::Dispatch( Uint32 groupCountX, Uint32 groupCountY, Uint32 groupCountZ )
    {
        myHandle->Dispatch( groupCountX, groupCountY, groupCountZ );
    }

    void KT_API D3D11GraphicsContext::CSSetConstantBuffers(
		Uint32 startSlot,
		Uint32 numSlots,
		D3D11HardwareBuffer* const* buffers )
	{
		const size_t maxSlotCount = D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;

		ID3D11Buffer* tempBuff[ maxSlotCount ];

        if( buffers != NULL )
		    for( size_t i = 0; i < numSlots; i++ )
		    {
			    if( buffers[i] != 0 )
				    tempBuff[i] = buffers[i]->GetHandle();
			    else
				    tempBuff[i] = 0;
		    }

		myHandle->CSSetConstantBuffers( 
            startSlot,
            numSlots,
            ( buffers != NULL ) ? tempBuff : NULL );
	}

	void KT_API D3D11GraphicsContext::CSSetShader( D3D11Shader* vs )
	{
		if( vs != 0 )
			myHandle->CSSetShader( reinterpret_cast<ID3D11ComputeShader*>( vs->GetHandle() ), 0, 0);
		else
			myHandle->CSSetShader( 0, 0, 0 );
	}

    void KT_API D3D11GraphicsContext::CSSetShaderResources( Uint32 startSlot, Uint32 numSlots, D3D11ShaderResource* const* resources )
    {
        const size_t maxSlotCount = D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;

		ID3D11ShaderResourceView* tempBuff[ maxSlotCount ];

        if( resources != NULL )
		    for( size_t i = 0; i < numSlots; i++ )
		    {
			    if( resources[i] != 0 )
                    tempBuff[i] = resources[i]->GetShaderResourceView();
			    else
				    tempBuff[i] = 0;
		    }

		myHandle->CSSetShaderResources(
            startSlot,
            numSlots,
            ( resources != NULL ) ? tempBuff : NULL );
    }

    void KT_API D3D11GraphicsContext::CSSetUnorderedAccessResources( Uint32 startSlot, Uint32 numSlots, D3D11UnorderedAccessResource* const* resources )
    {
        const size_t maxSlotCount = D3D11_PS_CS_UAV_REGISTER_COUNT;

		ID3D11UnorderedAccessView* tempBuff[ maxSlotCount ];
        UINT tempCounts[ maxSlotCount ];
        memset( tempCounts, 0, sizeof(UINT) * maxSlotCount );

        if( resources != NULL )
		    for( size_t i = 0; i < numSlots; i++ )
		    {
			    if( resources[i] != 0 )
                    tempBuff[i] = resources[i]->GetUnorderedAccessView();
			    else
				    tempBuff[i] = 0;
		    }

            myHandle->CSSetUnorderedAccessViews(
            startSlot,
            numSlots,
            ( resources != NULL ) ? tempBuff : NULL,
            tempCounts );
    }

    void KT_API D3D11GraphicsContext::CSSetSamplers( Uint32 startSlot, Uint32 numSlots, D3D11SamplerState* const* samplers )
    {
		const size_t maxSlotCount = D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT;

		ID3D11SamplerState* tempBuff[ maxSlotCount ];

        if( samplers != NULL )
		    for( size_t i = 0; i < numSlots; i++ )
		    {
			    if( samplers[i] != 0 )
				    tempBuff[i] = samplers[i]->GetHandle();
			    else
				    tempBuff[i] = 0;
		    }

		myHandle->CSSetSamplers(
            startSlot,
            numSlots,
            ( samplers != NULL ) ? tempBuff : NULL );
    }

    void KT_API D3D11GraphicsContext::GSSetConstantBuffers(
		Uint32 startSlot,
		Uint32 numSlots,
		D3D11HardwareBuffer* const* buffers )
	{
		const size_t maxSlotCount = D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;

		ID3D11Buffer* tempBuff[ maxSlotCount ];

        if( buffers != NULL )
		    for( size_t i = 0; i < numSlots; i++ )
		    {
			    if( buffers[i] != 0 )
				    tempBuff[i] = buffers[i]->GetHandle();
			    else
				    tempBuff[i] = 0;
		    }

		myHandle->GSSetConstantBuffers( 
            startSlot,
            numSlots,
            ( buffers != NULL ) ? tempBuff : NULL );
	}

	void KT_API D3D11GraphicsContext::GSSetShader( D3D11Shader* vs )
	{
		if( vs != 0 )
			myHandle->GSSetShader( reinterpret_cast<ID3D11GeometryShader*>( vs->GetHandle() ), 0, 0);
		else
			myHandle->GSSetShader( 0, 0, 0 );
	}

    void KT_API D3D11GraphicsContext::GSSetShaderResources( Uint32 startSlot, Uint32 numSlots, D3D11ShaderResource* const* resources )
    {
        const size_t maxSlotCount = D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;

		ID3D11ShaderResourceView* tempBuff[ maxSlotCount ];

        if( resources != NULL )
		    for( size_t i = 0; i < numSlots; i++ )
		    {
			    if( resources[i] != 0 )
                    tempBuff[i] = resources[i]->GetShaderResourceView();
			    else
				    tempBuff[i] = 0;
		    }

		myHandle->GSSetShaderResources(
            startSlot,
            numSlots,
            ( resources != NULL ) ? tempBuff : NULL );
    }

    void KT_API D3D11GraphicsContext::GSSetSamplers( Uint32 startSlot, Uint32 numSlots, D3D11SamplerState* const* samplers )
    {
		const size_t maxSlotCount = D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT;

		ID3D11SamplerState* tempBuff[ maxSlotCount ];

        if( samplers != NULL )
		    for( size_t i = 0; i < numSlots; i++ )
		    {
			    if( samplers[i] != 0 )
				    tempBuff[i] = samplers[i]->GetHandle();
			    else
				    tempBuff[i] = 0;
		    }

		myHandle->GSSetSamplers(
            startSlot,
            numSlots,
            ( samplers != NULL ) ? tempBuff : NULL );
    }

	void KT_API D3D11GraphicsContext::PSSetConstantBuffers(
		Uint32 startSlot,
		Uint32 numSlots,
		D3D11HardwareBuffer* const* buffers )
	{
		const size_t maxSlotCount = D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;

		ID3D11Buffer* tempBuff[ maxSlotCount ];

        if( buffers != NULL )
		    for( size_t i = 0; i < numSlots; i++ )
		    {
			    if( buffers[i] != 0 )
				    tempBuff[i] = buffers[i]->GetHandle();
			    else
				    tempBuff[i] = 0;
		    }

		myHandle->PSSetConstantBuffers(
            startSlot,
            numSlots,
            ( buffers != NULL ) ? tempBuff : NULL );
	}

	void KT_API D3D11GraphicsContext::PSSetShader( D3D11Shader* vs )
	{
		if( vs != 0 )
			myHandle->PSSetShader( reinterpret_cast<ID3D11PixelShader*>( vs->GetHandle() ), 0, 0);
		else
			myHandle->PSSetShader( 0, 0, 0 );
	}

    void KT_API D3D11GraphicsContext::PSSetShaderResources( Uint32 startSlot, Uint32 numSlots, D3D11ShaderResource* const* resources )
    {
        const size_t maxSlotCount = D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;

		ID3D11ShaderResourceView* tempBuff[ maxSlotCount ];

        if( resources != NULL )
		    for( size_t i = 0; i < numSlots; i++ )
		    {
			    if( resources[i] != 0 )
                    tempBuff[i] = resources[i]->GetShaderResourceView();
			    else
				    tempBuff[i] = 0;
		    }

		myHandle->PSSetShaderResources(
            startSlot,
            numSlots,
            ( resources != NULL ) ? tempBuff : NULL );
    }

    void KT_API D3D11GraphicsContext::PSSetSamplers( Uint32 startSlot, Uint32 numSlots, D3D11SamplerState* const* samplers )
    {
		const size_t maxSlotCount = D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT;

		ID3D11SamplerState* tempBuff[ maxSlotCount ];

        if( samplers != NULL )
		    for( size_t i = 0; i < numSlots; i++ )
		    {
			    if( samplers[i] != 0 )
				    tempBuff[i] = samplers[i]->GetHandle();
			    else
				    tempBuff[i] = 0;
		    }

		myHandle->PSSetSamplers( 
            startSlot,
            numSlots,
            ( samplers != NULL ) ? tempBuff : NULL );
    }

	void KT_API D3D11GraphicsContext::RSSetState( D3D11RasterizerState* state )
	{
		if( state != 0 )
			myHandle->RSSetState( state->GetHandle() );
		else
			myHandle->RSSetState( 0 );
	}

    void KT_API D3D11GraphicsContext::RSSetViewports( Uint32 num, const ViewportDesc* descs )
    {
        myHandle->RSSetViewports( num, reinterpret_cast< const D3D11_VIEWPORT*>( descs ) );
    }

	void KT_API D3D11GraphicsContext::VSSetConstantBuffers(
		Uint32 startSlot,
		Uint32 numSlots,
		D3D11HardwareBuffer* const* buffers )
	{
		const size_t maxSlotCount = D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT;

		ID3D11Buffer* tempBuff[ maxSlotCount ];

        if( buffers != NULL )
		    for( size_t i = 0; i < numSlots; i++ )
		    {
			    if( buffers[i] != 0 )
				    tempBuff[i] = buffers[i]->GetHandle();
			    else
				    tempBuff[i] = 0;
		    }

		myHandle->VSSetConstantBuffers(
            startSlot,
            numSlots,
            ( buffers != NULL ) ? tempBuff : NULL );
	}

	void KT_API D3D11GraphicsContext::VSSetShader( D3D11Shader* vs )
	{
		if( vs != 0 )
			myHandle->VSSetShader( reinterpret_cast<ID3D11VertexShader*>( vs->GetHandle() ), 0, 0);
		else
			myHandle->VSSetShader( 0, 0, 0 );
	}

    void KT_API D3D11GraphicsContext::VSSetShaderResources( Uint32 startSlot, Uint32 numSlots, D3D11ShaderResource* const* resources )
    {
        const size_t maxSlotCount = D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;

		ID3D11ShaderResourceView* tempBuff[ maxSlotCount ];

        if( resources != NULL )
		    for( size_t i = 0; i < numSlots; i++ )
		    {
			    if( resources[i] != 0 )
                    tempBuff[i] = resources[i]->GetShaderResourceView();
			    else
				    tempBuff[i] = 0;
		    }

		myHandle->VSSetShaderResources(
            startSlot,
            numSlots,
            ( resources != NULL ) ? tempBuff : NULL );
    }

    void KT_API D3D11GraphicsContext::VSSetSamplers( Uint32 startSlot, Uint32 numSlots, D3D11SamplerState* const* samplers )
    {
		const size_t maxSlotCount = D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT;

		ID3D11SamplerState* tempBuff[ maxSlotCount ];

        if( samplers != NULL )
		    for( size_t i = 0; i < numSlots; i++ )
		    {
			    if( samplers[i] != 0 )
				    tempBuff[i] = samplers[i]->GetHandle();
			    else
				    tempBuff[i] = 0;
		    }

		myHandle->VSSetSamplers(
            startSlot,
            numSlots,
            ( samplers != NULL ) ? tempBuff : NULL );
    }

#if defined(KT_DEBUG)
    void KT_API D3D11GraphicsContext::SetName( const std::string& name )
    {
        myHandle->SetPrivateData( WKPDID_D3DDebugObjectName, name.length(), name.c_str() );
    }
#endif
}