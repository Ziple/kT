/**
 * \file Core/System.hpp
 * \author Damien Hilloulin (ziple)
 * \date 16/07/2009
 * \brief Find the targeted operating system (windows, linux, mac os etc... )
 */
#ifndef __KTSYSTEM_HPP__
#define __KTSYSTEM_HPP__

/**
 * \ingroup ktcore_module
 * @{
 */

/* OS detection */
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__)

    #define KT_OS_WIN
    
    /* we must make the distinction between the two versions as not the same thing at all */
    #if defined(WINCE) || defined(_WIN32_WCE)

        #define KT_OS_WINCE
        #define KT_OS KT_OS_WINCE

    #else

        #define KT_OS KT_OS_WIN

    #endif

#elif defined(linux) || defined(__linux)

    #define KT_OS_LINUX
    #define KT_OS KT_OS_LINUX

#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)

    #define KT_OS_MACOS
    #define KT_OS KT_OS_MACOS

#else

    #error Unsupported operating system, sorry...

#endif

#if defined(KT_OS_LINUX) || defined(KT_OS_MACOS) || !defined(KT_OS_WIN)

    # define KT_OS_UNIX

#endif

/**
 * @}
 */

#endif /* __KTSYSTEM_HPP__ */
