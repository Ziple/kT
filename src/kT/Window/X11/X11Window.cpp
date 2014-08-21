#include <kT/Window/WindowManager.hpp>

#if defined(KT_WM_X11)

# include <kT/Window/X11/X11Window.hpp>
# include <kT/Window/X11/X11Package.hpp>

#include <kT/Core/Exceptions.hpp>

# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <X11/XKBlib.h>
# include <X11/Xutil.h>

namespace kT
{
    static const unsigned long  eventMask = FocusChangeMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask |
                               PointerMotionMask | KeyPressMask | KeyReleaseMask | StructureNotifyMask;

    KT_API Window::Window():
     WindowBase( 0 ),
     myIsExternal( false ),
     myInputContext( 0 ),
     myStyle( Window::NoDecoration )
    {
        mySize = Sizeui32( 1, 1 );
        myWindowHandle = XCreateWindow( X11Package::ourDisplay,
                                        X11Package::ourRootWindow,
                                        0, 0,
                                        mySize.Width, mySize.Height,
                                        0,
                                        DefaultDepth( X11Package::ourDisplay,
                                                      X11Package::ourScreen ),
                                        InputOutput,
                                        DefaultVisual( X11Package::ourDisplay,
                                                       X11Package::ourScreen ),
                                        0,
                                        0 );
    }

    KT_API Window::Window( const std::string& caption,
                                          const Sizeui32& size,
                                          Uint32 style ):
     WindowBase( 0 ),
     myIsExternal( false ),
     myInputContext( 0 ),
     myStyle( style )
    {
        Create( caption, size, style );
    }

    KT_API Window::Window( WindowHandle nativeHandle ):
     WindowBase( 0 ),
     myIsExternal( false ),
     myInputContext( 0 )
    {
        Create( nativeHandle );
    }

    KT_API Window::~Window()
    {
        Destroy();
    }

