#ifndef __KTOBJECTSTREAM_HPP__
#define __KTOBJECTSTREAM_HPP__

#include "../Core/Build.hpp"
#include "Vector3.hpp"

#include <cstddef>
#include <limits>

namespace kT
{
    // Forward declarations
    struct AABB;

    /**
     * \brief Base class for object streams.
     */
    class KT_API ObjectStream
    {
    public:

        virtual ~ObjectStream();

        /**
         * \brief Tells if the object at index is totally in the box or not.
         */
        virtual bool IsIn( const AABB& box, size_t index ) = 0;

        /**
         * \brief Swap the objects at the given indices.
         */
        virtual void Swap( size_t index1, size_t index2 ) = 0;

        /**
         * \brief Returns the number of objects in the stream.
         */
        virtual size_t Size() const = 0;
        /**
         * \brief Returns the minimal vector between start and end (not included).
         */
        virtual Vector3f32 Min( size_t start = 0, size_t end = std::numeric_limits<size_t>::max() ) const = 0;

        /**
         * \brief Returns the maximal vector between start and end (not included).
         */
        virtual Vector3f32 Max( size_t start = 0, size_t end = std::numeric_limits<size_t>::max() ) const = 0;
    };
}

#endif // __KTOBJECTSTREAM_HPP__