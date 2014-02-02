#include <kT/Core/Build.hpp>

#if defined(KT_OS_UNIX)

#include <kT/Core/Unix/UnixLibrary.hpp>

# include <dlfcn.h>
# include <cstring>

namespace kT
{
    KT_API UnixLibrary::UnixLibrary():
     myLibraryModule(0),
     myIsLoaded(false)
    {
    }

    KT_API UnixLibrary::~UnixLibrary()
    {
        if( myIsLoaded )
            Unload();
    }

    bool KT_API UnixLibrary::Load(const char* filename)
    {
        char* outStr = 0;

        outStr = strcpy( outStr, filename );

        myIsLoaded = ( myLibraryModule = dlopen( strcat( outStr, ".so" ), RTLD_LAZY) ) ? true : false;
        return myIsLoaded;
    }

    void KT_API UnixLibrary::Unload()
    {
        dlclose(myLibraryModule);
        myIsLoaded = false;
    }

    void* KT_API UnixLibrary::GetProcAddress(const char *symbol)
    {
        return dlsym(myLibraryModule, symbol);
    }

    bool KT_API UnixLibrary::IsLoaded() const
    {
        return myIsLoaded;
    }
}

#endif
