#include <kT/Math/Octree.hpp>
#include <kT/Math/ObjectStream.hpp>

#include <cstdlib>

namespace kT
{
    KT_API Octree::Octree(
        ObjectStream& objStream,
        size_t subdivisionLevel,
        ptrdiff_t start,
        ptrdiff_t end
    ):
     myObjectStream( objStream ),
     myBoundingBox( AABB::fromObjectStream( objStream, start, end ) ),
     myObjectStart( start ),
     myObjectEnd( end ),
     mySubLevels(0)
    {
        if( myObjectEnd > objStream.Size() )
            myObjectEnd = objStream.Size();

        if( subdivisionLevel != 0 
            && (start >= 0)
            && (end >= 0) ){

            mySubLevels = reinterpret_cast<Octree*>( malloc( sizeof(Octree) * 8 ) );

            Vector3f32 subHalfDiagonal = 0.5f * myBoundingBox.HalfDiagonal(); 

            ptrdiff_t ostart = start;
            // constructs all the eight sub octrees
            for( int i = 0; i < 3; i++ ){//face bit index
                for( int b = 0; b <= 1; b++ ){//bit value
                    int subLevelIndex = 2*i+b;

                    float xstep = (i == 0) ? ((b==0) ? -1.f : 1.f) : 0;
                    float ystep = (i == 1) ? ((b==0) ? -1.f : 1.f) : 0;
                    float zstep = (i == 2) ? ((b==0) ? -1.f : 1.f) : 0;

                    Vector3f32 stepv( xstep, ystep, zstep );
                    Vector3f32 subCenter = myBoundingBox.Center() + stepv * myBoundingBox.HalfDiagonal();

                    AABB subAABB( subCenter - subHalfDiagonal, subCenter + subHalfDiagonal );

                    ptrdiff_t oend = -1;
                    ptrdiff_t endl = end;
                    for( ptrdiff_t index = ostart; index < endl; ){

                        if( objStream.IsIn( subAABB, index ) ){
                            ostart++;// next time we will start at ostart, so we inc it.
                            oend++;
                            index++;
                        }else{
                            endl--;
                            objStream.Swap( index, endl );
                        }
                    }

                    // calls the constructor
                    new (mySubLevels+subLevelIndex) Octree( objStream, subdivisionLevel-1, ostart, oend );
                }
            }

            // the remaining objects are in no sub octree
            // so we keep them at this level
            myObjectStart = ostart;
        }
    }

    KT_API Octree::~Octree()
    {
        if( mySubLevels != 0 ){

            for( size_t i = 0; i < 8; i++ ){
                (mySubLevels+i)->~Octree();
            }

            free( mySubLevels );
        }
    }
}