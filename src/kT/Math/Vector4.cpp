#define KT_TEMPLATE_IMPL
#include <kT/Math/Vector4.hpp>

namespace kT
{
#if defined(KT_EXTERN_TEMPLATES_SUPPORT)
    template KT_TEMPLATE_API Vector4ui8;
    template KT_TEMPLATE_API Vector4ui16;
    template KT_TEMPLATE_API Vector4ui32;
    template KT_TEMPLATE_API Vector4i8;
    template KT_TEMPLATE_API Vector4i16;
    template KT_TEMPLATE_API Vector4i32;
    template KT_TEMPLATE_API Vector4f32;
    template KT_TEMPLATE_API Vector4sc;

    
    template Vector4ui8 KT_TEMPLATE_API Abs( const Vector4ui8& v );
    template Vector4ui8 KT_TEMPLATE_API Min( const Vector4ui8& v, const Vector4ui8& w );
    template Vector4ui8 KT_TEMPLATE_API Max( const Vector4ui8& v, const Vector4ui8& w );

    template Vector4ui16 KT_TEMPLATE_API Abs( const Vector4ui16& v );
    template Vector4ui16 KT_TEMPLATE_API Min( const Vector4ui16& v, const Vector4ui16& w );
    template Vector4ui16 KT_TEMPLATE_API Max( const Vector4ui16& v, const Vector4ui16& w );

    template Vector4ui32 KT_TEMPLATE_API Abs( const Vector4ui32& v );
    template Vector4ui32 KT_TEMPLATE_API Min( const Vector4ui32& v, const Vector4ui32& w );
    template Vector4ui32 KT_TEMPLATE_API Max( const Vector4ui32& v, const Vector4ui32& w );

    template Vector4i8 KT_TEMPLATE_API Abs( const Vector4i8& v );
    template Vector4i8 KT_TEMPLATE_API Min( const Vector4i8& v, const Vector4i8& w );
    template Vector4i8 KT_TEMPLATE_API Max( const Vector4i8& v, const Vector4i8& w );

    template Vector4i16 KT_TEMPLATE_API Abs( const Vector4i16& v );
    template Vector4i16 KT_TEMPLATE_API Min( const Vector4i16& v, const Vector4i16& w );
    template Vector4i16 KT_TEMPLATE_API Max( const Vector4i16& v, const Vector4i16& w );

    template Vector4i32 KT_TEMPLATE_API Abs( const Vector4i32& v );
    template Vector4i32 KT_TEMPLATE_API Min( const Vector4i32& v, const Vector4i32& w );
    template Vector4i32 KT_TEMPLATE_API Max( const Vector4i32& v, const Vector4i32& w );

    template Vector4f32 KT_TEMPLATE_API Abs( const Vector4f32& v );
    template Vector4f32 KT_TEMPLATE_API Min( const Vector4f32& v, const Vector4f32& w );
    template Vector4f32 KT_TEMPLATE_API Max( const Vector4f32& v, const Vector4f32& w );

    template Vector4sc KT_TEMPLATE_API Abs( const Vector4sc& v );
    template Vector4sc KT_TEMPLATE_API Min( const Vector4sc& v, const Vector4sc& w );
    template Vector4sc KT_TEMPLATE_API Max( const Vector4sc& v, const Vector4sc& w );
#endif
}