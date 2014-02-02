#include <kT/Window/WindowManager.hpp>

#if defined(KT_WM_X11)
# include <kT/Window/X11/X11Mouse.hpp>
# include <kT/Window/X11/X11Package.hpp>
# include <kT/Window/Window.hpp>

# include <X11/Xlib.h>
# include <X11/XKBlib.h>

namespace kT
{
    ////////////////////////////////////////////////////////////
    bool KT_API X11Mouse::IsButtonPressed(Mouse::Button button)
    {
        // Get the connection with the X server
        Display* display = X11Package::ourDisplay;

        // we don't care about these but they are required
        ::Window root, child;
        int wx, wy;
        int gx, gy;

        unsigned int buttons = 0;
        XQueryPointer(display, DefaultRootWindow(display), &root, &child, &gx, &gy, &wx, &wy, &buttons);

        switch (button)
        {
            case Mouse::Left:     return buttons & Button1Mask;
            case Mouse::Right:    return buttons & Button3Mask;
            case Mouse::Middle:   return buttons & Button2Mask;
            case Mouse::XButton1: return false; // not supported by X
            case Mouse::XButton2: return false; // not supported by X
            default:              return false;
        }

        return false;
    }


    ////////////////////////////////////////////////////////////
    Vector2i32 KT_API X11Mouse::GetPosition()
    {
        // Get the connection with the X server
        Display* display = X11Package::ourDisplay;

        // we don't care about these but they are required
        ::Window root, child;
        int x, y;
        unsigned int buttons;

        int gx = 0;
        int gy = 0;
        XQueryPointer(display, DefaultRootWindow(display), &root, &child, &gx, &gy, &x, &y, &buttons);

        return Vector2i32(gx, gy);
    }


    ////////////////////////////////////////////////////////////
    Vector2i32 KT_API X11Mouse::GetPosition(const Window& relativeTo)
    {
        WindowHandle handle = relativeTo.GetWindowHandle();
        if (handle)
        {
            // Get the connection with the X server
            Display* display = X11Package::ourDisplay;

            // we don't care about these but they are required
            ::Window root, child;
            int gx, gy;
            unsigned int buttons;

            int x = 0;
            int y = 0;
            XQueryPointer(display, handle, &root, &child, &gx, &gy, &x, &y, &buttons);

            return Vector2i32(x, y);
        }
        else
        {
            return Vector2i32();
        }
    }


    ////////////////////////////////////////////////////////////
    void KT_API X11Mouse::SetPosition(const Vector2i32& position)
    {
        // Get the connection with the X server
        Display* display = X11Package::ourDisplay;

        XWarpPointer(display, None, DefaultRootWindow(display), 0, 0, 0, 0, position.x, position.y);
        XFlush(display);
    }


    ////////////////////////////////////////////////////////////
    void KT_API X11Mouse::SetPosition(const Vector2i32& position, const Window& relativeTo)
    {
        // Get the connection with the X server
        Display* display = X11Package::ourDisplay;

        WindowHandle handle = relativeTo.GetWindowHandle();
        if (handle)
        {
            XWarpPointer(display, None, handle, 0, 0, 0, 0, position.x, position.y);
            XFlush(display);
        }
    }
}
#endif
