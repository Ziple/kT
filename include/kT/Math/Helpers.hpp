/**
 * \file Math/Helpers.hpp
 * \author Damien Hilloulin
 * \date 19/10/2008
 * \brief Contains some math helpers (constants, functions).
 */
#ifndef __KTMATHHELPERS_HPP__
#define __KTMATHHELPERS_HPP__

#include <kT/Core/Types.hpp>

namespace kT
{
    /*
     * \ingroup ktmath_module
     * @{
     */
    const Float32 RoundingError32 = 0.00005f;///< Rounding error for Float32.
    const Float64 RoundingError64 = 0.000005;///< Rounding error for Float64.

    const Float32 Pi32            = 3.14159265359f;///< Approximate value of pi
    const Float32 ReciprocalPi32 = 1.0f/ Pi32;///< Approximate of 1/pi
    const Float32 HalfPi32       = Pi32/2.0f; ///< pi/2

    const Float32 DegToRad32 = Pi32 / 180.0f;///< Constant to convert degrees to radians.
    const Float32 RadToDeg32   = 180.0f / Pi32;///< Constant to convert radians to degrees.

    /**
     * \brief Approximate of pi.
     */
    const Float64 Pi64          = 3.1415926535897932384626433832795028841971693993751;
    /**
     * \brief Approximate of 1/pi.
     */
    const Float64 ReciprocalPi64 = 1.0/ Pi64;

    const Float64 DegToRad64 = Pi64 / 180.0;///< Constant to convert degrees to radians.
    const Float64 RadToDeg64 = 180.0 / Pi64;///< Constant to convert radians to degrees.

    /**
     * \brief Returns the minimum of the two values.
     */
    template< typename T >
    inline const T& Min(const T& a,const T& b)
    {
        return a < b ? a : b;
    }

    /**
     * \brief Returns the minimum of the three values.
     */
    template< typename T >
    inline const T& Min(const T& a,const T& b, const T& c)
    {
        return a < b ? Min(a, c) : Min(b, c);

    }

    /**
     * \brief Returns the maximum of the two values.
     */
    template< typename T >
    inline const T& Max(const T& a,const T& b)
    {
        return a < b ? b : a;
    }

    /**
     * \brief Returns the maximum of the three values.
     */
    template< typename T >
    inline const T& Max(const T& a,const T& b, const T& c)
    {
        return a < b ? Max(b, c) : Max(a, c);

    }

    /**
     * \brief Returns the absolute value of the number.
     */
    template< typename T >
    inline T Abs(const T& a)
    {
        return a < T(0) ? -a : a;
    }

    /**
     * \brief Performs a linear interpolation of the two values according to t.
     * ret = a * (1.f-t) + (b*t);
     */
    template< typename T >
    inline T Lerp(const T& a, const T& b, Float32 t)
    {
        return T( (1.f-t) * a + (t*b));
    }

    /**
     * \brief Returns the clamped value of a in the range of [low,high].
     */
    template< typename T >
    inline T Clamp(const T& a, const T& low, const T& high)
    {
        return Min(Max(a, low),high);
    }

    /**
     * \brief Returns the reciproqual square root of x.
     */
    inline Float32 RcpqSqrt(Float32 x)
    {
        unsigned tmp = (0xBE6EB50C - *(unsigned*)&x)>>1;
        float i = *(float*)&tmp;
        return i * ( 1.5f - 0.5f * x * i * i );
    }

    /*
     * @}
     */
}

#endif /* __KTMATHHELPERS_HPP__ */
