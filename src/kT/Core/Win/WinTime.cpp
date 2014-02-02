#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>

#if defined(KT_OS_WIN)

#include <kT/Core/Win/WinTime.hpp>

namespace kT
{
    LARGE_INTEGER getFrequency()
    {
        LARGE_INTEGER frequency;
	    QueryPerformanceFrequency(&frequency);
        return frequency;
    }

    LARGE_INTEGER Time::ourFrequency = getFrequency();

    Time KT_API Time::GetTime()
    {
        // From SFML 2.1
        // Force the following code to run on first core
        // (see http://msdn.microsoft.com/en-us/library/windows/desktop/ms644904(v=vs.85).aspx)
        HANDLE currentThread = GetCurrentThread();
        DWORD_PTR previousMask = SetThreadAffinityMask(currentThread, 1);

        LARGE_INTEGER CurrentTime;
        QueryPerformanceCounter( &CurrentTime );

        // Restore the thread affinity
        SetThreadAffinityMask(currentThread, previousMask);

        return Time( CurrentTime );
    }

    void KT_API Time::Sleep( float duration )
    {
        ::Sleep( static_cast<DWORD>( duration * 1000 ) );
    }

    Float32 KT_API Time::AsSeconds()
    {
        return static_cast<Float32>( myTicks.QuadPart ) / ourFrequency.QuadPart;
    }

    Float32 KT_API Time::AsMilliSeconds()
    {
        return static_cast<Float32>( myTicks.QuadPart ) / (static_cast<Float32>(ourFrequency.QuadPart)/1000.f);
    }
}

#endif
