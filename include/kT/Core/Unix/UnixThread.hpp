#ifndef __KTUNIXTHREAD_HPP__
#define __KTUNIXTHREAD_HPP__

#include "../Build.hpp"
#include "../NonCopyable.hpp"
#include "../Types.hpp"

#include <pthread.h>

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief Implementation of threads under unix.
     */
    class KT_API UnixThread: public NonCopyable
    {
        public:

            typedef void* (*ThreadWorker) (void*);

            /**
             * \brief Constructor.
             * \param worker Function associated to the thread.
             * \param arg Argument to supply to the function.
             */
            UnixThread( ThreadWorker worker, void* arg = 0);

            /**
             * \brief Default destructor.
             */
            virtual ~UnixThread();

            /**
             * \brief Launches the thread.
             */
            bool Start();

            /**
             * \brief Waits until the thread has terminated.
             */
            void Wait();

            /**
             * \brief Terminates the thread.
             */
            void Terminate();

            /**
             * \brief Tells if the thread is running.
             */
            bool IsRunning() const;

            /**
             * \brief Returns the value returned by the thread in its end.
             */
            const Pointer GetReturn() const;

        protected:

            /**
             * \brief Actual function called when the thread is launched.
             *
             * Calls the Run() method of threadPtr.
             */
            static void* Exec( void* threadPtr );

            virtual void* Run();

        private:

            pthread_t myThreadID;
            volatile bool myIsRunning;
            ThreadWorker myWorker;
            Pointer myArg;
            Pointer myReturn;
    };
}

#endif /* __KTUNIXTHREAD_HPP__ */
