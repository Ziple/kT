#include <kT/Window/WindowManager.hpp>

#if defined(KT_WM_X11)

# include <kT/Graphics/OGL3Device/X11/X11OGL3Context.hpp>
# include <kT/Graphics/OGL3Device/OGL.hpp>
# include <kT/Graphics/OGL3Device/OGL3Check.hpp>
# include <kT/Window/X11/X11Package.hpp>
# include <kT/Window/Window.hpp>
# include <kT/Core/Exceptions.hpp>

namespace kT
{
    KT_API X11OGL3Context::X11OGL3Context( Window* window,
                                                    X11OGL3Context* sharedWith,
                                                    unsigned redBits,
                                                    unsigned greenBits,
                                                    unsigned blueBits,
                                                    unsigned alphaBits,
                                                    unsigned depth,
                                                    unsigned stencil )
    {
        myWindow = window ? window : new Window;

        const int attribList[] = { GLX_RENDER_TYPE, GLX_RGBA,
                                   GLX_DOUBLEBUFFER, True,
                                   GLX_RED_SIZE, redBits,
                                   GLX_GREEN_SIZE, greenBits,
                                   GLX_BLUE_SIZE, blueBits,
                                   GLX_DEPTH_SIZE, depth,
                                   GLX_STENCIL_SIZE, stencil,
                                   None };

        GLXFBConfig* conf = 0;
        int elem = 0;
        conf = glXChooseFBConfig( X11Package::GetDisplay(), DefaultScreen( X11Package::GetDisplay() ), attribList, &elem );

        if( !conf )
            kTLaunchException( Exception, "Can't find a valid ogl context config" );

        myOGLContext = 0;

        myOGLContext = glXCreateNewContext( X11Package::GetDisplay(), *conf, GLX_RGBA_TYPE, sharedWith ? sharedWith->GetHandle() : 0, True );

        if( !conf )
            kTLaunchException( Exception, "Can't create the ogl context" );
    }

    KT_API X11OGL3Context::~X11OGL3Context()
    {
        glXMakeCurrent( X11Package::GetDisplay(), myWindow->GetWindowHandle(), 0 );
        glXDestroyContext( X11Package::GetDisplay(), myOGLContext );
    }

    FunctionPointer KT_API X11OGL3Context::GetProcAddress( const char* procName )
    {
        return glXGetProcAddress( reinterpret_cast<const unsigned char*>(procName) );
    }

    void KT_API X11OGL3Context::LimitFramerate( bool limit )
    {
        kTOGL3Check( glXSwapIntervalSGI( limit ? 1 : 0) );
    }

    bool KT_API X11OGL3Context::IsCurrent() const
    {
        return glXGetCurrentContext() == myOGLContext ? true : false;
    }

    void KT_API X11OGL3Context::MakeCurrent()
    {
        glXMakeCurrent( X11Package::GetDisplay(), myWindow->GetWindowHandle(), myOGLContext );
    }

    void KT_API X11OGL3Context::SwapBuffers()
    {
        glXSwapBuffers( X11Package::GetDisplay(), myWindow->GetWindowHandle() );
    }
}
#endif
