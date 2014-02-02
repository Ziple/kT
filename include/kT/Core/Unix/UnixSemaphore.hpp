#ifndef __KTUNIXSEMAPHORE_HPP__
#define __KTUNIXSEMAPHORE_HPP__

#include "../Build.hpp"
#include "../NonCopyable.hpp"
#include "../Types.hpp"

#include <semaphore.h>

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief Implementation of semaphores under unix.
     */
    class KT_API UnixSemaphore: public NonCopyable
    {
        public:

            /**
             * \brief Constructor.
             * \param initialCount count with wich initialize the internal counter.
             */
            UnixSemaphore( Uint32 initialCount );

            /**
             * \brief Default destructor.
             */
            ~UnixSemaphore();

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

            sem_t mySemaphoreID;///< Handle to the semaphore.
    };
}

#endif /* __KTUNIXSEMAPHORE_HPP__ */
