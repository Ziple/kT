/**
 * \file Core/Thread.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/02/2009
 * \brief Contains the definition of the SKLThread class.
 */
#ifndef __KTTHREAD_HPP__
#define __KTTHREAD_HPP__

#include "Build.hpp"

#if defined(KT_OS_WIN)
# include "Win/WinThread.hpp"
# define ThreadImpl WinThread
#elif defined(KT_OS_UNIX)
# include "Unix/UnixThread.hpp"
# define ThreadImpl UnixThread
#endif

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief Provides an easy way to manipulate a thread.
     *
     * There are two ways to use Thread :
     *
     *   - Inherit from it and override the Run() virtual function
     *   - Construct a Thread instance and pass it a function pointer to call
     */
    class Thread: public ThreadImpl
    {
        public:

            Thread( ThreadWorker worker, void* arg = 0 ): ThreadImpl(worker, arg) {}
    };
}

#endif /* __KTTHREAD_HPP__ */