    void KT_API Window::Create( const std::string& caption,
                                   const Sizeui32& size,
                                   Uint32 style )
    {
        mySize = size;
        int left, top;

        // Compute position and size
        bool Fullscreen = (style & Window::Fullscreen) != 0;

        // Switch to fullscreen if necessary
        if ( !Fullscreen )
        {
            left = ( DisplayWidth( X11Package::ourDisplay, X11Package::ourScreen ) - mySize.Width )/2;
            top  = ( DisplayHeight( X11Package::ourDisplay, X11Package::ourScreen ) - mySize.Height )/2;
        }
        else
        {
            left = 0;
            top  = 0;
            mySize.Width = DisplayWidth( X11Package::ourDisplay, X11Package::ourScreen );
            mySize.Height = DisplayHeight( X11Package::ourDisplay, X11Package::ourScreen );
        }

        // Define the window attributes
        XSetWindowAttributes attributes;
        attributes.event_mask        = eventMask;
        attributes.override_redirect = Fullscreen;

        myWindowHandle = XCreateWindow( X11Package::ourDisplay,
                                        X11Package::ourRootWindow,
                                        left, top,
                                        mySize.Width, mySize.Height,
                                        0,
                                        DefaultDepth( X11Package::ourDisplay,
                                                      X11Package::ourScreen ),
                                        InputOutput,
                                        DefaultVisual( X11Package::ourDisplay,
                                                       X11Package::ourScreen ),
                                        CWEventMask | CWOverrideRedirect,
                                        &attributes );

        if ( !myWindowHandle )
            kTLaunchException( kT::Exception, "Can't create a new window!" );

        XStoreName( X11Package::ourDisplay, myWindowHandle, caption.c_str() );

        // Set the window's style (tell the windows manager to change our window's decorations and functions according to the requested style)
        if (!Fullscreen)
        {
            Atom WMHintsAtom = XInternAtom( X11Package::ourDisplay, "_MOTIF_WM_HINTS", false );
            if (WMHintsAtom)
            {
                static const unsigned long MWM_HINTS_FUNCTIONS   = 1 << 0;
                static const unsigned long MWM_HINTS_DECORATIONS = 1 << 1;

                //static const unsigned long MWM_DECOR_ALL         = 1 << 0;
                static const unsigned long MWM_DECOR_BORDER      = 1 << 1;
                static const unsigned long MWM_DECOR_RESIZEH     = 1 << 2;
                static const unsigned long MWM_DECOR_TITLE       = 1 << 3;
                static const unsigned long MWM_DECOR_MENU        = 1 << 4;
                static const unsigned long MWM_DECOR_MINIMIZE    = 1 << 5;
                static const unsigned long MWM_DECOR_MAXIMIZE    = 1 << 6;

                //static const unsigned long MWM_FUNC_ALL          = 1 << 0;
                static const unsigned long MWM_FUNC_RESIZE       = 1 << 1;
                static const unsigned long MWM_FUNC_MOVE         = 1 << 2;
                static const unsigned long MWM_FUNC_MINIMIZE     = 1 << 3;
                static const unsigned long MWM_FUNC_MAXIMIZE     = 1 << 4;
                static const unsigned long MWM_FUNC_CLOSE        = 1 << 5;

                struct WMHints
                {
                    unsigned long Flags;
                    unsigned long Functions;
                    unsigned long Decorations;
                    long          InputMode;
                    unsigned long State;
                };

                WMHints Hints;
                Hints.Flags       = MWM_HINTS_FUNCTIONS | MWM_HINTS_DECORATIONS;
                Hints.Decorations = 0;
                Hints.Functions   = 0;

                if ( style & Window::Titlebar )
                {
                    Hints.Decorations |= MWM_DECOR_BORDER | MWM_DECOR_TITLE | MWM_DECOR_MENU;
                    Hints.Functions   |= MWM_FUNC_MOVE;
                }
                if ( style & Window::Resizable )
                {
                    Hints.Decorations |= MWM_DECOR_MAXIMIZE | MWM_DECOR_MINIMIZE | MWM_DECOR_RESIZEH;
                    Hints.Functions   |= MWM_FUNC_MOVE  | MWM_FUNC_MINIMIZE | MWM_FUNC_MAXIMIZE | MWM_FUNC_RESIZE;
                }
                if ( style & Window::Closable )
                {
                    Hints.Decorations |= MWM_DECOR_BORDER;
                    Hints.Functions   |= MWM_FUNC_MOVE | MWM_FUNC_CLOSE;
                }

                const unsigned char* HintsPtr = reinterpret_cast<const unsigned char*>(&Hints);
                XChangeProperty( X11Package::ourDisplay,
                                 myWindowHandle,
                                 WMHintsAtom,
                                 WMHintsAtom,
                                 32,
                                 PropModeReplace,
                                 HintsPtr,
                                 5);
            }

            // This is a hack to force some windows managers to disable resizing
            if (!(style & Window::Resizable))
            {
                XSizeHints XSizeHints;
                XSizeHints.flags      = PMinSize | PMaxSize;
                XSizeHints.min_width  = XSizeHints.max_width  = mySize.Width;
                XSizeHints.min_height = XSizeHints.max_height = mySize.Height;
                XSetWMNormalHints( X11Package::ourDisplay, myWindowHandle, &XSizeHints);
            }
        }

        // Do some common initializations
        Initialize();

        // In fullscreen mode, we must grab keyboard and mouse inputs
        if ( Fullscreen )
        {
            XGrabPointer( X11Package::ourDisplay,
                          myWindowHandle,
                          true,
                          0,
                          GrabModeAsync,
                          GrabModeAsync,
                          myWindowHandle,
                          None,
                          CurrentTime );
            XGrabKeyboard( X11Package::ourDisplay,
                           myWindowHandle,
                           true,
                           GrabModeAsync,
                           GrabModeAsync,
                           CurrentTime);
        }
    }

    void KT_API Window::Create( WindowHandle nativeHandle )
    {
        // save the window handle
        myWindowHandle = nativeHandle;

        if ( myWindowHandle )
        {
            myIsExternal = true;
            // get the size
            XWindowAttributes windowAttributes;
            if ( XGetWindowAttributes( X11Package::ourDisplay, myWindowHandle, &windowAttributes ) == 0 )
                kTLaunchException( kT::Exception, "Failed to get the window attributes" );

            mySize.Width  = windowAttributes.width;
            mySize.Height = windowAttributes.height;

            XSelectInput( X11Package::ourDisplay, myWindowHandle, eventMask & ~ButtonPressMask);
            Initialize();
        }
    }

