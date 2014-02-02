#ifndef __KTUNIXMUTEX_HPP__
#define __KTUNIXMUTEX_HPP__

#include "../Build.hpp"
#include "../NonCopyable.hpp"

#include <pthread.h>

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief Implementation of mutex under unix.
     */
    class KT_API UnixMutex: public NonCopyable
    {
        public:

            /**
             * \brief Default constructor.
             */
            UnixMutex();

            /**
             * \brief Default destructor.
             */
            ~UnixMutex();

            /**
             * \brief Tries to lock the mutex.
             * \return true if successful, false otherwise.
             *
             * This call is not blocking.
             */
            bool TryLock();

            /**
             * \brief Waits until the lock is acquired.
             */
            void Lock();

            /**
             * \brief Unlocks the mutex.
             */
            void Unlock();

        private:

            pthread_mutex_t myMutexID;///< Handle to the mutex.
    };
}

#endif/* __KTUNIXMUTEX_HPP__ */
