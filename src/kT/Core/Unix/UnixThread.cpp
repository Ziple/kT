#include <kT/Core/Build.hpp>

#if defined(KT_OS_UNIX)

# include <kT/Core/Unix/UnixThread.hpp>

namespace kT
{
    KT_API UnixThread::UnixThread( ThreadWorker worker, void* arg):
     myThreadID(),
     myWorker( worker ),
     myArg( arg ),
     myReturn( 0 ),
     myIsRunning( false )
    {
    }

    KT_API UnixThread::~UnixThread()
    {
        if( myIsRunning )
            Wait();
    }

    bool KT_API UnixThread::Start()
    {
        return pthread_create(&myThreadID, NULL, &UnixThread::Exec, this) == 0;
    }

    void KT_API UnixThread::Wait()
    {
        pthread_join(myThreadID, NULL);
        myIsRunning = false;
    }

    void KT_API UnixThread::Terminate()
    {
        pthread_cancel(myThreadID);
        myIsRunning = false;
    }

    bool KT_API UnixThread::IsRunning() const
    {
        return myIsRunning;
    }

    const Pointer KT_API UnixThread::GetReturn() const
    {
        return myReturn;
    }

    void* UnixThread::Exec(void *threadPtr)
    {
        UnixThread* tmpPtr = reinterpret_cast<UnixThread*>(threadPtr);
        tmpPtr->myIsRunning = true;
        tmpPtr->myReturn = tmpPtr->Run();
        tmpPtr->myIsRunning = false;
        return 0;
    }

    KT_API void* UnixThread::Run()
    {
        return myWorker ? myWorker(myArg) : 0;
    }
}
#endif
