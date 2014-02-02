/**
 * \file Core/Semaphore.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/02/2009
 * \brief Contains the definitions of the Semaphore class.
 */
#ifndef __KTSEMAPHORE_HPP__
#define __KTSEMAPHORE_HPP__

#include "Build.hpp"
#include "Types.hpp"

#if defined(KT_OS_WIN)
# include "Win/WinSemaphore.hpp"
# define SemaphoreImpl WinSemaphore
#elif defined(KT_OS_LINUX)
# include "Unix/UnixSemaphore.hpp"
# define SemaphoreImpl UnixSemaphore
#endif

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief Basic semaphore implementation. Used for multithreading synchronisation.
     */
    class Semaphore: public SemaphoreImpl
    {
        Semaphore( Uint32 initialCount = 1 ):
         SemaphoreImpl( initialCount )
         {}
    };
}

#endif /* __KTSEMAPHORE_HPP__ */
