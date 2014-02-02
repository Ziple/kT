#include <kT/Core/Build.hpp>

#if defined(KT_OS_UNIX)

#include <kT/Core/Types.hpp>
#include <kT/Core/Time.hpp>

# include <unistd.h>
# include <sys/time.h>

namespace kT
{
    Time KT_API Time::GetTime()
    {
        timeval curtime = {0, 0};
        gettimeofday(&curtime, NULL);

        return Time( 1000000 * curtime.tv_sec + curtime.tv_usec );
    }

    void KT_API Time::Sleep( float duration )
    {
        usleep( duration * 1000000 );
    }

    Float32 KT_API Time::AsSeconds()
    {
        return static_cast<Float32>( myTicks ) / 1000000.f;
    }

    Float32 KT_API Time::AsMilliSeconds()
    {
        return static_cast<Float32>( myTicks ) / 1000.f;
    }
}

#endif