    void KT_API Window::Destroy()
    {
        if ( myInputContext )
        {
            XDestroyIC( myInputContext );
            myInputContext = 0;
        }

        // Destroy the window
        if ( myWindowHandle && !myIsExternal )
        {
            XDestroyWindow( X11Package::ourDisplay, myWindowHandle );
            myWindowHandle = 0;
            XFlush( X11Package::ourDisplay );
        }
    }

    void KT_API Window::SetCaption( const std::string& caption )
    {
        XStoreName( X11Package::ourDisplay, myWindowHandle, caption.c_str() );
    }

    void KT_API Window::Show( bool show )
    {
        if ( show == true )
            XMapWindow( X11Package::ourDisplay, myWindowHandle );
        else
            XUnmapWindow( X11Package::ourDisplay, myWindowHandle );
    }

    void KT_API Window::EnableKeyRepeat( bool enabled)
    {
        if ( enabled == true )
            XAutoRepeatOn( X11Package::ourDisplay );
        else
            XAutoRepeatOff( X11Package::ourDisplay );

        XFlush( X11Package::ourDisplay );
    }

    void KT_API Window::Resize( const Sizeui32& size )
    {
        mySize = size;
        XResizeWindow( X11Package::ourDisplay, myWindowHandle, size.Width, size.Height );
    }

    Vector2< Uint32 > KT_API Window::GetCursorPosition() const
    {
        return Vector2< Uint32 >();
    }

    void KT_API Window::SetCursorPosition( const Vector2< Uint32 >& newPos )
    {
        XWarpPointer( X11Package::ourDisplay, None, myWindowHandle, 0, 0, 0, 0, newPos.x, newPos.y );
        XFlush( X11Package::ourDisplay );
    }

    void KT_API Window::ShowCursor( bool show )
    {
        XDefineCursor( X11Package::ourDisplay, myWindowHandle, show == true ? None : myHiddenCursor );
        XFlush( X11Package::ourDisplay );
    }

    static Bool CheckEvent( Display*, XEvent* Event, XPointer UserData )
    {
        // Just check if the event matches our window
        return Event->xany.window == reinterpret_cast< ::Window >(UserData);
    }

