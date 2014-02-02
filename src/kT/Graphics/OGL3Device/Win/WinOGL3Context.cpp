#include <kT/Window/WindowManager.hpp>

#if defined(KT_WM_WIN)

# include <kT/Graphics/OGL3Device/Win/WinOGL3Context.hpp>
# include <kT/Graphics/OGL3Device/OGL.hpp>
# include <kT/Graphics/OGL3Device/OGL3Check.hpp>
# include <kT/Core/Exceptions.hpp>
# include <kT/Window/Window.hpp>

# include <windows.h>

namespace kT
{
    KT_API WinOGL3Context::WinOGL3Context( Window* window,
                                                    WinOGL3Context* sharedWith,
                                                    unsigned redBits,
                                                    unsigned greenBits,
                                                    unsigned blueBits,
                                                    unsigned alphaBits,
                                                    unsigned depth,
                                                    unsigned stencil )
    {
        myWindow = window ? window : new Window();

        myDC = GetDC( myWindow->GetWindowHandle() );

        if( !myDC )
            kTLaunchException( Exception, "Can't retrieve the DC to create a OGL context" );

        PIXELFORMATDESCRIPTOR pfd = {0};

        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.nVersion = 1;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.iLayerType = PFD_MAIN_PLANE;
        pfd.cColorBits = redBits + greenBits + blueBits + alphaBits;
        pfd.cRedBits = redBits;
        pfd.cGreenBits = greenBits;
        pfd.cBlueBits = blueBits;
        pfd.cAlphaBits = alphaBits;
        pfd.cDepthBits = depth;
        pfd.cStencilBits = stencil;

        int pixelFormat = ChoosePixelFormat( myDC, &pfd );

        if( !pixelFormat )
            kTLaunchException( Exception, "Can't find a matching pixel format" );

        if( SetPixelFormat( myDC, pixelFormat, &pfd ) == FALSE )
            kTLaunchException( Exception, "Can't set the pixel format" );

        myOGLContext = wglCreateContext( myDC );

        if( !myOGLContext )
            kTLaunchException( Exception, "Can't create the context" );

        if( sharedWith )
        {
            if( wglShareLists( sharedWith->GetHandle(), myOGLContext ) == FALSE )
                kTLaunchException( Exception, "Can't share the context" );
        }
    }

    KT_API WinOGL3Context::~WinOGL3Context()
    {
        wglMakeCurrent( myDC, 0 );
        wglDeleteContext( myOGLContext );
    }

    KT_API FunctionPointer WinOGL3Context::GetProcAddress( const char* name )
    {
        return reinterpret_cast<FunctionPointer>( wglGetProcAddress( name ) );
    }

    void KT_API WinOGL3Context::LimitFramerate( bool limit )
    {
        ktOGL3Check( wglSwapIntervalEXT( limit ? 1 : 0 ) );
    }

    bool KT_API WinOGL3Context::IsCurrent() const
    {
        return wglGetCurrentContext() == myOGLContext ? true : false;
    }

    void KT_API WinOGL3Context::MakeCurrent()
    {
        wglMakeCurrent( myDC, myOGLContext );
    }

    void KT_API WinOGL3Context::SwapBuffers()
    {
        ::SwapBuffers( myDC );
    }
}
#endif
