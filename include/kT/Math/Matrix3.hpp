/**
 * \file Math/Matrix3.hpp
 * \author Damien Hilloulin
 * \date 21/10/2008
 * \brief Contains the definition of the kT::Matrix3< T > class.
 */
#ifndef __KTMATRIX3_HPP__
#define __KTMATRIX3_HPP__

#include "../Core/Types.hpp"
#include "../Core/Build.hpp"
#include "../Core/Compiler.hpp"

#include "Vector3.hpp"

namespace kT
{
    /**
     * \ingroup ktmath_module
     * \brief Generic structure for 3x3 matrices.
     * \todo Ajouter toutes les fonctions du genre "build rotation".
     *
     * Uses the same convention as DirectX/OpenGL (row majors matrices).
     * 3x3 matrices are like the 4x4 matrices but can't be used for translations.
     */
    template< typename T >
    struct KT_TEMPLATE_API Matrix3
    {
        T _11, _12, _13,
          _21, _22, _23,
          _31, _32, _33;

        /**
         * \brief Default constructor.
         *
         * Doesn't do anything.
         */
        inline Matrix3();

        /**
         * \brief Copy constructor.
         */
        Matrix3( const Matrix3< T >& other );

        /**
         * \brief Copy operator.
         */
        Matrix3< T >& operator=( const Matrix3< T >& other );

        /**
         * \brief Transposes the matrix.
         */
        Matrix3< T >& Transpose();

        /**
         * \brief Returns the transposed matrix.
         */
        Matrix3< T > GetTransposed() const;

        /**
         * \brief Loads the identity matrix.
         */
        Matrix3< T >& LoadIdentity();

        /**
         * \brief Create a scaling the matrix according to the scale vector.
         */
        Matrix3< T >& BuildScaling( const Vector3< T >& scale );

        /**
         * \brief Scales the matrix according to the scale vector.
         */
        Matrix3< T >& Scale( const Vector3< T >& scale );

        /**
         * \brief Returns the scaled matrix along the axis.
         */
        Matrix3< T > GetScaled( const Vector3< T >& scale ) const;

        /**
         * \brief Builds a rotation matrix along the x axis with a radians for angle.
         */
        Matrix3< T >& BuildRotationX( const T& a );

        /**
         * \brief Builds a rotation matrix along the y axis with a radians for angle.
         */
        Matrix3< T >& BuildRotationY( const T& a );

        /**
         * \brief Builds a rotation matrix along the x axis with a radians for angle.
         */
        Matrix3< T >& BuildRotationZ( const T& a );

        /**
         * \brief Builds a rotation matrix from a set of Euler's angles.
         * Yaw, pitch, roll
         */
        Matrix3< T >& BuildRotation( const Vector3< T >& a );

        /**
         * \brief Performs a rotation on the x-axis.
         */
        Matrix3< T >& RotateX( const T& a );

        /**
         * \brief Performs a rotation on the y-axis.
         */
        Matrix3< T >& RotateY( const T& a );

        /**
         * \brief Performs a rotation on the z-axis.
         */
        Matrix3< T >& RotateZ( const T& a );

        /**
         * \brief Performs a rotation given the euler angles.
         */
        Matrix3< T >& Rotate( const Vector3< T >& a );

        /**
         * \brief Returns the rotated matrix along the x-axis.
         */
        Matrix3< T > GetRotatedX( const T& a ) const;

        /**
         * \brief Returns the rotated matrix along the y-axis.
         */
        Matrix3< T > GetRotatedY( const T& a ) const;

        /**
         * \brief Returns the rotated matrix along the z-axis.
         */
        Matrix3< T > GetRotatedZ( const T& a ) const;

        /**
         * \brief Returns the rotated matrix with euler angles.
         */
        Matrix3< T > GetRotated( const Vector3< T >& a ) const;

        /**
         * \brief Multiplies by the other matrix. M = other*M;
         */
        Matrix3< T >& operator*=(const Matrix3< T >& other);
    };

    typedef Matrix3< Uint16 > Matrix3ui16;
    typedef Matrix3< Uint32 > Matrix3ui32;
    typedef Matrix3< Float32 > Matrix3f32;
    typedef Matrix3< Scalar > Matrix3sc;
}

/**
 * \brief Returns A*B.
 */
template< typename T >
kT::Matrix3< T > KT_TEMPLATE_API operator*(const kT::Matrix3< T >& A, const kT::Matrix3< T >& B);

#include "Matrix3.inl"

#endif /* __KTMATRIX3_HPP__ */
