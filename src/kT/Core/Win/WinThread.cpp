#include <kT/Core/Build.hpp>

#if defined(KT_OS_WIN)

# include <kT/Core/Win/WinThread.hpp>

# include <windows.h>
# include <process.h>

namespace kT
{
    KT_API WinThread::WinThread( ThreadWorker worker, void* arg):
     myThreadID( 0 ),
     myWorker( worker ),
     myArg( arg ),
     myReturn( 0 ),
     myIsRunning( false )
    {
    }

    KT_API WinThread::~WinThread()
    {
        if( myIsRunning )
            Wait();
    }

    bool KT_API WinThread::Start()
    {
        if( myThreadID == 0 )
            myThreadID = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, &WinThread::Exec, this, 0, 0));

         return myThreadID != 0 ? true : false;
    }

    void KT_API WinThread::Wait()
    {
        WaitForSingleObject(myThreadID, INFINITE);
        CloseHandle(myThreadID);
        myThreadID = 0;
        myIsRunning = false;
    }

    void KT_API WinThread::Terminate()
    {
        TerminateThread(myThreadID, 0);
        myThreadID = 0;
        myIsRunning = false;
    }

    bool KT_API WinThread::IsRunning() const
    {
        return myIsRunning;
    }

    const Pointer KT_API WinThread::GetReturn() const
    {
        return myReturn;
    }

    unsigned int __stdcall WinThread::Exec(void *threadPtr)
    {
        WinThread* tmpPtr = static_cast<WinThread*>(threadPtr);
        tmpPtr->myIsRunning = true;
        tmpPtr->myReturn = tmpPtr->Run();
        tmpPtr->myIsRunning = false;
        //I'm not a brute
        _endthreadex(0);
        return 0;
    }

    KT_API void* WinThread::Run()
    {
        return myWorker ? myWorker(myArg) : 0;
    }
}

#endif
