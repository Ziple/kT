#include <kT/Core/Clock.hpp>
#include <kT/Core/Time.hpp>

namespace kT
{
    KT_API Clock::Clock()
    {
        Reset();
    }

    void KT_API Clock::Reset()
    {
        myRefTime = Time::GetTime();
    }

    void KT_API Clock::Stop()
    {
        myRefTime = GetTimeElapsed();
    }

    void KT_API Clock::Resume()
    {
        myRefTime = Time::Diff( Time::GetTime(), myRefTime );
    }

    Time KT_API Clock::GetTimeElapsed() const
    {
        return Time::Diff( Time::GetTime(), myRefTime );
    }

    Time KT_API Clock::GetTimeElapsedReset()
    {
        Time oldRefTime = myRefTime;
        myRefTime = Time::GetTime();
        return Time::Diff( myRefTime, oldRefTime );
    }
}