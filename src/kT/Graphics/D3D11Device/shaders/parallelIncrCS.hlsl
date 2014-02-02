#define BLOCK_SIZE (512)
#define THREADS_X (BLOCK_SIZE/2)

StructuredBuffer<uint> Incr : register( s0 );
RWStructuredBuffer<uint> Data : register( u0 );

[numthreads(THREADS_X, 1, 1)]
void main( uint3 Gid : SV_GroupID, 
                  uint3 DTid : SV_DispatchThreadID, 
                  uint3 GTid : SV_GroupThreadID, 
                  uint GI : SV_GroupIndex )
{
    // As L1 cache is slightly faster than group shared memory,
    // we don't use such memory to hold the value of Incr[ Gid.x ]
    uint incr = Incr[ Gid.x ];
    Data[ 2 * DTid.x ] += incr;
    Data[ 2 * DTid.x  + 1 ] += incr;
}