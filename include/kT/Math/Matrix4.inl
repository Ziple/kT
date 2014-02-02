#include <algorithm>

namespace kT
{
    template< typename T >
    Matrix4< T >::Matrix4( const T* a )
    {
        memcpy( &_11, a, sizeof(T) * 16 );
    }

    template< typename T >
    Matrix4< T >::Matrix4( const Matrix4< T >& other )
    {
        memcpy( &_11, &(other._11), sizeof(T) * 16 );
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::LoadIdentity()
    {
        _11 = _22 = _33 = _44 = T(1);
        _12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _34 = _41 = _42 = _43 = T(0);
        return *this;
    }

    template< typename T >
    Matrix4< T > Matrix4< T >::Identity()
    {
        Matrix4< T > id;
        id.LoadIdentity();
        return id;
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::BuildLookAtLH( const Vector3< T >& pos,
                                           const Vector3< T >& at,
                                           const Vector3< T >& up )
    {
        Vector3< T > zaxis = at - pos;
        zaxis.Normalize();

        Vector3< T > xaxis = up.Cross(zaxis);
        xaxis.Normalize();

        Vector3< T > yaxis = zaxis.Cross(xaxis);

        _11 = (T)xaxis.x;
        _12 = (T)yaxis.x;
        _13 = (T)zaxis.x;
        _14 = 0;

        _21 = (T)xaxis.y;
        _22 = (T)yaxis.y;
        _23 = (T)zaxis.y;
        _24 = 0;

        _31 = (T)xaxis.z;
        _32 = (T)yaxis.z;
        _33 = (T)zaxis.z;
        _34 = 0;

        _41 = (T)-xaxis.Dot(pos);
        _42 = (T)-yaxis.Dot(pos);
        _43 = (T)-zaxis.Dot(pos);
        _44 = 1;

        return *this;
    }

    template< typename T >
    Matrix4< T > Matrix4< T >::LookAtLH( const Vector3< T >& pos,
                                           const Vector3< T >& at,
                                           const Vector3< T >& up )
    {
        Matrix4< T > mat;
        mat.BuildLookAtLH( pos, at, up );
        return mat;
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::BuildLookAtRH( const Vector3< T >& pos,
                                           const Vector3< T >& at,
                                           const Vector3< T >& up )
    {
        Vector3< T > zaxis = pos - at;
        zaxis.Normalize();

        Vector3< T > xaxis = up.Cross(zaxis);
        xaxis.Normalize();

        Vector3< T > yaxis = zaxis.Cross(xaxis);

        _11 = (T)xaxis.x;
        _12 = (T)yaxis.x;
        _13 = (T)zaxis.x;
        _14 = 0;

        _21 = (T)xaxis.y;
        _22 = (T)yaxis.y;
        _23 = (T)zaxis.y;
        _24 = 0;

        _31 = (T)xaxis.z;
        _32 = (T)yaxis.z;
        _33 = (T)zaxis.z;
        _34 = 0;

        _41 = (T)-xaxis.Dot(pos);
        _42 = (T)-yaxis.Dot(pos);
        _43 = (T)-zaxis.Dot(pos);
        _44 = 1;

        return *this;
    }

    template< typename T >
    Matrix4< T > Matrix4< T >::LookAtRH( const Vector3< T >& pos,
                                           const Vector3< T >& at,
                                           const Vector3< T >& up )
    {
        Matrix4< T > mat;
        mat.BuildLookAtRH( pos, at, up );
        return mat;
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::BuildPerspectiveProjectionFOVLH( const T& fov,
                                                            const T& aspectRatio,
                                                            const T& zNear,
                                                            const T& zFar )
    {
        const double h = 1.0/ std::tan( fov * 0.5 );
        const T w = T(h / aspectRatio);
        const T q = zFar/(zFar-zNear);

        _11 = w;
        _12 = 0;
        _13 = 0;
        _14 = 0;

        _21 = 0;
        _22 = (T)h;
        _23 = 0;
        _24 = 0;

        _31 = 0;
        _32 = 0;
        _33 = q;
        _34 = 1;

        _41 = 0;
        _42 = 0;
        _43 = -q * zNear;
        _44 = 0;

        return *this;
    }

    template< typename T >
    Matrix4< T > Matrix4< T >::PerspectiveProjectionFOVLH( const T& fov,
                                                            const T& aspectRatio,
                                                            const T& zNear,
                                                            const T& zFar )
    {
        Matrix4< T > mat;
        mat.BuildPerspectiveProjectionFOVLH( fov, aspectRatio, zNear, zFar );
        return mat;
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::BuildPerspectiveProjectionFOVRH( const T& fov,
                                                            const T& aspectRatio,
                                                            const T& zNear,
                                                            const T& zFar )
    {
        const double h = 1.0/ std::tan( fov * 0.5 );
        const T w = T(h / aspectRatio);
        const T q = zFar/(zNear-zFar);

        _11 = w;
        _12 = 0;
        _13 = 0;
        _14 = 0;

        _21 = 0;
        _22 = (T)h;
        _23 = 0;
        _24 = 0;

        _31 = 0;
        _32 = 0;
        _33 = q;
        _34 = -1;

        _41 = 0;
        _42 = 0;
        _43 = q * zNear;
        _44 = 0;

        return *this;
    }

    template< typename T >
    Matrix4< T > Matrix4< T >::PerspectiveProjectionFOVRH( const T& fov,
                                                            const T& aspectRatio,
                                                            const T& zNear,
                                                            const T& zFar )
    {
        Matrix4< T > mat;
        mat.BuildPerspectiveProjectionFOVRH( fov, aspectRatio, zNear, zFar );
        return mat;
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::BuildRotationX( const T& a )
    {
        T c = std::cos( a );
        T s = std::sin( a );

        _22 = c;
        _23 = s;
        _32 = -s;
        _33 = c;

        _11 = _44 = T(1);
        _12 = _13 = _14 = _21 = _24 = _31 = _34 = _41 = _42 = _43 = T(0);

        return *this;
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::BuildRotationY( const T& a )
    {
        T c = std::cos( a );
        T s = std::sin( a );

        _11 = c;
        _13 = -s;
        _31 = s;
        _33 = c;

        _22 = _44 = T(1);
        _12 = _23 = _14 = _21 = _24 = _32 = _34 = _41 = _42 = _43 = T(0);

        return *this;
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::BuildRotationZ( const T& a )
    {
        T c = std::cos( a );
        T s = std::sin( a );

        _11 = c;
        _12 = s;
        _21 = -s;
        _22 = c;

        _33 = _44 = T(1);
        _13 = _14 = _23 = _24 = _31 = _32 = _34 = _41 = _42 = _43 = T(0);

        return *this;
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::BuildRotation( const Vector3< T >& a )
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
        _31  =  D;
        _12  = BD * E + A * F;
        _22  =  -BD * F + A * E;
        _32  =  -B * C;
        _13  =  -AD * E + B * F;
        _23  = AD * F + B * E;
        _33 =   A * C;

        _41 = _42 = _43 = _14 = _24 = _34 = T(0);
        _44 = T(1);

        return *this;
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::RotateX( const T& a )
    {
        Matrix4< T > temp;
        temp.BuildRotationX(a);
        
        (*this) *= temp;
        return *this;
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::RotateY( const T& a )
    {
        Matrix4< T > temp;
        temp.BuildRotationY(a);
        
        (*this) *= temp;
        return *this;
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::RotateZ( const T& a )
    {
        Matrix4< T > temp;
        temp.BuildRotationZ(a);
        
        (*this) *= temp;
        return *this;
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::Rotate( const Vector3< T >& a )
    {
        Matrix4< T > temp;
        temp.BuildRotation(a);
        
        (*this) *= temp;
        return *this;
    }

    template< typename T >
    Matrix4< T > Matrix4< T >::GetRotatedX( const T& a ) const
    {
        Matrix4< T > temp;
        temp.BuildRotationX(a);
        return (*this) * temp;
    }

    template< typename T >
    Matrix4< T > Matrix4< T >::GetRotatedY( const T& a ) const
    {
        Matrix4< T > temp;
        temp.BuildRotationY(a);
        return (*this) * temp;
    }

    template< typename T >
    Matrix4< T > Matrix4< T >::GetRotatedZ( const T& a ) const
    {
        Matrix4< T > temp;
        temp.BuildRotationZ(a);
        return (*this) * temp;
    }

    template< typename T >
    Matrix4< T > Matrix4< T >::GetRotated( const Vector3< T >& a ) const
    {
        Matrix4< T > temp;
        temp.BuildRotation(a);
        return (*this) * temp;
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::BuildTranslation( const Vector3< T >& t )
    {
        _41 = t.x;
        _42 = t.y;
        _43 = t.z;

        _11 = _22 = _33 = _44 = T(1);
        _12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _34 = T(0);

        return *this;
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::Translate( const Vector3< T >& t )
    {
        _41 += t.x;
        _42 += t.y;
        _43 += t.z;

        return *this;
    }

    template< typename T >
    Matrix4< T > Matrix4< T >::GetTranslated( const Vector3< T >& t )
    {
        Matrix4< T > r( *this );
        return r.Translate( t );
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::BuildScaling( const Vector3< T >& s )
    {
        _11 = s.x;
        _22 = s.y;
        _33 = s.z;

        _12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _34 = _41 = _42 = _43 = T(0);
        _44 = T(1);

        return *this;
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::Scale( const Vector3< T >& s )
    {
        _11 *= s.x;
        _21 *= s.x;
        _31 *= s.x;
        _41 *= s.x;

        _12 *= s.y;
        _22 *= s.y;
        _32 *= s.y;
        _42 *= s.y;

        _13 *= s.z;
        _23 *= s.z;
        _33 *= s.z;
        _43 *= s.z;

        return *this;
    }

    template< typename T >
    Matrix4< T > Matrix4< T >::GetScaled( const Vector3< T >& s ) const
    {
        Matrix4< T > r( *this );
        return r.Scale( s );
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::Transpose()
    {
        std::swap( _12, _21 );
        std::swap( _13, _31 );
        std::swap( _14, _41 );
        std::swap( _23, _32 );
        std::swap( _24, _42 );
        std::swap( _34, _43 );

        return *this;
    }

    template< typename T >
    Matrix4< T > Matrix4< T >::GetTransposed() const
    {
        Matrix4< T > r;
        r._11 = _11;
        r._22 = _22;
        r._33 = _33;
        r._44 = _44;

        r._12 = _21;
        r._13 = _31;
        r._14 = _41;

        r._21 = _12;
        r._23 = _32;
        r._24 = _42;

        r._31 = _13;
        r._32 = _23;
        r._34 = _43;

        r._41 = _14;
        r._42 = _24;
        r._43 = _34;

        return r;
    }

    template< typename T >
    Matrix4< T >& Matrix4< T >::operator*=( const Matrix4< T >& o )
    {
        return (*this) = o * (*this);
    }
}

template< typename T >
kT::Matrix4< T > operator*( const kT::Matrix4< T >& A, const kT::Matrix4< T >& B )
{
    kT::Matrix4< T > r;

    r._11 = B._11*A._11 + B._12*A._21 + B._13*A._31 + B._14*A._41;
    r._12 = B._11*A._12 + B._12*A._22 + B._13*A._32 + B._14*A._42;
    r._13 = B._11*A._13 + B._12*A._23 + B._13*A._33 + B._14*A._43;
    r._14 = B._11*A._14 + B._12*A._24 + B._13*A._34 + B._14*A._44;

    r._21 = B._21*A._11 + B._22*A._21 + B._23*A._31 + B._24*A._41;
    r._22 = B._21*A._12 + B._22*A._22 + B._23*A._32 + B._24*A._42;
    r._23 = B._21*A._13 + B._22*A._23 + B._23*A._33 + B._24*A._43;
    r._24 = B._21*A._14 + B._22*A._24 + B._23*A._34 + B._24*A._44;

    r._31 = B._31*A._11 + B._32*A._21 + B._33*A._31 + B._34*A._41;
    r._32 = B._31*A._12 + B._32*A._22 + B._33*A._32 + B._34*A._42;
    r._33 = B._31*A._13 + B._32*A._23 + B._33*A._33 + B._34*A._43;
    r._34 = B._31*A._14 + B._32*A._24 + B._33*A._34 + B._34*A._44;

    r._41 = B._41*A._11 + B._42*A._21 + B._43*A._31 + B._44*A._41;
    r._42 = B._41*A._12 + B._42*A._22 + B._43*A._32 + B._44*A._42;
    r._43 = B._41*A._13 + B._42*A._23 + B._43*A._33 + B._44*A._43;
    r._44 = B._41*A._14 + B._42*A._24 + B._43*A._34 + B._44*A._44;

    return r;
}

template< typename T >
kT::Vector3< T > operator*( const kT::Matrix4< T >& M, const kT::Vector3< T >& v )
{
    kT::Vector3< T > r;
    r.x = v.x*M._11 + v.y*M._21 + v.z*M._31 + M._41;
    r.y = v.x*M._12 + v.y*M._22 + v.z*M._32 + M._42;
    r.z = v.x*M._13 + v.y*M._23 + v.z*M._33 + M._43;
    return r;
}

template< typename T >
kT::Vector4< T > operator*( const kT::Matrix4< T >& M, const kT::Vector4< T >& v )
{
    kT::Vector4< T > r;
    r.x = v.x*M._11 + v.y*M._21 + v.z*M._31 + v.w*M._41;
    r.y = v.x*M._12 + v.y*M._22 + v.z*M._32 + v.w*M._42;
    r.z = v.x*M._13 + v.y*M._23 + v.z*M._33 + v.w*M._43;
	r.w = v.x*M._14 + v.y*M._24 + v.z*M._34 + v.w*M._44;
    return r;
}
