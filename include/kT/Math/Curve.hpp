/**
 * \file Math/Matrix3.hpp
 * \author Damien Hilloulin
 * \date 07/11/2013
 * \brief Contains the interface for Curves.
 */
#ifndef __KTCURVE_HPP__
#define __KTCURVE_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Math/Vector3.hpp>

#include <vector>

namespace kT
{
    /**
     * Base class for curves. Curves give a point from
     * an absciss s on the curve.
     */
    template< typename PointT, typename TimeT >
    class Curve
    {
    public:

        virtual ~Curve();

        /**
         * \brief Returns the point at the absciss s.
         */
        virtual PointT GetPoint( TimeT s ) = 0;
    };

    /**
     * Implementation of curves for Bezier curves.
     * Bezier curves are a special kind of curves, which given
     * a list of points, will be able to return a curve passing through
     * all those points.
     */
    template< typename PointT, typename TimeT >
    class BezierCurve: public Curve< PointT, TimeT >
    {
        public:

            BezierCurve(
                const std::vector< PointT >& controlPoints
            );

            ~BezierCurve();

            void SetControlPoints( const std::vector< PointT >& controlPoints );

            PointT GetPoint( TimeT s );

        protected:

            std::vector< PointT > myControlPoints;
            PointT* myShadow;
    };
}

#include "Curve.inl"

#endif /* __KTCURVE_HPP__ */