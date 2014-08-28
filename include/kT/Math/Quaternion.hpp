/**
 * \file Math/Quaternion.hpp
 * \author Damien Hilloulin
 * \date 21/10/2008
 * \brief Contains the definition of the kT::Quaternion< T > class.
 */
#ifndef __KTQUATERNION_HPP__
#define __KTQUATERNION_HPP__

#include "../Core/Types.hpp"
#include "../Core/Build.hpp"
#include "../Core/Compiler.hpp"
#include "Matrix4.hpp"

namespace kT
{
    template<typename Q>
    struct KT_TEMPLATE_API AxisAndAngle
    {
        Vector3<Q> axis;
        Q angle;
    };

    /**
     * \ingroup ktmath_module
     * \brief Generic class for quaternions.
     * \todo Add some rotate funcs. magnitude
     *
     * The quaternions are commonly used to represent rotations and ensure
     * they are not pertubated by the gimbal lock.
     */
    template< typename T >
    struct KT_TEMPLATE_API Quaternion
    {
        T x, y, z, w;

        /**
         * \brief Default constructor.
         *
         * Sets the components accordingly.
         */
        Quaternion( const T& x = T(0),
                       const T& y = T(0),
                       const T& z = T(0),
                       const T& w = T(1) );

        /**
         * \brief Constructor from a set of Euler angles.
         *
         * The angles are passed like this:
         *  a.x = Yaw;
         *  a.y = Pitch;
         *  a.z = Roll;
         */
        Quaternion( const Vector3< T >& a );

        /**
         * \brief Copies another quaternion.
         */
        Quaternion< T >& operator=(const Quaternion< T >& other);

        /**
         * \brief Returns a new quaternion, result of the combination of both.
         */
        Quaternion< T > operator*(const Quaternion< T >& other) const;

        /**
         * \brief Changes the quaternion by the result of the rotation of both.
         */
        Quaternion< T >& operator*=(const Quaternion< T >& other);

        /**
         * \brief Resets te quaternion according to the euler angle provided.
         *
         * The angles are passed like this:
         *  a.x = Yaw;
         *  a.y = Pitch;
         *  a.z = Roll;
         */
        Quaternion< T >& BuildFromEuler( const Vector3< T >& a );

        /**
         * \brief Resets te quaternion according to the axis and angle provided.
         *
         */
        Quaternion< T >& BuildFromAxisAndAngle( const Vector3< T >& axis, const T& angle );

        /**
         * \brief Returns the conjugated quaternion.
         */
        Quaternion< T > GetConjugated() const;

        /**
         * \brief Conjugates the quaternion.
         */
        Quaternion< T >& Conjugate();

        /**
         * \brief Returns the rotation matrix represented by this quaternion.
         */
        Matrix4< T > GetMatrix4() const;

        AxisAndAngle< T > GetAxisAndAngle() const;

        /**
         * \brief Normalizes the quaternion.
         */
        Quaternion< T >& Normalize();

        /**
         * \brief Returns the normalized quaternion.
         */
        Quaternion< T > GetNormalized() const;
    };

    typedef Quaternion< Uint16 > Quaternionui16;
    typedef Quaternion< Uint32 > Quaternionui32;
    typedef Quaternion< Float32 > Quaternionf32;
    typedef Quaternion< Scalar > Quaternionsc;
}

#include "Quaternion.inl"

#endif /* __KTQUATERNION_HPP__ */
