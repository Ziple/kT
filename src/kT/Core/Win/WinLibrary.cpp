#include <kT/Core/Build.hpp>

#if defined(KT_OS_WIN)

#include <kT/Core/Win/WinLibrary.hpp>

namespace kT
{
    KT_API WinLibrary::WinLibrary():
     myLibraryModule(0),
     myIsLoaded(false)
    {
    }

    KT_API WinLibrary::~WinLibrary()
    {
        if( myIsLoaded )
            Unload();
    }

    KT_API bool WinLibrary::Load(const char* filename)
    {
        char* outStr = 0;

        outStr = strcpy( outStr, filename );

        myIsLoaded = ( myLibraryModule = LoadLibraryA( strcat( outStr, ".dll" ) ) ) ? true : false;
        return myIsLoaded;
    }

    KT_API void WinLibrary::Unload()
    {
        FreeLibrary(myLibraryModule);
        myLibraryModule = 0;
        myIsLoaded = false;
    }

    KT_API void* WinLibrary::GetProcAddress(const char *symbol)
    {
        return (void*)::GetProcAddress(myLibraryModule, symbol);
    }

    bool KT_API WinLibrary::IsLoaded() const
    {
        return myIsLoaded;
    }
}

#endif
