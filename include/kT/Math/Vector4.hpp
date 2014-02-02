/**
 * \file Math/Vector4.hpp
 * \author Damien Hilloulin
 * \date 13/04/2013
 * \brief Contains the definition of the kT::Vector4< T > class.
 */
#ifndef __KTVECTOR4_HPP__
#define __KTVECTOR4_HPP__

#include <kT/Core/Types.hpp>

namespace kT
{
    /**
     * \ingroup ktmath_module
     * \brief Generic class for 3D vectors.
     */
    template< typename T >
    struct Vector4
    {
        T x, y, z, w;

        /**
         * \brief Defautl detailed constructor.
         */
        Vector4( const T& x_ = T(0),
                    const T& y_ = T(0),
                    const T& z_ = T(0),
                    const T& w_ = T(0) );

        /**
         * \brief Copy constructor.
         */
        Vector4( const Vector4< T >& other );

        /**
         * \brief Are-equal operator.
         */
        bool operator==( const Vector4< T >& o ) const;

        /**
         * \brief Are-different operator.
         */
        bool operator!=( const Vector4< T >& o ) const;

        /**
         * \brief Copy operator.
         */
        Vector4< T >& operator=(const Vector4< T >& other);

        /**
         * \brief Returns a new vector, opposite of this one.
         */
        Vector4< T > operator-() const;

        /**
         * \brief Returns a new vector, result of the addition of the vector.
         */
        Vector4< T > operator+(const Vector4< T >& other) const;

        /**
         * \brief Adds the vector.
         */
        Vector4< T >& operator+=(const Vector4< T >& other);

        /**
         * \brief Returns a new vector, result of substraction of the vectors.
         */
        Vector4< T > operator-(const Vector4< T >& other) const;

        /**
         * \brief Substracts the vector.
         */
        Vector4< T >& operator-=(const Vector4< T >& other);

        /**
         * \brief Multiplies with the scalar.
         */
        Vector4< T >& operator*=(const T& s);

        /**
         * \brief Returns a new vector, result of the division by the scalar.
         */
        Vector4< T > operator/(const T& s) const;

        /**
         * \brief Divides by the scalar.
         */
        Vector4< T >& operator/=(const T& s);

        /**
         * \brief Returns the dot product of the two vectors.
         */
        T Dot(const Vector4< T >& other) const;

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
        Vector4< T >& Normalize();

        /**
         * \brief Returns the normalized vector.
         */
        Vector4< T > Normalized() const;
    };

    typedef Vector4< Uint8 > Vector4ui8;
    typedef Vector4< Uint16 > Vector4ui16;
    typedef Vector4< Uint32 > Vector4ui32;
    typedef Vector4< Int8 > Vector4i8;
    typedef Vector4< Int16 > Vector4i16;
    typedef Vector4< Int32 > Vector4i32;
    typedef Vector4< Float32 > Vector4f32;
    typedef Vector4< Scalar > Vector4sc;

    template< typename T >
    Vector4< T > Abs( const Vector4< T >& v );

    template< typename T >
    Vector4< T > Min( const Vector4< T >& v, const Vector4< T >& w );

    template< typename T >
    Vector4< T > Max( const Vector4< T >& v, const Vector4< T >& w );
}

/**
 * \brief Returns a new vector, result of the product with the scalar.
 */
template< typename T >
kT::Vector4< T > operator*(const T& s, const kT::Vector4< T >& v);

#include "Vector4.inl"

#endif /* __KTVECTOR4_HPP__ */
