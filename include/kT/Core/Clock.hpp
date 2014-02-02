/**
 * \file Core/Clock.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/02/2009
 * \brief Contains the definition of the kT::Clock class, used for time-tracing.
 */
#ifndef __KTCLOCK_HPP__
#define __KTCLOCK_HPP__

#include "Build.hpp"
#include "Types.hpp"
#include "Time.hpp"

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief An utility class to manipulate time.
     *
     * Thanks to an object of this class you can get the elapsed time since the last
     * call to Clock::Reset(), and even stop the time ( Clock::Stop() ) and
     * then resume the mesure ( Clock::Resume() ).
     */
    class KT_API Clock
    {
        public:

            Clock();

            /**
             * \brief Restarts the timer.
             */
            void Reset();

            /**
             * \brief Stops the timer.
             */
            void Stop();

            /**
             * \brief Resumes the timer.
             */
            void Resume();

            /**
             * \brief Gets the elapsed time since last reset in seconds.
             */
            Time GetTimeElapsed() const;

            /**
             * \brief Gets the elapsed time since last reset in seconds, then performs a reset.
             */
            Time GetTimeElapsedReset();

        private:

            Time myRefTime; /// Time Reference.
    };
}

#endif /* __KTCLOCK_HPP__ */