    void KT_API Window::ProcessEvents()
    {
        XEvent WinEvent;
        while ( XCheckIfEvent( X11Package::ourDisplay,
                               &WinEvent,
                               CheckEvent,
                               reinterpret_cast<XPointer>(myWindowHandle)
                               ) )
       {
           switch (WinEvent.type)
            {
                // Destroy event
                case DestroyNotify :
                {
                    // The window is about to be destroyed : we must cleanup resources
                    ShowCursor();
                    break;
                }

                // Gain focus event
                case FocusIn :
                {
                    // Update the input context
                    if (myInputContext)
                        XSetICFocus(myInputContext);

                    GUIEvent Evt;
                    Evt.Type = GUIEvent::GainedFocus;
                    SendEvent( &Evt );
                    break;
                }

                // Lost focus event
                case FocusOut :
                {
                    // Update the input context
                    if (myInputContext)
                        XUnsetICFocus(myInputContext);

                    GUIEvent Evt;
                    Evt.Type = GUIEvent::LostFocus;
                    SendEvent( &Evt );
                    break;
                }

                // Resize event
                case ConfigureNotify :
                {
                    if ((WinEvent.xconfigure.width != static_cast<int>(mySize.Width)) || (WinEvent.xconfigure.height != static_cast<int>(mySize.Height)))
                    {
                        mySize.Width  = WinEvent.xconfigure.width;
                        mySize.Height = WinEvent.xconfigure.height;

                        GUIEvent Evt;
                        Evt.Type        = GUIEvent::Resized;
                        Evt.Size.Width  = mySize.Width;
                        Evt.Size.Height = mySize.Height;
                        SendEvent( &Evt );
                    }
                    break;
                }

                // Close event
                case ClientMessage :
                {
                    if ((WinEvent.xclient.format == 32) && (WinEvent.xclient.data.l[0]) == static_cast<long>(myAtomClose))
                    {
                        GUIEvent Evt;
                        Evt.Type = GUIEvent::Closed;
                        SendEvent( &Evt );
                    }
                    break;
                }

                            // Key down event
                case KeyPress :
                {
                    // Get the keysym of the key that has been pressed
                    static XComposeStatus KeyboardStatus;
                    char Buffer[32];
                    KeySym Sym;
                    XLookupString(&WinEvent.xkey, Buffer, sizeof(Buffer), &Sym, &KeyboardStatus);

                    // Fill the event parameters
                    GUIEvent Evt;
                    Evt.Type        = GUIEvent::KeyPressed;
                    Evt.Key.Code    = TranslateKeysym(Sym);
                    Evt.Key.Alt     = WinEvent.xkey.state & Mod1Mask;
                    Evt.Key.Control = WinEvent.xkey.state & ControlMask;
                    Evt.Key.Shift   = WinEvent.xkey.state & ShiftMask;
                    Evt.Key.System  = WinEvent.xkey.state & Mod4Mask;
                    SendEvent( &Evt );

                    // Generate a TextEntered event
                    if (!XFilterEvent(&WinEvent, None))
                    {
                        #ifdef X_HAVE_UTF8_STRING
                        if (myInputContext)
                        {
                            Status ReturnedStatus;
                            Uint8  KeyBuffer[16];
                            if (Xutf8LookupString(myInputContext, &WinEvent.xkey, reinterpret_cast<char*>(KeyBuffer), sizeof(KeyBuffer), NULL, &ReturnedStatus))
                            {
                                GUIEvent TextEvt;
                                TextEvt.Type         = GUIEvent::TextEntered;
                                TextEvt.Text.Unicode = UTF8toUTF16(KeyBuffer);
                                SendEvent( &TextEvt );
                            }
                        }
                        else
                        #endif
                        {
                            static XComposeStatus ComposeStatus;
                            char KeyBuffer[16];
                            if (XLookupString(&WinEvent.xkey, KeyBuffer, sizeof(KeyBuffer), NULL, &ComposeStatus))
                            {
                                GUIEvent TextEvt;
                                TextEvt.Type         = GUIEvent::TextEntered;
                                TextEvt.Text.Unicode = KeyBuffer[0];
                                SendEvent( &TextEvt );
                            }
                        }
                    }

                    break;
                }

                // Key up event
                case KeyRelease :
                {
                    // Get the keysym of the key that has been pressed
                    char Buffer[32];
                    KeySym Sym;
                    XLookupString(&WinEvent.xkey, Buffer, 32, &Sym, NULL);

                    // Fill the event parameters
                    GUIEvent Evt;
                    Evt.Type        = GUIEvent::KeyReleased;
                    Evt.Key.Code    = TranslateKeysym(Sym);
                    Evt.Key.Alt     = WinEvent.xkey.state & Mod1Mask;
                    Evt.Key.Control = WinEvent.xkey.state & ControlMask;
                    Evt.Key.Shift   = WinEvent.xkey.state & ShiftMask;
                    Evt.Key.System  = WinEvent.xkey.state & Mod4Mask;

                    SendEvent( &Evt );
                    break;
                }

                // Mouse button pressed
                case ButtonPress :
                {
                    unsigned int Button = WinEvent.xbutton.button;
                    if ((Button == Button1) || (Button == Button2) || (Button == Button3) || (Button == 8) || (Button == 9))
                    {
                        GUIEvent Evt;
                        Evt.Type = GUIEvent::MouseButtonPressed;
                        switch (Button)
                        {
                            case Button1 : Evt.MouseButton.Button = Mouse::Left;     break;
                            case Button2 : Evt.MouseButton.Button = Mouse::Middle;   break;
                            case Button3 : Evt.MouseButton.Button = Mouse::Right;    break;
                            case 8 :       Evt.MouseButton.Button = Mouse::XButton1; break;
                            case 9 :       Evt.MouseButton.Button = Mouse::XButton2; break;
                        }
                        SendEvent( &Evt );
                    }
                    break;
                }

                // Mouse button released
                case ButtonRelease :
                {
                    unsigned int Button = WinEvent.xbutton.button;
                    if ((Button == Button1) || (Button == Button2) || (Button == Button3) || (Button == 8) || (Button == 9))
                    {
                        GUIEvent Evt;
                        Evt.Type = GUIEvent::MouseButtonReleased;
                        switch (Button)
                        {
                            case Button1 : Evt.MouseButton.Button = Mouse::Left;     break;
                            case Button2 : Evt.MouseButton.Button = Mouse::Middle;   break;
                            case Button3 : Evt.MouseButton.Button = Mouse::Right;    break;
                            case 8 :       Evt.MouseButton.Button = Mouse::XButton1; break;
                            case 9 :       Evt.MouseButton.Button = Mouse::XButton2; break;
                        }
                        SendEvent( &Evt );
                    }
                    else if ((Button == Button4) || (Button == Button5))
                    {
                        GUIEvent Evt;
                        Evt.Type             = GUIEvent::MouseWheelMoved;
                        Evt.MouseWheel.Delta = WinEvent.xbutton.button == Button4 ? 1 : -1;
                        SendEvent( &Evt );
                    }
                    break;
                }

                // Mouse moved
                case MotionNotify :
                {
                    GUIEvent Evt;
                    Evt.Type        = GUIEvent::MouseMoved;
                    Evt.MouseMove.X = WinEvent.xmotion.x;
                    Evt.MouseMove.Y = WinEvent.xmotion.y;
                    SendEvent( &Evt );
                    break;
                }
            }
       }
    }

