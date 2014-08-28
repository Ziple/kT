#include <kT/Math/IndexedTriangleStream.hpp>
#include <kT/Math/AABB.hpp>

#include <algorithm>

namespace kT
{
    bool KT_API IndexedTriangleStream::IsIn( const AABB& box, size_t index )
    {
        bool ret = true;

        for( size_t i = 0; i < 3; i++ ){
            const Vector4f32& v = myVertices[ myIndices[ 3 * index + i ] ];
            Vector3f32 v3(v.x, v.y, v.z);

            if( !box.IsIn(v3) ){
                ret = false;
                break;
            }
        }

        return ret;
    }

    void KT_API IndexedTriangleStream::Swap( size_t o1, size_t o2 )
    {
        std::swap( myIndices[ 3 * o1 + 0 ], myIndices[ 3 * o2 + 0 ] );
        std::swap( myIndices[ 3 * o1 + 1 ], myIndices[ 3 * o2 + 1 ] );
        std::swap( myIndices[ 3 * o1 + 2 ], myIndices[ 3 * o2 + 2 ] );
    }

    size_t KT_API IndexedTriangleStream::Size() const
    {
        return myIndices.size() / 3;
    }

    Vector3f32 KT_API IndexedTriangleStream::Min( size_t start, size_t end ) const
    {
        size_t numTriangles = Size();
        if( end > numTriangles )
            end = numTriangles;

        float inf = std::numeric_limits<float>::infinity();
        Vector3f32 ret( inf, inf, inf );

        for( size_t i = start; i < end; i++ ){
            const Vector4f32& A = myVertices[ myIndices[ 3 * i + 0 ] ];
            const Vector4f32& B = myVertices[ myIndices[ 3 * i + 0 ] ];
            const Vector4f32& C = myVertices[ myIndices[ 3 * i + 0 ] ];

            Vector3f32 A3( A.x, A.y, A.z );
            Vector3f32 B3( B.x, B.y, B.z );
            Vector3f32 C3( C.x, C.y, C.z );

            Vector3f32 mAB = kT::Min(A3,B3);
            Vector3f32 mABC = kT::Min(mAB, C3);
            ret = kT::Min( ret, mABC );
        }

        return ret;
    }

    Vector3f32 KT_API IndexedTriangleStream::Max( size_t start, size_t end ) const
    {
        size_t numTriangles = Size();
        if( end > numTriangles )
            end = numTriangles;

        float ninf = -std::numeric_limits<float>::infinity();
        Vector3f32 ret( ninf, ninf, ninf );

        for( size_t i = start; i < end; i++ ){
            const Vector4f32& A = myVertices[ myIndices[ 3 * i + 0 ] ];
            const Vector4f32& B = myVertices[ myIndices[ 3 * i + 0 ] ];
            const Vector4f32& C = myVertices[ myIndices[ 3 * i + 0 ] ];

            Vector3f32 A3( A.x, A.y, A.z );
            Vector3f32 B3( B.x, B.y, B.z );
            Vector3f32 C3( C.x, C.y, C.z );

            Vector3f32 mAB = kT::Max(A3,B3);
            Vector3f32 mABC = kT::Max(mAB, C3);
            ret = kT::Max( ret, mABC );
        }

        return ret;
    }
}