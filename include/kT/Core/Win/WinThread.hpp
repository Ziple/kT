#ifndef __KTWINTHREAD_HPP__
#define __KTWINTHREAD_HPP__

#include "../Build.hpp"
#include "../NonCopyable.hpp"
#include "../Types.hpp"

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief Implementation of threads under unix.
     */
    class KT_API WinThread: public NonCopyable
    {
        public:

            typedef void* (*ThreadWorker) (void*);

            /**
             * \brief Constructor.
             * \param worker Function associated to the thread.
             * \param arg Argument to supply to the function.
             */
            WinThread( ThreadWorker worker, void* arg = 0);

            /**
             * \brief Default destructor.
             */
            virtual ~WinThread();

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
            static unsigned int __stdcall Exec(void* threadPtr);

            virtual void* Run();

        private:

            Handle myThreadID;
            ThreadWorker myWorker;
            Pointer myArg;
            Pointer myReturn;
            volatile bool myIsRunning;
    };
}

#endif /* __KTWINTHREAD_HPP__ */