    void Window::Initialize()
    {
        myAtomClose = XInternAtom( X11Package::ourDisplay, "WM_DELETE_WINDOW", false);
        XSetWMProtocols( X11Package::ourDisplay, myWindowHandle, &myAtomClose, 1);

        if ( X11Package::ourInputMethod )
        {
            myInputContext = XCreateIC( X11Package::ourInputMethod,
                               XNClientWindow,  myWindowHandle,
                               XNFocusWindow,   myWindowHandle,
                               XNInputStyle,    XIMPreeditNothing  | XIMStatusNothing,
                               //XNResourceName,  "kT",
                               //XNResourceClass, "kT",
                               0 );
        }

        CreateHiddenCursor();

        XFlush( X11Package::ourDisplay );
    }

    void Window::CreateHiddenCursor()
    {
        // Create the cursor's pixmap (1x1 pixels)
        Pixmap CursorPixmap = XCreatePixmap( X11Package::ourDisplay, myWindowHandle, 1, 1, 1 );
        GC GraphicsContext = XCreateGC( X11Package::ourDisplay, CursorPixmap, 0, 0 );
        XDrawPoint( X11Package::ourDisplay, CursorPixmap, GraphicsContext, 0, 0 );
        XFreeGC( X11Package::ourDisplay, GraphicsContext );

        // Create the cursor, using the pixmap as both the shape and the mask of the cursor
        XColor Color;
        Color.flags = DoRed | DoGreen | DoBlue;
        Color.red = Color.blue = Color.green = 0;
        myHiddenCursor = XCreatePixmapCursor( X11Package::ourDisplay, CursorPixmap, CursorPixmap, &Color, &Color, 0, 0 );

        // We don't need the pixmap any longer, free it
        XFreePixmap( X11Package::ourDisplay, CursorPixmap );
    }

