/**
 * \file Math/Matrix4.hpp
 * \author Damien Hilloulin
 * \date 21/10/2008
 * \brief Contains the definition of the kT::Matrix4< T > class.
 */
#ifndef __KTMATRIX4_HPP__
#define __KTMATRIX4_HPP__

#include <cstring>
#include <cmath>

#include <kT/Core/Types.hpp>
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace kT
{
    /**
     * \ingroup ktmath_module
     * \brief Generic class for 4x4 matrices.
     */
    template< typename T >
    struct Matrix4
    {
        T _11, _12, _13, _14,
            _21, _22, _23, _24,
            _31, _32, _33, _34,
            _41, _42, _43, _44;

        /**
         * \brief Default constructor.
         *
         * Do nothing. You must initialises the matrix content
         * by yourself with BuildRotation(), BuildTranslation(), and all the other
         * BuildXXX().
         */
        inline Matrix4() {}

        /**
         * \brief Constructor from array.
         */
        inline Matrix4( const T* a );

        /**
         * \brief Copy constructor.
         */
        inline Matrix4( const Matrix4< T >& other );

        /**
         * \brief Loads the identity matrix
         */
        Matrix4< T >& LoadIdentity();

        /**
         * \brief Returns an identity matrix
         */
        static inline Matrix4< T > Identity();

        /**
         * \brief Builds a left-handed look at matrix.
         */
        Matrix4< T >& BuildLookAtLH( const Vector3< T >& pos, const Vector3< T >& at, const Vector3< T >& up );

        /**
         * \brief Returns a left-handed look at matrix.
         */
        static inline Matrix4< T > LookAtLH( const Vector3< T >& pos, const Vector3< T >& at, const Vector3< T >& up );

        /**
         * \brief Builds a right-handed look at matrix.
         */
        Matrix4< T >& BuildLookAtRH( const Vector3< T >& pos, const Vector3< T >& at, const Vector3< T >& up );

        /**
         * \brief Returns a right-handed look at matrix.
         */
        static inline Matrix4< T > LookAtRH( const Vector3< T >& pos, const Vector3< T >& at, const Vector3< T >& up );

        /**
         * \brief Builds a left-handed perspective projection matrix.
         */
        Matrix4< T >& BuildPerspectiveProjectionFOVLH( const T& fovRadians,
                                                        const T& aspectRatio,
                                                        const T& zNear,
                                                        const T& zFar );

        /**
         * \brief Returns a left-handed perspective projection matrix.
         */
        static inline Matrix4< T > PerspectiveProjectionFOVLH( const T& fovRadians,
                                                        const T& aspectRatio,
                                                        const T& zNear,
                                                        const T& zFar );

        /**
         * \brief Builds a right-handed perspective projection matrix.
         */
        Matrix4< T >& BuildPerspectiveProjectionFOVRH( const T& fovRadians,
                                                        const T& aspectRatio,
                                                        const T& zNear,
                                                        const T& zFar );

        /**
         * \brief Returns a right-handed perspective projection matrix.
         */
        static inline Matrix4< T > PerspectiveProjectionFOVRH( const T& fovRadians,
                                                        const T& aspectRatio,
                                                        const T& zNear,
                                                        const T& zFar );

        /**
         * \brief Builds a rotation matrix along the x axis with a radians for angle.
         */
        Matrix4< T >& BuildRotationX( const T& a );

        /**
         * \brief Builds a rotation matrix along the y axis with a radians for angle.
         */
        Matrix4< T >& BuildRotationY( const T& a );

        /**
         * \brief Builds a rotation matrix along the x axis with a radians for angle.
         */
        Matrix4< T >& BuildRotationZ( const T& a );

        /**
         * \brief Builds a rotation matrix from a set of Euler's angles.
         * Yaw, pitch, roll
         */
        Matrix4< T >& BuildRotation( const Vector3< T >& a );

        /**
         * \brief Returns the matrix rotated accordingly.
         */
        Matrix4< T >& RotateX( const T& a );

        /**
         * \brief Returns the matrix rotated accordingly.
         */
        Matrix4< T >& RotateY( const T& a );

        /**
         * \brief Returns the matrix rotated accordingly.
         */
        Matrix4< T >& RotateZ( const T& a );

        /**
         * \brief Returns the matrix rotated accordingly given the euler angles.
         * Yaw, pitch, roll
         */
        Matrix4< T >& Rotate( const Vector3< T >& a );

        /**
         * \brief Returns an new matrix result of the rotation with the given euler angles.
         * Yaw, pitch, roll
         */
        Matrix4< T > GetRotatedX( const T& a ) const;

        /**
         * \brief Returns an new matrix result of the rotation.
         */
        Matrix4< T > GetRotatedY( const T& a ) const;

        /**
         * \brief Returns an new matrix result of the rotation.
         */
        Matrix4< T > GetRotatedZ( const T& a ) const;

        /**
         * \brief Returns an new matrix result of the rotation.
         */
        Matrix4< T > GetRotated( const Vector3< T >& a ) const;

        /**
         * \brief Builds a translation matrix from the translation vector.
         */
        Matrix4< T >& BuildTranslation( const Vector3< T >& t );

        /**
         * \brief Returns the matrix translated accordingly.
         */
        inline Matrix4< T >& Translate( const Vector3< T >& t );

        /**
         * \brief Returns a new matrix image of the matrix translated accordingly.
         */
        inline Matrix4< T > GetTranslated( const Vector3< T >& t );

        /**
         * \brief Builds a scaling matrix from the scaling vector..
         */
        Matrix4< T >& BuildScaling( const Vector3< T >& s );

        /**
         * \brief Performs a in-place scaling.
         */
        Matrix4< T >& Scale( const Vector3< T >& s );

        /**
         * \brief Returns an new matrix result of the scaling.
         */
        Matrix4< T > GetScaled( const Vector3< T >& s ) const;

        /**
         * \brief Returns the transposed matrix, done on place.
         */
        Matrix4< T >& Transpose();

        /**
         * \brief Returns a new matrix, transposed of the former.
         */
        Matrix4< T > GetTransposed() const;

        /**
         * \brief this = o * this.
         */
        Matrix4< T >& operator*=( const Matrix4< T >& o );
    };

    typedef Matrix4< Uint16 > Matrix4ui16;
    typedef Matrix4< Uint32 > Matrix4ui32;
    typedef Matrix4< Float32 > Matrix4f32;
    typedef Matrix4< Float64 > Matrix4f64;
    typedef Matrix4< Scalar > Matrix4sc;
}

/**
* \brief Returns A * B.
*/
template< typename T >
kT::Matrix4< T > operator*( const kT::Matrix4< T >& A, const kT::Matrix4< T >& B );

/**
 * \brief Return the transformed vector.
 */
template< typename T >
kT::Vector3< T > operator*( const kT::Matrix4< T >& M, const kT::Vector3< T >& v );

/**
 * \brief Return the transformed vector.
 */
template< typename T >
kT::Vector4< T > operator*( const kT::Matrix4< T >& M, const kT::Vector4< T >& v );

#include "Matrix4.inl"

#endif /* __KTMATRIX4_HPP__ */
