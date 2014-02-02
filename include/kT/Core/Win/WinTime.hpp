/**
 * \file Core/Win/WinTime.hpp
 * \author Damien Hilloulin (ziple)
 * \date 13/07/2013
 * \brief Contains the definition of some utility fonctions about time.
 */
#ifndef __KTWINTIME_HPP__
#define __KTWINTIME_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>

#include <windows.h>

/**
 * \ingroup ktcore_module
 * @{
 */

namespace kT
{
    class KT_API Time
    {
        public:

            Time(){}

            /**
             * \brief Returns time elapsed since app's beginning in seconds.
             */
            static Time GetTime();

            /**
             * \brief Sleeps during the specified time (duration is in seconds).
             */
            static void Sleep( float sec );

            /**
             * \brief Returns a - b
             */
            static inline Time Diff( const Time& a, const Time& b )
            {
                LARGE_INTEGER ret;
                ret.QuadPart = a.myTicks.QuadPart - b.myTicks.QuadPart;
                return Time( ret );
            }

            /**
             * \brief Returns a float which is the time in seconds.
             */
            Float32 AsSeconds();

            /**
             * \brief Returns a float which is the time in milliseconds.
             */
            Float32 AsMilliSeconds();

        protected:

            Time(
                LARGE_INTEGER ticks ):
             myTicks( ticks )
            {}

        private:

            static LARGE_INTEGER ourFrequency;
            LARGE_INTEGER myTicks;
    };
}

/**
 * @}
 */

#endif /* __KTWINTIME_HPP__ */