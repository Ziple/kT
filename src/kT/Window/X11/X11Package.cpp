#include <kT/Window/WindowManager.hpp>

#if defined(KT_WM_X11)

# include <kT/Window/X11/X11Package.hpp>

# include <X11/Xlib.h>
# include <X11/XKBlib.h>

# include <cstdlib>

namespace kT
{
    static void _cleanX11Package()
    {
        if ( X11Package::ourInputMethod )
        {
            XCloseIM( X11Package::ourInputMethod );
            X11Package::ourInputMethod = 0;
        }

        X11Package::ourRootWindow = 0;
        X11Package::ourScreen = 0;
        XCloseDisplay(  X11Package::ourDisplay );
        X11Package::ourDisplay = 0;
    }

    static Display* _initX11Package()
    {
        Display* display = XOpenDisplay( 0 );

        if ( display )
        {
            X11Package::ourScreen = DefaultScreen( display );
            X11Package::ourRootWindow = DefaultRootWindow( display );

            Bool Supported;
            XkbSetDetectableAutoRepeat( display, True, &Supported );
            XFlush( display );

            X11Package::ourInputMethod = XOpenIM( display, 0, 0, 0 );
        }
        else
            throw;

        atexit( _cleanX11Package );
        return display;
    }

    Display*        X11Package::ourDisplay     = _initX11Package();
    int             X11Package::ourScreen      = 0;
    unsigned long X11Package::ourRootWindow  = 0;
    XIM             X11Package::ourInputMethod = 0;

    Display* X11Package::GetDisplay()
    {
        return ourDisplay;
    }
}

#endif
