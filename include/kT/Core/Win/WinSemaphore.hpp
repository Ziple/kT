#ifndef __KTWINSEMAPHORE_HPP__
#define __KTWINSEMAPHORE_HPP__

#include "../Build.hpp"
#include "../NonCopyable.hpp"
#include "../Types.hpp"

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief Implementation of semaphores under unix.
     */
    class KT_API WinSemaphore: public NonCopyable
    {
        public:

            /**
             * \brief Constructor.
             * \param initialCount count with wich initialize the internal counter.
             */
            WinSemaphore( Uint32 initialCount );

            /**
             * \brief Default destructor.
             */
            ~WinSemaphore();

            /**
             * \brief Tries to wait for the signal.
             * \return true if the signal has been posted.
             *
             * This call is not blocking.
             */
            bool TryWait();

            /**
             * \brief Waits until the signal is posted.
             */
            void Wait();

            /**
             * \brief Posts the signal.
             */
            void Post();

        private:

            Handle mySemaphoreID;///< Handle to the semaphore.
    };
}

#endif /* __KTWINSEMAPHORE_HPP__ */
