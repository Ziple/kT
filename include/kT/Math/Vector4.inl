#include <cmath>

namespace kT
{
    template< typename T >
    Vector4< T >::Vector4(const T& x_, const T& y_, const T& z_, const T& w_):
     x(x_),
     y(y_),
     z(z_),
     w(w_)
    {
    }

    template< typename T >
    Vector4< T >::Vector4(const Vector4< T >& other):
     x(other.x),
     y(other.y),
     z(other.z),
     w(other.w)
    {
    }

    template< typename T >
    bool Vector4< T >::operator==( const Vector4< T >& o ) const
    {
        return (x == o.x) && (y == o.y) && (z == o.z) && (w == o.w);
    }

    template< typename T >
    bool Vector4< T >::operator!=( const Vector4< T >& o ) const
    {
        return (x != o.x) || (y != o.y) || (z != o.z) || (w != o.w);
    }

    template< typename T >
    Vector4< T >& Vector4< T >::operator=(const Vector4< T >& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;

        return *this;
    }

    template< typename T >
    Vector4< T > Vector4< T >::operator-() const
    {
        return Vector4< T >( -x, -y, -z, -w );
    }

    template< typename T >
    Vector4< T > Vector4< T >::operator+(const Vector4< T >& other) const
    {
        return Vector4< T >(x + other.x, y + other.y, z + other.z, w + other.w );
    }

    template< typename T >
    Vector4< T >& Vector4< T >::operator+=(const Vector4< T >& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;

        return *this;
    }

    template< typename T >
    Vector4< T > Vector4< T >::operator-(const Vector4< T >& other) const
    {
        return Vector4< T >(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    template< typename T >
    Vector4< T >& Vector4< T >::operator-=(const Vector4< T >& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;

        return *this;
    }

    template< typename T >
    Vector4< T >& Vector4< T >::operator*=(const T& s)
    {
        x *= s;
        y *= s;
        z *= s;
        w *= s;

        return *this;
    }

    template< typename T >
    Vector4< T > Vector4< T >::operator/(const T& s) const
    {
        return Vector4< T >(x / s, y /s, z / s, w / s);
    }

    template< typename T >
    Vector4< T >& Vector4< T >::operator/=(const T& s)
    {
        x /= s;
        y /= s;
        z /= s;
        w /= s;

        return *this;
    }

    template< typename T >
    T Vector4< T >::Dot(const Vector4< T >& other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    template< typename T >
    T Vector4< T >::SqrLength() const
    {
        return x*x + y*y + z*z + w*w;
    }

    template< typename T >
    T Vector4< T >::Length() const
    {
        return std::sqrt(x*x + y*y + z*z + w*w);
    }

    template< typename T >
    Vector4< T >& Vector4< T >::Normalize()
    {
        T len = Length();
        x /= len;
        y /= len;
        z /= len;
        w /= len;

        return *this;
    }

    template< typename T >
    Vector4< T > Vector4< T >::Normalized() const
    {
        Vector4< T > r( *this );
        return r.Normalize();
    }

    template< typename T >
    Vector4< T > Abs( const Vector4< T >& v )
    {
        return Vector4< T >( kT::Abs( v.x ), kT::Abs( v.y ), kT::Abs( v.z ), kT::Abs( v.w ) ); 
    }

    template< typename T >
    Vector4< T > Min( const Vector4< T >& v, const Vector4< T >& w )
    {
        return Vector4< T >( kT::Min( v.x, w.x ), kT::Min( v.y, w.y ), kT::Min( v.z, w.z ), kT::Min( v.w, w.w ) );
    }

    template< typename T >
    Vector4< T > Max( const Vector4< T >& v, const Vector4< T >& w )
    {
        return Vector4< T >( kT::Max( v.x, w.x ), kT::Max( v.y, w.y ), kT::Max( v.z, w.z ), kT::Max( v.w, w.w ) );
    }
}

template< typename T >
kT::Vector4< T > operator*( const T& s, const kT::Vector4< T >& v )
{
    return kT::Vector4< T >(v.x * s, v.y *s, v.z * s, v.w * s);
}
