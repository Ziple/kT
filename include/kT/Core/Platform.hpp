/**
 * \file Core/Platform.hpp
 * \author Damien Hilloulin (ziple)
 * \date 16/07/2009
 * \brief Find the type of the targeted platform (x86 one, x86_64, PPC, ARM...)
 */
#ifndef __KTPLATFORM_HPP__
#define __KTPLATFORM_HPP__

/**
 * \ingroup ktcore_module
 * @{
 */

/* Platform detection */
/* x86_64 processor */
#if defined(__amd64__) || defined(__x86_64) || defined(__x86_64__) || defined(_M_AMD64) || defined(_M_X64)

    # define KT_ARCH_X64
    # define KT_ARCH KT_ARCH_X64

/* x86 processor */
#elif defined(__i386__) || defined(_M_IX86) || defined(_X86_) || defined(__INTEL__) || defined(__i386)

    # define KT_ARCH_X86
    # define KT_ARCH KT_ARCH_X86

/* itanium 64 processor */
#elif defined(__IA64__) || defined(_M_IA64)

    # define KT_ARCH_IA64
    # define KT_ARCH KT_ARCH_IA64

/* power pc processor */
#elif defined(__powerpc__) || defined(_M_PPC) || defined(_ARCH_PPC)

    # define KT_ARCH_POWERPC
    # define KT_ARCH KT_ARCH_POWERPC

/* ARM processor */
#elif defined(ARM7) || defined(ARM9) || defined(__arm__)

    # define KT_ARCH_ARM
    # define KT_ARCH KT_ARCH_ARM

#else

    # error Unsupported platform, sorry...

#endif

#if defined(KT_PLATFORM_PPC)

    # define KT_BIG_ENDIAN
    # define KT_ENDIANNESS KT_BIG_ENDIAN

#else

    # define KT_LITTLE_ENDIAN
    # define KT_ENDIANNESS KT_LITTLE_ENDIAN

#endif

/**
 * @}
 */

#endif /* __KTPLATFORM_HPP__ */
