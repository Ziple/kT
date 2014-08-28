#include <kT/Math/Octree.hpp>
#include <kT/Math/ObjectStream.hpp>

#include <cstdlib>

#include <new>

namespace kT
{
    KT_API Octree::Octree(
        ObjectStream& objStream,
        size_t subdivisionLevel,
        ptrdiff_t start,
        ptrdiff_t end
    ):
     myObjectStream( objStream ),
     myObjectStart( start ),
     myObjectEnd( end )
    {
        for( size_t i = 0; i < 8; i++ )
            mySubLevels[i] = 0;

        if( myObjectEnd > ptrdiff_t( myObjectStream.Size() ) )
            myObjectEnd = ptrdiff_t( myObjectStream.Size() );

        if( myObjectStart < myObjectEnd ){
            myBoundingBox = AABB::fromObjectStream( objStream, start, end );

            if( subdivisionLevel > 0 ){
                Octree* ptr = reinterpret_cast<Octree*>( malloc( sizeof(Octree) * 8 ) );
                for( size_t i = 0; i < 8; i++ )
                    mySubLevels[i] = ptr+i;

                Vector3f32 subHalfDiagonal = 0.5f * myBoundingBox.HalfDiagonal(); 

                ptrdiff_t ostart = myObjectStart;
                ptrdiff_t nostart = ostart;
                // constructs all the eight sub octrees
                for( int i = 0; i < 8; i++ ){//face bit index

                    Vector3f32 stepv;
                    if( i == 0 )
                        stepv = kT::Vector3f32( -0.5f, -0.5f, -0.5f );
                    else if( i== 1 )
                        stepv = kT::Vector3f32( -0.5f, -0.5f, 0.5f );
                    else if( i == 2 )
                        stepv = kT::Vector3f32( -0.5f, 0.5f, 0.5f );
                    else if( i == 3 )
                        stepv = kT::Vector3f32( -0.5f, 0.5f, -0.5f );
                    else if( i == 4 )
                        stepv = kT::Vector3f32( 0.5f, 0.5f, -0.5f );
                    else if( i == 5 )
                        stepv = kT::Vector3f32( 0.5f, 0.5f, 0.5f );
                    else if( i == 6 )
                        stepv = kT::Vector3f32( 0.5f, -0.5f, 0.5f );
                    else if( i == 7 )
                        stepv = kT::Vector3f32( 0.5f, -0.5f, -0.5f );
                    else
                        stepv = kT::Vector3f32( 0.0f, 0.0f, 0.0f );

                    Vector3f32 subCenter = myBoundingBox.Center() + stepv * myBoundingBox.HalfDiagonal();
                    AABB subAABB( subCenter - subHalfDiagonal, subCenter + subHalfDiagonal );

                    ptrdiff_t oend = ostart;
                    ptrdiff_t endl = myObjectEnd;
                    for( ptrdiff_t index = ostart; index < endl; ){
                        if( myObjectStream.IsIn( subAABB, size_t(index) ) ){
                            nostart++;// next time we will start at ostart, so we inc it.
                            oend++;
                            index++;
                        }else{
                            endl--;
                            myObjectStream.Swap( index, endl );
                        }
                    }

                    // calls the constructor
                    new (mySubLevels[i]) Octree( myObjectStream, subdivisionLevel-1, ostart, oend );
                    ostart = nostart;
                }

                // the remaining objects are in no sub octree
                // so we keep them at this level
                myObjectStart = ostart;
            }
        }
    }

    KT_API Octree::~Octree()
    {
        if( mySubLevels[0] != 0 ){

            for( size_t i = 0; i < 8; i++ )
                (mySubLevels[i])->~Octree();

            free( mySubLevels[0] );
        }
    }

    void KT_API Octree::visit( Octree::OctreeVisitorLambda lambda, void* user_data ) const
    {
        lambda( this, user_data );

        if( mySubLevels[0] != 0 )
            for( size_t i = 0; i < 8; i++ )
                mySubLevels[i]->visit( lambda, user_data );
    }
}