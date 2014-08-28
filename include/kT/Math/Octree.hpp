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
#include <array>
#include <functional>

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

        typedef std::function< void ( const Octree*, void* ) > OctreeVisitorLambda;

        Octree(
            ObjectStream& objStream,
            size_t subdivisionLevel = 0,
            ptrdiff_t start = 0,
            ptrdiff_t end = std::numeric_limits<ptrdiff_t>::max() );

        ~Octree();

        void visit( OctreeVisitorLambda lambda, void* userData ) const;

        ObjectStream& GetObjectStream() const { return myObjectStream; }

        const AABB& GetBoundingBox() const { return myBoundingBox; }

        const std::array< Octree*, 8 >& GetSubLevels() const { return mySubLevels; }

    protected:

        ObjectStream& myObjectStream;
        AABB myBoundingBox;
        ptrdiff_t myObjectStart;
        ptrdiff_t myObjectEnd;

        std::array< Octree*, 8 > mySubLevels;
    };

}

#endif // __KTOCTREE_HPP__