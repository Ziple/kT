#include <kT/Core/Build.hpp>

#if defined(KT_OS_WIN)

# include <kT/Core/Win/WinMutex.hpp>

# include <windows.h>

namespace kT
{
    KT_API WinMutex::WinMutex():
     myMutexID( 0 )
    {
        myMutexID = CreateMutex(NULL, FALSE, NULL);

        if ( myMutexID == 0 ) throw;
    }

    KT_API WinMutex::~WinMutex()
    {
        CloseHandle(myMutexID);
    }

    bool KT_API WinMutex::TryLock()
    {
        return WaitForSingleObject(myMutexID, 0) == WAIT_OBJECT_0 ? 1 : 0;
    }

    void KT_API WinMutex::Lock()
    {
        WaitForSingleObject(myMutexID, INFINITE);
    }

    void KT_API WinMutex::Unlock()
    {
        ReleaseMutex(myMutexID);
    }
}
#endif
