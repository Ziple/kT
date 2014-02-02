#define BLOCK_SIZE (512)
#define THREADS_X (BLOCK_SIZE/2)
#define NUM_ELEMENTS BLOCK_SIZE

cbuffer Constants
{
    uint groupX;
    uint groupY;
    uint2 pad;
}

RWStructuredBuffer<uint> Data : register( u0 );
RWStructuredBuffer<uint> Sums : register( u1 );

groupshared unsigned int shared_data[BLOCK_SIZE];

[numthreads(THREADS_X, 1, 1)]
void main( uint3 Gid : SV_GroupID, 
                  uint3 DTid : SV_DispatchThreadID, 
                  uint3 GTid : SV_GroupThreadID, 
                  uint GI : SV_GroupIndex )
{
    // Load shared data
    shared_data[ 2 * GI ] = Data[2 * DTid.x];
    shared_data[ 2 * GI + 1 ] = Data[2 * DTid.x + 1];

    // first step: reduction
    uint i = 1;
    for (uint d = (NUM_ELEMENTS>>1); d > 0; d>>=1 )
    {
        GroupMemoryBarrierWithGroupSync();
        if( GI < d )
        {
            uint ai = i*(2*GI+1)-1;
            uint bi = i*(2*GI+2)-1;
            shared_data[bi] += shared_data[ai];
        }
        i <<= 1;
    }
    
    // second step: propagation
    if( GI == 0 )
    {
        Sums[ Gid.x ] = shared_data[ NUM_ELEMENTS - 1 ];
        shared_data[ NUM_ELEMENTS - 1 ] = 0;
    }

    for ( uint e = 1; e < NUM_ELEMENTS; e <<= 1)
    {
        i >>= 1;
        GroupMemoryBarrierWithGroupSync();
        if ( GI < e )                     
        {
            uint ai = i*(2*GI+1)-1;
            uint bi = i*(2*GI+2)-1;

            uint t = shared_data[ai];
            shared_data[ai] = shared_data[bi];
            shared_data[bi] += t; 
        }
    }


    // Store shared data
    GroupMemoryBarrierWithGroupSync();
    Data[2 * DTid.x] = shared_data[ 2 * GI ];
    Data[2 * DTid.x + 1] = shared_data[ 2 * GI + 1 ];
}