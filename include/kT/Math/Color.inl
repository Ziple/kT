namespace kT
{
    template< typename T >
    Color< T >::Color():
     r( 0 ),
     g( T(0) ),
     b( T(0) ),
     a( T(0) )
    {}

    template< typename T >
    Color< T >::Color( const T& r_, const T& g_, const T& b_, const T& a_ ):
     r( r_ ),
     g( g_ ),
     b( b_ ),
     a( a_ )
    {}

    template< typename T >
    Color< T >::Color( const T* components ):
     r( components[0] ),
     g( components[1] ),
     b( components[2] ),
     a( components[3] )
    {}

    template< typename T >
    Color< T >::Color( const Color< T >& other ):
     r( other.r ),
     g( other.g ),
     b( other.b ),
     a( other.a)
    {}
}