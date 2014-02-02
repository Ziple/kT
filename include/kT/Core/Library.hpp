/**
 * \file Core/Library.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/02/2009
 * \brief Contains the definition of the Library class, used to load and use dynamic libraries.
 */
#ifndef __KTLIBRARY_HPP__
#define __KTLIBRARY_HPP__

#include "Build.hpp"

#if defined(KT_OS_WIN)
# include "Win/WinLibrary.hpp"
# define LibraryImpl WinLibrary
#elif defined(KT_OS_UNIX)
# include "Unix/UnixLibrary.hpp"
# define LibraryImpl UnixLibrary
#endif

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief Manages dynamic libraries.
     */
    class Library: public LibraryImpl
    {
    };
}

#endif /* __KTLIBRARY_HPP__ */
