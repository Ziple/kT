/**
 * \file Core/Build.hpp
 * \author Damien Hilloulin (ziple)
 * \date 16/07/2009
 * \brief File to tune compilation. Must be included by allmost all others headers.
 */
#ifndef __KTBUILD_HPP__
#define __KTBUILD_HPP__

#include "System.hpp"
#include "Compiler.hpp"

/**
 * \ingroup ktcore_module
 * @{
 */

/* Portable macros for import/export */
#if defined(KT_OS_WIN) && defined(KT_DYNAMIC)

    #ifndef KT_BUILDING_LIBRARY

        #define KT_API __declspec(dllimport)

    #else

        #define KT_API __declspec(dllexport)

        // For Visual C++ compilers, we also need to turn off this annoying C4251 warning.
        // You can read lots ot different things about it, but the point is the code will
        // just work fine, and so the simplest way to get rid of this warning is to disable it
        #ifdef _MSC_VER

            #pragma warning(disable : 4251)

        #endif

    #endif

#else

    #define KT_API

#endif


/* debug mode compilation */
#if !defined(NDEBUG) || defined(_DEBUG)

    # define KT_DEBUG

#endif

#if defined(KT_EXTERN_TEMPLATES_SUPPORT)

    #define KT_TEMPLATE_API KT_API

#else

    #define KT_TEMPLATE_API

#endif

/**
 * @}
 */

#endif /* __KTBUILD_HPP__ */
