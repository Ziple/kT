#include <kT/Math/AABB.hpp>
#include <kT/Math/ObjectStream.hpp>

namespace kT
{
    AABB KT_API AABB::fromObjectStream(
        const ObjectStream& objStream,
        size_t start,
        size_t end )
    {
        Vector3f32 minv = objStream.Min( start, end );
        Vector3f32 maxv = objStream.Max( start, end );

        return AABB( minv, maxv );
    }

    KT_API AABB::AABB(
        const Vector3f32& minv_,
        const Vector3f32& maxv_
        ):
     minv( minv_ ),
     maxv( maxv_ )
    {}

    Vector3f32 KT_API AABB::Center() const
    {
        return 0.5f * ( minv + maxv );
    }

    Vector3f32 KT_API AABB::Diagonal() const
    {
        return maxv - minv;
    }

    Vector3f32 KT_API AABB::HalfDiagonal() const
    {
        return 0.5f * Diagonal();
    }

    bool KT_API AABB::IsXIn( float x ) const
    {
        return (x >= minv.x) && (x <= maxv.x );
    }

    bool KT_API AABB::IsYIn( float y ) const
    {
        return (y >= minv.y) && (y <= maxv.y );
    }

    bool KT_API AABB::IsZIn( float z ) const
    {
        return (z >= minv.z) && (z <= maxv.z );
    }

    bool KT_API AABB::IsIn( const Vector3f32& v ) const
    {
        return IsXIn(v.x) && IsYIn(v.y) && IsZIn(v.z);
    }
}