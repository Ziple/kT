#ifndef __KTAABB_HPP__
#define __KTAABB_HPP__

#include "../Core/Types.hpp"
#include "../Core/Build.hpp"

#include "Vector3.hpp"

#include <cstddef>
#include <limits>

namespace kT
{
    // Forward declarations
    class ObjectStream;

    struct KT_API AABB
    {
        Vector3f32 minv;
        Vector3f32 maxv;

        static AABB fromObjectStream(
            const ObjectStream& objStream,
            size_t start = 0,
            size_t end = std::numeric_limits<size_t>::max()
            );

        AABB(
            const Vector3f32& minv = Vector3f32(0.0f,0.0f,0.0f),
            const Vector3f32& maxv = Vector3f32(0.0f,0.0f,0.0f)
            );

        Vector3f32 Center() const;

        Vector3f32 Diagonal() const;

        Vector3f32 HalfDiagonal() const;

        bool IsXIn( float x ) const;

        bool IsYIn( float y ) const;

        bool IsZIn( float z ) const;

        bool IsIn( const Vector3f32& v ) const;

    };
}

#endif // __KTAABB_HPP__