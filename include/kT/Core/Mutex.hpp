/**
 * \file Core/Mutex.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/02/2009
 * \brief Contains the definition of Mutex, letting use muteces in an system-independent way.
 */
#ifndef __KTMUTEX_HPP__
#define __KTMUTEX_HPP__

#include "Build.hpp"

#if defined(KT_OS_WIN)
# include "Win/WinMutex.hpp"
# define MutexImpl WinMutex
#elif defined(KT_OS_UNIX)
# include "Unix/UnixMutex.hpp"
# define MutexImpl UnixMutex
#endif

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief Basic mutex class for multithreading synchronisation.
     */
    class Mutex: public MutexImpl
    {
    };
}

#endif /* __KTMUTEX_HPP__ */
