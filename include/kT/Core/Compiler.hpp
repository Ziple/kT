/**
 * \file Core/Compiler.hpp
 * \author Damien Hilloulin (ziple)
 * \date 16/07/2009
 * \brief Determines the compiler.
 */
#ifndef __KTCOMPILER_HPP__
#define __KTCOMPILER_HPP__

/**
 * \ingroup ktcore_module
 * @{
 */

#if defined(__INTEL_COMPILER)

    # define KT_COMPILER_INTEL///< Defined if Intel Compiler is used.

    # define KT_COMPILER KT_COMPILER_INTEL

#elif defined(_MSC_VER)

    # define KT_COMPILER_VC///< Defined if Visual C++ Compiler is used.

    # define KT_COMPILER KT_COMPILER_VC

#elif defined(__GNUC__)

    # define KT_COMPILER_GCC///< Defined if GNU C++ Compiler is used.

    # define KT_COMPILER KT_COMPILER_GCC

#else

    # error Unsupported compiler, sorry...

#endif

/**
 * @}
 */

#endif /* __KTCOMPILER_HPP__ */