    Keyboard::Key Window::TranslateKeysym(KeySym symbol)
    {
        // First convert to uppercase (to avoid dealing with two different keysyms for the same key)
        KeySym lower, key;
        XConvertCase(symbol, &lower, &key);

        switch (key)
        {
            case XK_Shift_L :      return Keyboard::LShift;
            case XK_Shift_R :      return Keyboard::RShift;
            case XK_Control_L :    return Keyboard::LControl;
            case XK_Control_R :    return Keyboard::RControl;
            case XK_Alt_L :        return Keyboard::LAlt;
            case XK_Alt_R :        return Keyboard::RAlt;
            case XK_Super_L :      return Keyboard::LSystem;
            case XK_Super_R :      return Keyboard::RSystem;
            case XK_Menu :         return Keyboard::Menu;
            case XK_Escape :       return Keyboard::Escape;
            case XK_semicolon :    return Keyboard::SemiColon;
            case XK_slash :        return Keyboard::Slash;
            case XK_equal :        return Keyboard::Equal;
            case XK_bracketleft :  return Keyboard::LBracket;
            case XK_bracketright : return Keyboard::RBracket;
            case XK_comma :        return Keyboard::Comma;
            case XK_period :       return Keyboard::Period;
            case XK_dead_acute :   return Keyboard::Quote;
            case XK_backslash :    return Keyboard::BackSlash;
            case XK_space :        return Keyboard::Space;
            case XK_Return :       return Keyboard::Return;
            case XK_KP_Enter :     return Keyboard::Return;
            case XK_BackSpace :    return Keyboard::BackSpace;
            case XK_Tab :          return Keyboard::Tab;
            case XK_Prior :        return Keyboard::PageUp;
            case XK_Next :         return Keyboard::PageDown;
            case XK_End :          return Keyboard::End;
            case XK_Home :         return Keyboard::Home;
            case XK_Insert :       return Keyboard::Insert;
            case XK_Delete :       return Keyboard::Delete;
            case XK_KP_Add :       return Keyboard::Add;
            case XK_KP_Subtract :  return Keyboard::Subtract;
            case XK_KP_Multiply :  return Keyboard::Multiply;
            case XK_KP_Divide :    return Keyboard::Divide;
            case XK_Pause :        return Keyboard::Pause;
            case XK_F1 :           return Keyboard::F1;
            case XK_F2 :           return Keyboard::F2;
            case XK_F3 :           return Keyboard::F3;
            case XK_F4 :           return Keyboard::F4;
            case XK_F5 :           return Keyboard::F5;
            case XK_F6 :           return Keyboard::F6;
            case XK_F7 :           return Keyboard::F7;
            case XK_F8 :           return Keyboard::F8;
            case XK_F9 :           return Keyboard::F9;
            case XK_F10 :          return Keyboard::F10;
            case XK_F11 :          return Keyboard::F11;
            case XK_F12 :          return Keyboard::F12;
            case XK_F13 :          return Keyboard::F13;
            case XK_F14 :          return Keyboard::F14;
            case XK_F15 :          return Keyboard::F15;
            case XK_Left :         return Keyboard::Left;
            case XK_Right :        return Keyboard::Right;
            case XK_Up :           return Keyboard::Up;
            case XK_Down :         return Keyboard::Down;
            case XK_KP_0 :         return Keyboard::Numpad0;
            case XK_KP_1 :         return Keyboard::Numpad1;
            case XK_KP_2 :         return Keyboard::Numpad2;
            case XK_KP_3 :         return Keyboard::Numpad3;
            case XK_KP_4 :         return Keyboard::Numpad4;
            case XK_KP_5 :         return Keyboard::Numpad5;
            case XK_KP_6 :         return Keyboard::Numpad6;
            case XK_KP_7 :         return Keyboard::Numpad7;
            case XK_KP_8 :         return Keyboard::Numpad8;
            case XK_KP_9 :         return Keyboard::Numpad9;
            case XK_A :            return Keyboard::A;
            case XK_Z :            return Keyboard::Z;
            case XK_E :            return Keyboard::E;
            case XK_R :            return Keyboard::R;
            case XK_T :            return Keyboard::T;
            case XK_Y :            return Keyboard::Y;
            case XK_U :            return Keyboard::U;
            case XK_I :            return Keyboard::I;
            case XK_O :            return Keyboard::O;
            case XK_P :            return Keyboard::P;
            case XK_Q :            return Keyboard::Q;
            case XK_S :            return Keyboard::S;
            case XK_D :            return Keyboard::D;
            case XK_F :            return Keyboard::F;
            case XK_G :            return Keyboard::G;
            case XK_H :            return Keyboard::H;
            case XK_J :            return Keyboard::J;
            case XK_K :            return Keyboard::K;
            case XK_L :            return Keyboard::L;
            case XK_M :            return Keyboard::M;
            case XK_W :            return Keyboard::W;
            case XK_X :            return Keyboard::X;
            case XK_C :            return Keyboard::C;
            case XK_V :            return Keyboard::V;
            case XK_B :            return Keyboard::B;
            case XK_N :            return Keyboard::N;
            case XK_0 :            return Keyboard::Num0;
            case XK_1 :            return Keyboard::Num1;
            case XK_2 :            return Keyboard::Num2;
            case XK_3 :            return Keyboard::Num3;
            case XK_4 :            return Keyboard::Num4;
            case XK_5 :            return Keyboard::Num5;
            case XK_6 :            return Keyboard::Num6;
            case XK_7 :            return Keyboard::Num7;
            case XK_8 :            return Keyboard::Num8;
            case XK_9 :            return Keyboard::Num9;
        }

        return Keyboard::Unknown;
    }
}

#endif
