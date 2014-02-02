#ifndef __KTWINMUTEX_HPP__
#define __KTWINMUTEX_HPP__

#include "../Build.hpp"
#include "../Types.hpp"
#include "../NonCopyable.hpp"

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief Implementation of mutex under windows.
     * \todo Switch to Critical sections (faster)
     */
    class KT_API WinMutex: public NonCopyable
    {
        public:

            /**
             * \brief Default constructor.
             */
            WinMutex();

            /**
             * \brief Default destructor.
             */
            ~WinMutex();

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

            Handle myMutexID;///< Handle to the mutex.
    };
}
#endif /* __KTWINMUTEX_HPP__ */
