/**
 * \file Core/Unix/UnixTime.hpp
 * \author Damien Hilloulin (ziple)
 * \date 13/07/2013
 * \brief Contains the definition of some utility fonctions about time.
 */
#ifndef __KTUNIXTIME_HPP__
#define __KTUNIXTIME_HPP__

#include "../Types.hpp"

namespace kT
{
    /**
     * \ingroup ktcore_module
     * @{
     */

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
                return Time( a.myTicks - b.myTicks );
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
                Uint64 ticks ):
             myTicks( ticks )
            {}

        private:

            Uint64 myTicks; ///< Microseconds
    };
}

#endif /* __KTUNIXTIME_HPP__ */