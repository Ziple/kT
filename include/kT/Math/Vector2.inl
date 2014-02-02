namespace kT
{
    template< typename T >
    Vector2< T >::Vector2():
     x(T(0)),
     y(T(0))
    {
    }

    template< typename T >
    Vector2< T >::Vector2(const Vector2< T >& other):
     x(other.x),
     y(other.y)
    {
    }

    template< typename T >
    Vector2< T >::Vector2(const T& x_, const T& y_):
     x(x_),
     y(y_)
    {
    }

    template< typename T >
    bool Vector2< T >::operator==( const Vector2< T >& o ) const
    {
        return (x == o.x) && (y == o.y);
    }

    template< typename T >
    bool Vector2< T >::operator!=( const Vector2< T >& o ) const
    {
        return (x != o.x) || (y != o.y);
    }

    template< typename T >
    Vector2< T >& Vector2< T >::operator=(const Vector2< T >& other)
    {
        x = other.x;
        y = other.y;

        return *this;
    }

    template< typename T >
    Vector2< T > Vector2< T >::operator+(const Vector2< T >& other) const
    {
        return Vector2< T >(x + other.x, y + other.y);
    }

    template< typename T >
    Vector2< T >& Vector2< T >::operator+=(const Vector2< T >& other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    template< typename T >
    Vector2< T > Vector2< T >::operator-(const Vector2< T >& other) const
    {
        return Vector2< T >(x - other.x, y - other.y);
    }

    template< typename T >
    Vector2< T >& Vector2< T >::operator-=(const Vector2< T >& other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    template< typename T >
    Vector2< T >& Vector2< T >::operator*=(const T& s)
    {
        x *= s;
        y *= s;

        return *this;
    }

    template< typename T >
    Vector2< T > Vector2< T >::operator/(const T& s) const
    {
        return Vector2< T >(x / s, y /s);
    }

    template< typename T >
    Vector2< T >& Vector2< T >::operator/=(const T& s)
    {
        x /= s;
        y /= s;

        return *this;
    }

    template< typename T >
    T Vector2< T >::Dot(const Vector2< T >& other) const
    {
        return x * other.x + y * other.y;
    }

    template< typename T >
    T Vector2< T >::SqrLength() const
    {
        return x*x + y*y;
    }

    template< typename T >
    T Vector2< T >::Length() const
    {
        return sqrt(x*x + y*y);
    }

    template< typename T >
    Vector2< T >& Vector2< T >::Normalize()
    {
        T len = Length();
        x /= len;
        y /= len;

        return *this;
    }

    template< typename T >
    Vector2< T > Abs( const Vector2< T >& v )
    {
        return Vector2< T >( kT::Abs( v.x ), kT::Abs( v.y ) ); 
    }

    template< typename T >
    Vector2< T > Min( const Vector2< T >& v, const Vector2< T >& w )
    {
        return Vector2< T >( kT::Min( v.x, w.x ), kT::Min( v.y, w.y ) );
    }

    template< typename T >
    Vector2< T > Max( const Vector2< T >& v, const Vector2< T >& w )
    {
        return Vector2< T >( kT::Max( v.x, w.x ), kT::Max( v.y, w.y ) );
    }
}

template< typename T >
kT::Vector2< T > operator*( const T& s, const kT::Vector2< T >& v )
{
    return kT::Vector2< T >(v.x * s, v.y *s, v.z * s);
}