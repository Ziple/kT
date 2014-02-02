#include <kT/Core/Build.hpp>

#if defined(KT_OS_WIN)

# include <kT/Core/Win/WinSemaphore.hpp>

# include <windows.h>

namespace kT
{
    KT_API WinSemaphore::WinSemaphore( Uint32 initialCount ):
     mySemaphoreID( 0 )
    {
        mySemaphoreID = CreateSemaphore( 0, initialCount, 32768, 0);

        if( mySemaphoreID == 0 ) throw;
    }

    KT_API WinSemaphore::~WinSemaphore()
    {
        CloseHandle( mySemaphoreID );
    }

    bool KT_API WinSemaphore::TryWait()
    {
        return WaitForSingleObject( mySemaphoreID, 0 ) == WAIT_OBJECT_0 ? true : false;
    }

    void KT_API WinSemaphore::Wait()
    {
        WaitForSingleObject( mySemaphoreID, INFINITE );
    }

    void KT_API WinSemaphore::Post()
    {
        ReleaseSemaphore( mySemaphoreID, 1, 0 );
    }
}
#endif
