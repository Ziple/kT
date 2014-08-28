#ifndef __KTINDEXEDTRIANGLESTREAM_HPP__
#define __KTINDEXEDTRIANGLESTREAM_HPP__

#include "../Core/Build.hpp"
#include "ObjectStream.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

#include <vector>

namespace kT
{
    class KT_API IndexedTriangleStream: public ObjectStream
    {
    public:

        IndexedTriangleStream(
            std::vector<unsigned>& indices,
            std::vector<Vector4f32>& vertices
         ):
         myIndices( indices ),
         myVertices( vertices )
        {}

        /**
         * \brief Tells if the object at index is totally in the box or not.
         */
        bool IsIn( const AABB& box, size_t index );

        /**
         * \brief Swap the two triangles given their position in the stream.
         */
        void Swap( size_t index1, size_t index2 );

        /**
         * \brief Returns the number of triangles in the stream.
         */
        size_t Size() const;

        /**
         * \brief Returns the minimal vector between start and end (not included).
         */
        Vector3f32 Min( size_t start = 0, size_t end = std::numeric_limits<size_t>::max() ) const;

        /**
         * \brief Returns the maximal vector between start and end (not included).
         */
        Vector3f32 Max( size_t start = 0, size_t end = std::numeric_limits<size_t>::max() ) const;

        std::vector<unsigned>& Indices() { return myIndices; }

        std::vector<Vector4f32>& Vertices() { return myVertices; }

    protected:

        std::vector<unsigned>& myIndices;
        std::vector<Vector4f32>& myVertices;
    };
}

#endif // __KTINDEXEDTRIANGLESTREAM_HPP__