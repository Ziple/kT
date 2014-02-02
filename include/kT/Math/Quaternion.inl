#include "Helpers.hpp"

namespace kT
{
    template< typename T >
    Quaternion< T >::Quaternion( const T& x_,
                                     const T& y_,
                                     const T& z_,
                                     const T& w_ ):
     x( x_ ),
     y( y_ ),
     z( z_ ),
     w( w_ )
    {
    }

    template< typename T >
    Quaternion< T >::Quaternion( const Vector3< T >& a )
    {
        BuildFromEuler( a );
    }

    template< typename T >
    Quaternion< T >& Quaternion< T >::operator=( const Quaternion< T >& other )
    {
        w = other.w;
        x = other.x;
        y = other.y;
        z = other.z;

        return *this;
    }

    template< typename T >
    Quaternion< T > Quaternion< T >::operator*( const Quaternion< T >& other ) const
    {
         Quaternion< T > r( T(0), T(0), T(0), T(1) );

         r.w = (w * other.w) - (x * other.x) - (y * other.y) - (z * other.z);
         r.x = (w * other.x) + (x * other.w) + (y * other.z) - (z * other.y);
         r.y = (w * other.y) + (y * other.w) + (z * other.x) - (x * other.z);
         r.z = (w * other.z) + (z * other.w) + (x * other.y) - (y * other.x);

        return r;
    }

    template< typename T >
    Quaternion< T >& Quaternion< T >::operator*=( const Quaternion< T >& other )
    {
        (*this) = (*this) * other;
        return *this;
    }

    template< typename T >
    Quaternion< T >& Quaternion< T >::BuildFromEuler( const Vector3< T >& a )
    {
        const T fYaw = T( a.x * 0.5f ),
                fPitch = T( a.y * 0.5f ),
                fRoll = T( a.z * 0.5f );

        const T cX = std::cos( fPitch ),
                cY = std::cos( fYaw ),
                cZ = std::cos( fRoll ),
                sX = std::sin( fPitch ),
                sY = std::sin( fYaw ),
                sZ = std::sin( fRoll ),
                cYcZ = cY * cZ,
                sYsZ = sY * sZ,
                cYsZ = cY * sZ,
                sYcZ = sY * cZ;

        w = (cX * cYcZ) + (sX * sYsZ);
        x = (sX * cYcZ) - (cX * sYsZ);
        y = (cX * sYcZ) + (sX * cYsZ);
        z = (cX * cYsZ) - (sX * sYcZ);

        return *this;
    }

    template< typename T >
    Quaternion< T >& Quaternion< T >::BuildFromAxisAndAngle( const Vector3< T >& axis, const T& angle )
    {
        const T sina = std::sin( angle/ T(2) ),
                cosa = std::cos( angle / T(2) );

        x = axis.x * sina;
        y = axis.y * sina;
        z = axis.z * sina;
        w = cosa;

        Normalize();
        return *this;
    }

    template< typename T >
    Quaternion< T > Quaternion< T >::GetConjugated() const
    {
        return Quaternion< T >(w, -x, -y, -z);
    }

    template< typename T >
    Quaternion< T >& Quaternion< T >::Conjugate()
    {
        x = -x;
        y = -y;
        z = -z;

        return *this;
    }

    template< typename T >
    Matrix4< T > Quaternion< T >::GetMatrix4() const
    {
        Matrix4< T > r;
        T wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

        x2 = x + x;
        y2 = y + y;
        z2 = z + z;

        xx = x * x2;
        xy = x * y2;
        xz = x * z2;

        yy = y * y2;
        yz = y * z2;
        zz = z * z2;

        wx = w * x2;
        wy = w * y2;
        wz = w * z2;

        r._11 = T(1) - (yy + zz);
        r._12 = xy - wz;
        r._13 = xz + wy;

        r._21 = xy + wz;
        r._22 = T(1) - (xx + zz);
        r._23 = yz - wx;

        r._31 = xz - wy;
        r._32 = yz + wx;
        r._33 = T(1) - (xx + yy);

        r._41 = r._42 = r._43 = T(0);
        r._44 = T(1);

        return r;
    }

    template< typename T >
    AxisAndAngle< T > Quaternion< T >::GetAxisAndAngle() const
    {
        AxisAndAngle< T > axisAndAngle;

        axisAndAngle.angle = std::acos( w ) * T(2);
        axisAndAngle.axis = Vector3< T >( x, y, z );
        axisAndAngle.axis.Normalize();
        return axisAndAngle;
    }

    template< typename T >
    Quaternion< T >& Quaternion< T >::Normalize()
    {
        T n = RcpqSqrt( w*w + x*x + y*y + z*z);

        w *= n;
        x *= n;
        y *= n;
        z *= n;

        return *this;
    }

    template< typename T >
    Quaternion< T > Quaternion< T >::GetNormalized() const
    {
        Quaternion< T > r( *this );
        return r.Normalize();
    }
}