#include <kT/Core/Build.hpp>

#if defined(KT_OS_UNIX)

# include <kT/Core/Unix/UnixMutex.hpp>


namespace kT
{
    KT_API UnixMutex::UnixMutex():
     myMutexID()
    {
        pthread_mutex_init(&myMutexID, NULL);
    }

    KT_API UnixMutex::~UnixMutex()
    {
        pthread_mutex_destroy(&myMutexID);
    }

    bool KT_API UnixMutex::TryLock()
    {
        return pthread_mutex_trylock(&myMutexID) == 0;
    }

    void KT_API UnixMutex::Lock()
    {
        pthread_mutex_lock(&myMutexID);
    }

    void KT_API UnixMutex::Unlock()
    {
        pthread_mutex_unlock(&myMutexID);
    }
}
#endif
