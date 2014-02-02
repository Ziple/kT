#include <kT/Graphics/D3D11Device/Algorithm/ParallelScan.hpp>

#include <kT/Graphics/D3D11Device/D3D11HardwareBuffer.hpp>
#include <kT/Graphics/D3D11Device/D3D11Device.hpp>
#include <kT/Graphics/D3D11Device/D3D11ImmediateContext.hpp>
#include <kT/Core/String.hpp>

#include <vector>

const UINT BLOCK_SIZE = 512;

// Constant Buffer Layout
struct Constants
{
    kT::Uint32 groupX;
    kT::Uint32 groupY;
    kT::Uint32 pad1;
    kT::Uint32 pad2;
};

namespace kT
{
    KT_API ParallelScan::ParallelScan(
        D3D11Device* dev,
        kT::Uint32 numElements
        ):
     myDev( dev ),
     myNumElements( numElements )
    {
        myConstantBuffer = dev->CreateBuffer(
            kT::D3D11HardwareBuffer::ConstantBuffer,
            kT::D3D11HardwareBuffer::DefaultBufferUsage,
            0,
            sizeof(Constants),
            1,
            0 );

#if defined(KT_DEBUG)
        myConstantBuffer->SetName( "ParallelScan::ConstantBuffer" );
#endif

        myTotalCountBuffer = dev->CreateBuffer(
            kT::D3D11HardwareBuffer::UnorderedAccess | kT::D3D11HardwareBuffer::ShaderResource,
                kT::D3D11HardwareBuffer::DefaultBufferUsage,
                0,
                sizeof(kT::Uint32),
                1,
                0 );

#if defined(KT_DEBUG)
        myTotalCountBuffer->SetName( "ParallelScan::TotalCountBuffer" );
#endif

        kT::Uint32 groupX = ((numElements + BLOCK_SIZE-1) / BLOCK_SIZE);
        kT::Uint32 buffSize = groupX * BLOCK_SIZE;

        myNumTempBuffers = CountNecessaryTempBuffers( groupX );
        myTempBuffers = new kT::D3D11HardwareBuffer*[ myNumTempBuffers ];

        kT::Uint32 i = 0;
        while( groupX > 0 )
        {
            myTempBuffers[i] = 
                dev->CreateBuffer(
                kT::D3D11HardwareBuffer::UnorderedAccess | kT::D3D11HardwareBuffer::ShaderResource,
                kT::D3D11HardwareBuffer::DefaultBufferUsage,
                0,
                sizeof(kT::Uint32),
                buffSize,
                0 );

#if defined(KT_DEBUG)
            myTempBuffers[i]->SetName( std::string("ParallelScan::TempBuffers[") + toString(i) + std::string("]") );
#endif

            i++;

            if( groupX == 1 )
                break;

            groupX = (groupX + BLOCK_SIZE-1) / BLOCK_SIZE;
            buffSize = groupX * BLOCK_SIZE;
        }
    }


    KT_API ParallelScan::~ParallelScan()
    {
        for( kT::Uint32 i = 0; i < myNumTempBuffers; i++ )
            delete myTempBuffers[i];
        delete[] myTempBuffers;

        delete myTotalCountBuffer;

        delete myConstantBuffer;
    }

    kT::Uint32 ParallelScan::CountNecessaryTempBuffers( kT::Uint32 groupsX )
    {
        kT::Uint32 i = 0;

        while( groupsX > 0 )
        {
            i++;
            if( groupsX == 1 )
                break;

            groupsX = (groupsX + BLOCK_SIZE-1) / BLOCK_SIZE;
        }

        return i;
    }

    void ParallelScan::DoRecursion(
        D3D11ImmediateContext* ctx,
        D3D11Shader* scanShader,
        D3D11Shader* incrShader,
        kT::Uint32 groupsX,
        kT::Uint32 i
        )
    {
        Constants cb = { groupsX, 1, 0, 0 };
        myConstantBuffer->WriteData( ctx, 0, sizeof(Constants), &cb );
        ctx->CSSetConstantBuffers( 0, 1, &myConstantBuffer );

        kT::D3D11UnorderedAccessResource* uavs[] = {
            myTempBuffers[i],
            groupsX > 1 ? myTempBuffers[i+1] : myTotalCountBuffer
        };

        ctx->CSSetUnorderedAccessResources( 0, 2, uavs );

        ctx->CSSetShader( scanShader );
        ctx->Dispatch( groupsX, 1, 1 );

        uavs[0] = NULL;
        uavs[1] = NULL;
        ctx->CSSetUnorderedAccessResources( 0, 2, uavs );

        if( groupsX > 1 )
        {
            DoRecursion( ctx, scanShader, incrShader, (groupsX + BLOCK_SIZE-1) / BLOCK_SIZE, i+1 );

            kT::D3D11UnorderedAccessResource* uavs[] = {
                myTempBuffers[i],
            };
            ctx->CSSetUnorderedAccessResources( 0, 1, uavs );

            kT::D3D11ShaderResource* srvs[] = {
                myTempBuffers[i+1],
            };
            ctx->CSSetShaderResources( 0, 1, srvs );

            ctx->CSSetShader( incrShader );
            ctx->Dispatch( groupsX, 1, 1 );

            uavs[0] = NULL;
            ctx->CSSetUnorderedAccessResources( 0, 1, uavs );

            srvs[0] = NULL;
            ctx->CSSetShaderResources( 0, 1, srvs );
        }
    }

    void KT_API ParallelScan::Scan(
        D3D11ImmediateContext* ctx,
        D3D11Shader* scanShader,
        D3D11Shader* incrShader,
        D3D11HardwareBuffer* inBuffer,
        D3D11HardwareBuffer* outBuffer
                )
    {
        if( myNumTempBuffers > 0 )
        {
            for( size_t i = 0; i < myNumTempBuffers; i++ )
                ctx->ClearUnorderedAccessResource( myTempBuffers[i], kT::Vector4ui32(0,0,0,0) );

            myTempBuffers[0]->CopyData( ctx, 0, myNumElements * sizeof(kT::Uint32), 0, inBuffer );

            kT::Uint32 groupX = ((myNumElements + BLOCK_SIZE-1) / BLOCK_SIZE);
            DoRecursion( ctx, scanShader, incrShader, groupX, 0 );
            outBuffer->CopyData( ctx, 0, sizeof(kT::Uint32) * myNumElements, 0, myTempBuffers[0] );
        }
    }
}
