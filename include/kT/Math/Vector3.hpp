/**
 * \file Math/Vector3.hpp
 * \author Damien Hilloulin
 * \date 19/10/2008
 * \brief Contains the definition of the kT::Vector3< T > class.
 */
#ifndef __KTVECTOR3_HPP__
#define __KTVECTOR3_HPP__

#include <kT/Core/Types.hpp>
#include "Helpers.hpp"
#include "Vector4.hpp"

namespace kT
{
    /**
     * \ingroup ktmath_module
     * \brief Generic class for 3D vectors.
     */
    template< typename T >
    struct Vector3
    {
        T x, y, z;

        /**
         * \brief Defautl detailed constructor.
         */
        Vector3( const T& x_ = T(0),
                    const T& y_ = T(0),
                    const T& z_ = T(0) );

        /**
         * \brief Copy constructor.
         */
        Vector3( const Vector3< T >& other );

		/**
		 * \brief Converts to a point in homogeneous coordinates.
		 */
		Vector4<T> AsPoint4() const;

		/**
		 * \brief Converts to a vector in homogeneous coordinates.
		 */
		Vector4<T> AsVector4() const;

        /**
         * \brief Are-equal operator.
         */
        bool operator==( const Vector3< T >& o ) const;

        /**
         * \brief Are-different operator.
         */
        bool operator!=( const Vector3< T >& o ) const;

        /**
         * \brief Copy operator.
         */
        Vector3< T >& operator=(const Vector3< T >& other);

        /**
         * \brief Returns a new vector, opposite of this one.
         */
        Vector3< T > operator-() const;

        /**
         * \brief Returns a new vector, result of the addition of the vector.
         */
        Vector3< T > operator+(const Vector3< T >& other) const;

        /**
         * \brief Adds the vector.
         */
        Vector3< T >& operator+=(const Vector3< T >& other);

        /**
         * \brief Returns a new vector, result of substraction of the vectors.
         */
        Vector3< T > operator-(const Vector3< T >& other) const;

        /**
         * \brief Substracts the vector.
         */
        Vector3< T >& operator-=(const Vector3< T >& other);

        /**
         * \brief Multiplies with the scalar.
         */
        Vector3< T >& operator*=(const T& s);

        /**
         * \brief Returns a new vector, result of the division by the scalar.
         */
        Vector3< T > operator/(const T& s) const;

        /**
         * \brief Divides by the scalar.
         */
        Vector3< T >& operator/=(const T& s);

        /**
         * \brief Returns the dot product of the two vectors.
         */
        T Dot(const Vector3< T >& other) const;

        /**
         * \brief Performs a cross product.
         */
        Vector3< T > Cross(const Vector3< T >& other) const;

        /**
         * \brief Returns the squared length of the vector.
         */
        T SqrLength() const;

        /**
         * \brief Returns the length of the vector.
         */
        T Length() const;

        /**
         * \brief Normalizes the vector.
         */
        Vector3< T >& Normalize();

        /**
         * \brief Returns the normalized vector.
         */
        Vector3< T > Normalized() const;

        /**
         * \brief Rotates the vector given a unit axis and an angle.
         * \return the reference to the vector after it has been rotated.
         */
        Vector3< T >& Rotate( const Vector3< T >& axis, Scalar angle );

        /**
         * \brief Give a new vector from the rotation.
         */
        Vector3< T > Rotated( const Vector3< T >& axis, Scalar angle ) const;
    };

    typedef Vector3< Uint8 > Vector3ui8;
    typedef Vector3< Uint16 > Vector3ui16;
    typedef Vector3< Uint32 > Vector3ui32;
    typedef Vector3< Int8 > Vector3i8;
    typedef Vector3< Int16 > Vector3i16;
    typedef Vector3< Int32 > Vector3i32;
    typedef Vector3< Float32 > Vector3f32;
    typedef Vector3< Scalar > Vector3sc;

    template< typename T >
    Vector3< T > Abs( const Vector3< T >& v );

    template< typename T >
    Vector3< T > Min( const Vector3< T >& v, const Vector3< T >& w );

    template< typename T >
    Vector3< T > Max( const Vector3< T >& v, const Vector3< T >& w );
}

/**
 * \brief Returns a new vector, result of the product with the scalar.
 */
template< typename T >
kT::Vector3< T > operator*(const T& s, const kT::Vector3< T >& v);

#include "Vector3.inl"

#endif /* __KTVECTOR3_HPP__ */
