/**
 * \file Core/Types.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/02/2009
 * \brief Essential file where the types used by the engine are defined.
 */
#ifndef __KTTYPES_HPP__
#define __KTTYPES_HPP__

#include "Build.hpp"
#include <limits.h>

namespace kT
{
    #if UCHAR_MAX ==  0xFF
        typedef char                Int8;
        typedef unsigned char        Uint8;
    #else
        #error No 8 bits types on this platform!
    #endif

    #if USHRT_MAX == 0xFFFF
        typedef short                Int16;
        typedef unsigned short        Uint16;
    #elif UINT_MAX == 0xFFFF
        typedef int                    Int16;
        typedef unsigned int        Uint16;
    #elif ULONG_MAX == 0xFFFF
        typedef long                Int16;
        typedef unsigned long        Uint16;
    #else
        #error No 16 bits types on this platform!
    #endif

    #if USHRT_MAX == 0xFFFFFFFF
        typedef short                Int32;
        typedef unsigned short        Uint32;
    #elif UINT_MAX == 0xFFFFFFFF
        typedef int                    Int32;
        typedef unsigned int        Uint32;
    #elif ULONG_MAX == 0xFFFFFFFF
        typedef long                Int32;
        typedef unsigned long        Uint32;
    #else
        #error No 32 bits types on this platform!
    #endif

    #if UINT_MAX == 0xFFFFFFFFFFFFFFFF
        typedef int                 Int64;
        typedef unsigned int        Uint64;
    #elif ULONG_MAX == 0xFFFFFFFFFFFFFFFF
        typedef long                Int64;
        typedef unsigned long        Uint64;
    #elif ULLONG_MAX == 0xFFFFFFFFFFFFFFFF
        typedef long long            Int64;
        typedef unsigned long long  Uint64;
    #else
        #warning No 64 bits integers on this platform!
        #define KT_NO_64BITS_INTEGERS
    #endif

        typedef float                Float32;
        typedef double                Float64;

        typedef Float32          Scalar;//< type used as a scalar

        typedef void*               Pointer;
        typedef Pointer          Handle;

        typedef void (*FunctionPointer)();
        typedef bool (Predicate)( Pointer );
}

#endif /* __KTTYPES_HPP__ */
