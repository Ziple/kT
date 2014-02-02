#include <cmath>

namespace kT
{
    template< typename T >
    Vector3< T >::Vector3(const T& x_, const T& y_, const T& z_):
     x(x_),
     y(y_),
     z(z_)
    {
    }

    template< typename T >
    Vector3< T >::Vector3(const Vector3< T >& other):
     x(other.x),
     y(other.y),
     z(other.z)
    {
    }

    template< typename T >
    bool Vector3< T >::operator==( const Vector3< T >& o ) const
    {
        return (x == o.x) && (y == o.y) && (z == o.z);
    }

    template< typename T >
    bool Vector3< T >::operator!=( const Vector3< T >& o ) const
    {
        return (x != o.x) || (y != o.y) || (z != o.z);
    }

    template< typename T >
    Vector3< T >& Vector3< T >::operator=(const Vector3< T >& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;

        return *this;
    }

    template< typename T >
    Vector3< T > Vector3< T >::operator-() const
    {
        return Vector3< T >( -x, -y, -z );
    }

    template< typename T >
    Vector3< T > Vector3< T >::operator+(const Vector3< T >& other) const
    {
        return Vector3< T >(x + other.x, y + other.y, z + other.z);
    }

    template< typename T >
    Vector3< T >& Vector3< T >::operator+=(const Vector3< T >& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }

    template< typename T >
    Vector3< T > Vector3< T >::operator-(const Vector3< T >& other) const
    {
        return Vector3< T >(x - other.x, y - other.y, z - other.z);
    }

    template< typename T >
    Vector3< T >& Vector3< T >::operator-=(const Vector3< T >& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;

        return *this;
    }

    template< typename T >
    Vector3< T >& Vector3< T >::operator*=(const T& s)
    {
        x *= s;
        y *= s;
        z *= s;

        return *this;
    }

    template< typename T >
    Vector3< T > Vector3< T >::operator/(const T& s) const
    {
        return Vector3< T >(x / s, y /s, z / s);
    }

    template< typename T >
    Vector3< T >& Vector3< T >::operator/=(const T& s)
    {
        x /= s;
        y /= s;
        z /= s;

        return *this;
    }

    template< typename T >
    T Vector3< T >::Dot(const Vector3< T >& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    template< typename T >
    Vector3< T > Vector3< T >::Cross(const Vector3< T >& other) const
    {
        return Vector3< T >(y * other.z - z * other.y,
                          z * other.x - x * other.z,
                          x * other.y - y * other.x);
    }

    template< typename T >
    T Vector3< T >::SqrLength() const
    {
        return x*x + y*y + z*z;
    }

    template< typename T >
    T Vector3< T >::Length() const
    {
        return std::sqrt(x*x + y*y + z*z);
    }

    template< typename T >
    Vector3< T >& Vector3< T >::Normalize()
    {
        T len = Length();
        x /= len;
        y /= len;
        z /= len;

        return *this;
    }

    template< typename T >
    Vector3< T > Vector3< T >::Normalized() const
    {
        Vector3< T > r( *this );
        return r.Normalize();
    }

    template< typename T >
    Vector3< T >& Vector3< T >::Rotate( const Vector3< T >& axis, Scalar angle )
    {
        // Projection of the vector on the axis. (i.e the part that is not rotated)
        Vector3< T > proj = Dot(axis) * axis;
        // Part of the vector in the orthogonal of the axis. (i.e the part that is rotated)
        // First vector of the local basis.
        Vector3< T > ortho = (*this) - proj;
        // The second vector of the basis.
        Vector3< T > y = axis.Cross( x );

        (*this) = proj + ( std::cos(angle) * ortho + std::sin(angle) * y );
        return *this;
    }

    template< typename T >
    Vector3< T > Vector3< T >::Rotated( const Vector3< T >& axis, Scalar angle ) const
    {
        // Projection of the vector on the axis. (i.e the part that is not rotated)
        Vector3< T > proj = Dot(axis) * axis;
        // Part of the vector in the orthogonal of the axis. (i.e the part that is rotated)
        // First vector of the local basis.
        Vector3< T > ortho = (*this) - proj;
        // The second vector of the basis.
        Vector3< T > y = axis.Cross( x );

        return proj + ( std::cos(angle) * ortho + std::sin(angle) * y );
    }

    template< typename T >
    Vector3< T > Abs( const Vector3< T >& v )
    {
        return Vector3< T >( kT::Abs( v.x ), kT::Abs( v.y ), kT::Abs( v.z ) ); 
    }

    template< typename T >
    Vector3< T > Min( const Vector3< T >& v, const Vector3< T >& w )
    {
        return Vector3< T >( kT::Min( v.x, w.x ), kT::Min( v.y, w.y ), kT::Min( v.z, w.z ) );
    }

    template< typename T >
    Vector3< T > Max( const Vector3< T >& v, const Vector3< T >& w )
    {
        return Vector3< T >( kT::Max( v.x, w.x ), kT::Max( v.y, w.y ), kT::Max( v.z, w.z ) );
    }
}

template< typename T >
kT::Vector3< T > operator*( const T& s, const kT::Vector3< T >& v )
{
    return kT::Vector3< T >(v.x * s, v.y *s, v.z * s);
}
