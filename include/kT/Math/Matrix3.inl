#include <cmath>
#include <cstring>

namespace kT
{
    template< typename T >
    Matrix3< T >::Matrix3()
    {
    }

    template< typename T >
    Matrix3< T >::Matrix3( const Matrix3< T >& other )
    {
        memcpy( this, &other._11, sizeof(Matrix3< T >) );
    }

    template< typename T >
    Matrix3< T >& Matrix3< T >::operator=( const Matrix3< T >& other )
    {
        memcpy( this, &other._11, sizeof(Matrix3< T >) );
        return *this;
    }

    template< typename T >
    Matrix3< T >& Matrix3< T >::Transpose()
    {
        T swap;

        swap = _12;
        _12 = _21;
        _21 = swap;

        swap = _13;
        _13 = _31;
        _31 = swap;

        swap = _23;
        _23 = _32;
        _32 = swap;

        return *this;
    }

    template< typename T >
    Matrix3< T > Matrix3< T >::GetTransposed() const
    {
        Matrix3< T > r( this );
        return r.Transpose();
    }

    template< typename T >
    Matrix3< T >& Matrix3< T >::LoadIdentity()
    {
        _11 = _22 = _33 = T(1);
        _12 = _13 = _21 = _23 = _31 = _32 = T(0);
        return *this;
    }

    template< typename T >
    Matrix3< T >& Matrix3< T >::BuildScaling( const Vector3< T >& scale )
    {
        _11 = scale.x;
        _22 = scale.y;
        _33 = scale.z;

        _12 = _13 = _21 = _23 = _31 = _32 = T(0)

        return *this;
    }

    template< typename T >
    Matrix3< T >& Matrix3< T >::Scale( const Vector3< T >& scale )
    {
        _11 *= scale.x;
        _21 *= scale.x;
        _31 *= scale.x;

        _12 *= scale.y;
        _22 *= scale.y;
        _32 *= scale.y;

        _13 *= scale.z;
        _23 *= scale.z;
        _33 *= scale.z;

        return *this;
    }

    template< typename T >
    Matrix3< T > Matrix3< T >::GetScaled( const Vector3< T >& scale ) const
    {
        Matrix3 r( this );
        return r.Scale( scale );
    }

    template< typename T >
    Matrix3< T >& Matrix3< T >::BuildRotationX( const T& a )
    {
        T c = std::cos( a );
        T s = std::sin( a );

        _22 = c;
        _23 = s;
        _32 = -s;
        _33 = c;

        _11 = T(1);
        _12 = _13 = _21 = _31 = T(0);

        return *this;
    }

    template< typename T >
    Matrix3< T >& Matrix3< T >::BuildRotationY( const T& a )
    {
        T c = std::cos( a );
        T s = std::sin( a );

        _11 = c;
        _13 = -s;
        _31 = s;
        _33 = c;

        _22 = T(1);
        _12 = _23 = _21 = _32 = T(0);

        return *this;
    }

    template< typename T >
    Matrix3< T >& Matrix3< T >::BuildRotationZ( const T& a )
    {
        T c = std::cos( a );
        T s = std::sin( a );

        _11 = c;
        _12 = s;
        _21 = -s;
        _22 = c;

        _33 = T(1);
        _13 = _23 = _31 = _32 = T(0);

        return *this;
    }

    template< typename T >
    Matrix3< T >& Matrix3< T >::BuildRotation( const Vector3< T >& a )
    {
        float A       = cos(a.x);
        float B       = sin(a.x);
        float C       = cos(a.y);
        float D       = sin(a.y);
        float E       = cos(a.z);
        float F       = sin(a.z);

        float AD      =   A * D;
        float BD      =   B * D;

        _11  =   C * E;
        _21  =  -C * F;
        _31  =  -D;
        _12  = -BD * E + A * F;
        _22  =  BD * F + A * E;
        _32  =  -B * C;
        _13  =  AD * E + B * F;
        _23  = -AD * F + B * E;
        _33 =   A * C;

        return *this;
    }

    template< typename T >
    Matrix3< T >& Matrix3< T >::RotateX( const T& a )
    {
        Matrix3< T > temp;
        temp.BuildRotationX(a);
        
        (*this) *= temp;
        return *this;
    }

    template< typename T >
    Matrix3< T >& Matrix3< T >::RotateY( const T& a )
    {
        Matrix3< T > temp;
        temp.BuildRotationY(a);
        
        (*this) *= temp;
        return *this;
    }

    template< typename T >
    Matrix3< T >& Matrix3< T >::RotateZ( const T& a )
    {
        Matrix3< T > temp;
        temp.BuildRotationZ(a);
        
        (*this) *= temp;
        return *this;
    }

    template< typename T >
    Matrix3< T >& Matrix3< T >::Rotate( const Vector3< T >& a )
    {
        Matrix3< T > temp;
        temp.BuildRotation(a);
        
        (*this) *= temp;
        return *this;
    }

    template< typename T >
    Matrix3< T > Matrix3< T >::GetRotatedX( const T& a ) const
    {
        Matrix3< T > temp;
        temp.BuildRotationX(a);
        return (*this) * temp;
    }

    template< typename T >
    Matrix3< T > Matrix3< T >::GetRotatedY( const T& a ) const
    {
        Matrix3< T > temp;
        temp.BuildRotationY(a);
        return (*this) * temp;
    }

    template< typename T >
    Matrix3< T > Matrix3< T >::GetRotatedZ( const T& a ) const
    {
        Matrix3< T > temp;
        temp.BuildRotationZ(a);
        return (*this) * temp;
    }

    template< typename T >
    Matrix3< T > Matrix3< T >::GetRotated( const Vector3< T >& a ) const
    {
        Matrix3< T > temp;
        temp.BuildRotation(a);
        return (*this) * temp;
    }

    template< typename T >
    Matrix3< T >& Matrix3< T >::operator*=( const Matrix3< T >& other )
    {
        Matrix3& t = *this;
        *this = other * t;
        return *this;
    }
}

template< typename T >
kT::Matrix3< T > operator*( const kT::Matrix3< T >& A, const kT::Matrix3< T >& B )
{
    kT::Matrix3< T > r;

    r._11 = B._11*A._11 + B._12*A._21 + B._13*A._31;
    r._12 = B._11*A._12 + B._12*A._22 + B._13*A._32;
    r._13 = B._11*A._13 + B._12*A._23 + B._13*A._33;

    r._21 = B._21*A._11 + B._22*A._21 + B._23*A._31;
    r._22 = B._21*A._12 + B._22*A._22 + B._23*A._32;
    r._23 = B._21*A._13 + B._22*A._23 + B._23*A._33;

    r._31 = B._31*A._11 + B._32*A._21 + B._33*A._31;
    r._32 = B._31*A._12 + B._32*A._22 + B._33*A._32;
    r._33 = B._31*A._13 + B._32*A._23 + B._33*A._33;

    return r;
}