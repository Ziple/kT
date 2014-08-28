/**
 * \file Math/Octree.hpp
 * \author Damien Hilloulin (ziple)
 * \date 27/08/2014
 * \brief Contains the definitions of the octree class.
 */
#ifndef __KTOCTREE_HPP__
#define __KTOCTREE_HPP__

#include "../Core/Types.hpp"
#include "../Core/Build.hpp"
#include "../Core/Compiler.hpp"

#include "AABB.hpp"

#include <cstddef>
#include <limits>

namespace kT
{
    // Forward declarations
    class ObjectStream;

    /**
     * \brief An octree is a class able to store objects in an optimized manner in 3D dimension.
     */
    class KT_API Octree
    {
    public:

        Octree(
            ObjectStream& objStream,
            size_t subdivisionLevel,
            ptrdiff_t start = 0,
            ptrdiff_t end = std::numeric_limits<ptrdiff_t>::max() );

        ~Octree();

        inline void* operator new( size_t sz, void* here ) { return here ; }

        inline void* operator new[]( size_t sz, void* here ) { return here ; }

    protected:

        ObjectStream& myObjectStream;
        AABB myBoundingBox;
        ptrdiff_t myObjectStart;
        ptrdiff_t myObjectEnd;

        Octree* mySubLevels;
    };

}

#endif // __KTOCTREE_HPP__