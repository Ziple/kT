#include <kT/Core/Build.hpp>

#if defined(KT_OS_UNIX)

# include <kT/Core/Unix/UnixSemaphore.hpp>

namespace kT
{
    KT_API UnixSemaphore::UnixSemaphore( Uint32 initialCount )
    {
        sem_init( &mySemaphoreID, 0, initialCount );
    }

    KT_API UnixSemaphore::~UnixSemaphore()
    {
        sem_destroy( &mySemaphoreID );
    }

    bool KT_API UnixSemaphore::TryWait()
    {
        return sem_trywait( &mySemaphoreID ) == -1 ? false : true;
    }

    void KT_API UnixSemaphore::Wait()
    {
        sem_wait( &mySemaphoreID );
    }

    void KT_API UnixSemaphore::Post()
    {
        sem_post( &mySemaphoreID );
    }
}
#endif
