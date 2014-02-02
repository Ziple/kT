#include <cstring>

namespace kT
{
    template< typename PointT, typename TimeT >
    Curve::~Curve() {}

    template< typename PointT, typename TimeT >
    BezierCurve::BezierCurve(
        const std::vector< PointT >& controlPoints
        ):
     myShadow( 0 )
    {
        SetControlPoints( controlPoints );
    }

    template< typename PointT, typename TimeT >
    BezierCurve::~BezierCurve()
    {
        delete[] myShadow;
    }

    template< typename PointT, typename TimeT >
    void BezierCurve::SetControlPoints( const std::vector< PointT >& controlPoints )
    {
        if( myShadow != 0 )
            delete[] myShadow;

        myControlPoints = controlPoints;

        myShadow = new PointT[ myControlPoints.size() ];

    }

    template< typename PointT, typename TimeT >
    PointT BezierCurve::GetPoint( TimeT lambda )
    {
        TimeT s = (TimeT(1) - lambda);
        TimeT d = lambda;

        PointT ret;
        memcpy( myShadow, &myControlPoints[0], sizeof(PointT) * myControlPoints.size() );

        unsigned numPoints = myControlPoints.size();
        while( numPoints > 1 )
        {
            for( int i = 0; i < numPoints - 1; i++ )
                myShadow[i] = s * myShadow[i] + d * myShadow[i+1];
            numPoints--;
        }

        return myShadow[0];
    }
}