/**
 * \file Math/Vector2.hpp
 * \author Damien Hilloulin
 * \date 21/10/2008
 * \brief Contains the definition of the kT::Vector2< T > class.
 */
#ifndef __KTVECTOR2_HPP__
#define __KTVECTOR2_HPP__

#include "../Core/Types.hpp"
#include "../Core/Build.hpp"
#include "../Core/Compiler.hpp"

namespace kT
{
    /**
     * \ingroup ktmath_module
     * \brief Generic class for 2D vectors.
     * \todo Refactor this.
     */
    template< typename T >
    struct KT_TEMPLATE_API Vector2
    {
        T x, y;

        /**
         * \brief Default constructor.
         */
        Vector2();

        /**
         * \brief Copy constructor.
         */
        Vector2(const Vector2< T >& other);

        /**
         * \brief Detailed constructor.
         */
        Vector2(const T& x_, const T& y_);

        /**
         * \brief Are-equal operator.
         */
        bool operator==( const Vector2< T >& o ) const;

        /**
         * \brief Are-different operator.
         */
        bool operator!=( const Vector2< T >& o ) const;

        /**
         * \brief Copy operator.
         */
        Vector2< T >& operator=(const Vector2< T >& other);

        /**
         * \brief Returns a new vector result of the addition of the two.
         */
        Vector2< T > operator+(const Vector2< T >& other) const;

        /**
         * \brief Adds the vector to this one.
         */
        Vector2< T >& operator+=(const Vector2< T >& other);

        /**
         * \brief Returns a new vector, result of the substraction of the two.
         */
        Vector2< T > operator-(const Vector2< T >& other) const;

        /**
         * \brief Substract the vector to this one.
         */
        Vector2< T >& operator-=(const Vector2< T >& other);


        /* mise à l'échelle */
        Vector2< T >& operator*=(const T& s);

        Vector2< T > operator/(const T& s) const;
        Vector2< T >& operator/=(const T& s);

        T Dot(const Vector2< T >& other) const;

        T SqrLength() const;
        T Length() const;

        Vector2< T >& Normalize();
    };

    typedef Vector2< Uint8 > Vector2ui8;
    typedef Vector2< Uint16 > Vector2ui16;
    typedef Vector2< Uint32 > Vector2ui32;
    typedef Vector2< Int8 > Vector2i8;
    typedef Vector2< Int16 > Vector2i16;
    typedef Vector2< Int32 > Vector2i32;
    typedef Vector2< Float32 > Vector2f32;
    typedef Vector2< Scalar > Vector2sc;

    template< typename T >
    Vector2< T > KT_TEMPLATE_API Abs( const Vector2< T >& v );

    template< typename T >
    Vector2< T > KT_TEMPLATE_API Min( const Vector2< T >& v, const Vector2< T >& w );

    template< typename T >
    Vector2< T > KT_TEMPLATE_API Max( const Vector2< T >& v, const Vector2< T >& w );
}

/**
 * \brief Returns a new vector, result of the product with the scalar.
 */
template< typename T >
kT::Vector2< T > KT_TEMPLATE_API operator*(const T& s, const kT::Vector2< T >& v);

#include "Vector2.inl"

#endif /* __KTVECTOR2_HPP__ */
