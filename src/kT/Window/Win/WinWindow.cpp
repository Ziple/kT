#include <kT/Window/WindowManager.hpp>

#if defined(KT_WM_WIN)

#define WINVER 0x500
#include <windows.h>

# include <kT/Window/Win/WinWindow.hpp>

#include <kT/Core/Exceptions.hpp>

#include <sstream>

#ifndef XBUTTON1
    #define XBUTTON1 0x0001
#endif
#ifndef XBUTTON2
    #define XBUTTON2 0x0002
#endif

namespace kT
{
    bool _hasUnicodeSupport()
    {
        OSVERSIONINFO VersionInfo;
        ZeroMemory( &VersionInfo, sizeof( VersionInfo ) );
        VersionInfo.dwOSVersionInfoSize = sizeof( VersionInfo );

        if ( GetVersionEx( &VersionInfo ) )
        {
            return VersionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT ? true : false;
        }
        else
            return false;
    }

    wchar_t* _charToWChar( const char* in )
    {
        unsigned int size = strlen( in );

        wchar_t* string = new wchar_t[ size ];

        int nbChars = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, in, size, string, size+1 );

        if ( nbChars == 0 )
            return 0;

        string[ nbChars ] = L'\0';

        return string;
    }


    Uint32 Window::ourWindowCount = 0;

    KT_API Window::Window():
     WindowBase( 0 ),
     myCallback( 0 ),
     myStyle( Window::NoDecoration )
    {
        if ( ourWindowCount == 0 )
            RegisterWindowClass();

        // Use small dimensions
        mySize.Width  = 1;
        mySize.Height = 1;

        // Create a dummy window (disabled and hidden)
        if ( _hasUnicodeSupport() )
            myWindowHandle = CreateWindowW( L"kTEngineWindowClass",
                                            L"",
                                            WS_POPUP | WS_DISABLED,
                                            0, 0, 1, 1,
                                            0, 0,
                                            GetModuleHandle( NULL ),
                                            0 );
        else
            myWindowHandle = CreateWindowA( "kTEngineWindowClass",
                                            "",
                                            WS_POPUP | WS_DISABLED,
                                            0, 0, 1, 1,
                                            0, 0,
                                            GetModuleHandle( NULL ),
                                            0 );

        // set the window hidden
        ShowWindow( myWindowHandle, SW_HIDE );
    }

    KT_API Window::Window( const std::string& caption, const Sizeui32& size, Uint32 style ):
     WindowBase( 0 ),
     myCallback( 0 ),
     myStyle( style )
    {
        Create( caption, size, style);
    }

    KT_API Window::Window( WindowHandle nativeHandle ):
     WindowBase( 0 ),
     myCallback( 0 )
    {
        Create( nativeHandle );
    }

    KT_API Window::~Window()
    {
        Destroy();
    }

    void KT_API Window::Create( WindowHandle nativeHandle )
    {
        myWindowHandle = nativeHandle;

        if( myWindowHandle )
        {
            // retrieve window's size
            RECT Rect;
            GetClientRect(myWindowHandle, &Rect);
            mySize.Width  = Rect.right - Rect.left;
            mySize.Height = Rect.bottom - Rect.top;

            // We change the event procedure of the control (it is important to save the old one)
            SetWindowLongPtr( myWindowHandle, GWLP_USERDATA, reinterpret_cast<long>( this ) );
            myCallback = SetWindowLongPtr( myWindowHandle, GWLP_WNDPROC, reinterpret_cast<long>( &Window::WndProc ) );
        }
    }

    void KT_API Window::Create( const std::string& caption, const Sizeui32& size, Uint32 style )
    {
        if( myWindowHandle )
            Destroy();

        if ( ourWindowCount == 0 )
            RegisterWindowClass();

        // Compute position and size
        int Left, Top, Width, Height;
        DWORD Win32Style = 0;

        bool fullscreen = (style & Window::Fullscreen) != 0;

        if ( fullscreen )
        {
            // update the size according to the desktop size (we don't change resolution)
            Left = Top = 0;
            Width = mySize.Width = GetDeviceCaps( GetDC( 0 ), HORZRES );
            Height = mySize.Height = GetDeviceCaps( GetDC( 0 ), VERTRES );
            Win32Style = WS_POPUP;
        }
        else
        {
            // find left and top to be centered on the screen
            Left   = ( GetDeviceCaps( GetDC( 0 ), HORZRES ) - size.Width )  / 2;
            Top    = ( GetDeviceCaps( GetDC( 0 ), VERTRES ) - size.Height ) / 2;
            Width  = mySize.Width  = size.Width;
            Height = mySize.Height = size.Height;

            // Choose the window style according to the Style parameter
            if( style & Window::NoDecoration )         Win32Style = WS_POPUP;
            else
            {
                if ( style & Window::Titlebar )   Win32Style = WS_CAPTION | WS_MINIMIZEBOX;
                if ( style & Window::Resizable )  Win32Style |= WS_THICKFRAME | WS_MAXIMIZEBOX;
                if ( style & Window::Closable )   Win32Style |= WS_SYSMENU;
            }

            // find the real dimensions according to the requested style
            RECT Rect = {0, 0, Width, Height};
            AdjustWindowRect(&Rect, Win32Style, false);
            Width  = Rect.right - Rect.left;
            Height = Rect.bottom - Rect.top;
        }

        // Create the window
        if ( _hasUnicodeSupport() == true )
            myWindowHandle = CreateWindowW( L"kTEngineWindowClass",
                                            _charToWChar( caption.c_str() ),
                                            Win32Style,
                                            Left, Top, Width, Height,
                                            0,
                                            0,
                                            GetModuleHandle( NULL ),
                                            this);
        else
            myWindowHandle = CreateWindowA( "kTEngineWindowClass",
                                            caption.c_str(),
                                            Win32Style,
                                            Left, Top, Width, Height,
                                            0,
                                            0,
                                            GetModuleHandle( NULL ),
                                            this);

        if( myWindowHandle == 0 )
        {
            std::ostringstream out;
            out<<"The creation of the windows failed! Error code: "<<GetLastError();

            kTLaunchException( kT::Exception, out.str() );
        }

        // By default, the OS limits the size of the window the the desktop size,
        // we have to resize it after creation to apply the real size
        Resize(size);

        // increment the window count so as don't
        // unregister window class if there are more than one window
        ourWindowCount++;
    }

    void KT_API Window::Destroy()
    {
        if ( !myCallback )
        {
            // Destroy the window
            if ( myWindowHandle )
                DestroyWindow( myWindowHandle );

            // Decrement the window count
            ourWindowCount--;

            // Unregister window class if we were the last window
            if ( ourWindowCount == 0)
                UnregisterWindowClass();
        }
        else
        {
            // The window is external : remove the hook on its message callback
            SetWindowLongPtr( myWindowHandle, GWLP_WNDPROC, myCallback );
        }
    }

    void KT_API Window::SetCaption( const std::string& caption )
    {
        if( _hasUnicodeSupport() )
            SetWindowTextW( myWindowHandle, _charToWChar( caption.c_str() ) );
        else
            SetWindowTextA( myWindowHandle, caption.c_str() );
    }

    void KT_API Window::Show( bool show)
    {
        ShowWindow(myWindowHandle, show == true ? SW_SHOW : SW_HIDE);
        UpdateWindow(myWindowHandle);
    }

    void KT_API Window::Resize( const Sizeui32& size )
    {
        SetWindowPos( myWindowHandle, HWND_TOP, 0, 0, size.Width, size.Height, SWP_NOMOVE );
    }

    Vector2< Uint32 > KT_API Window::GetCursorPosition() const
    {
        POINT cursorPos;
        GetCursorPos( &cursorPos );
        return Vector2< Uint32 >( cursorPos.x, cursorPos.y );
    }

    void KT_API Window::SetCursorPosition( const Vector2< Uint32 >& newPos )
    {
        SetCursorPos( newPos.x, newPos.y );
    }

    void KT_API Window::ShowCursor( bool show )
    {
        ::ShowCursor( show == true ? TRUE : FALSE );
    }

    void KT_API Window::ProcessEvents()
    {
        MSG msg;
        while ( PeekMessage( &msg, myWindowHandle, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    LRESULT CALLBACK Window::WndProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam )
    {
        // Associate handle and Window instance when the creation message is received
        if (message == WM_CREATE)
        {
            // Get WindowImplWin32 instance (it was passed as the last argument of CreateWindow)
            LONG_PTR window = (LONG_PTR)reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams;

            // Set as the "user data" parameter of the window
            SetWindowLongPtr(handle, GWLP_USERDATA, window);
        }

        // Get the WindowImpl instance corresponding to the window handle
        Window* window = handle ? reinterpret_cast<Window*>(GetWindowLongPtr(handle, GWLP_USERDATA)) : NULL;

        // Forward the event to the appropriate function
        if (window)
        {
            window->RealWndProc(message, wParam, lParam);

            if (window->myCallback)
                return CallWindowProc(reinterpret_cast<WNDPROC>(window->myCallback), handle, message, wParam, lParam);
        }

        // We don't forward the WM_CLOSE message to prevent the OS from automatically destroying the window
        if (message == WM_CLOSE)
            return 0;

        // Don't forward the menu system command, so that pressing ALT or F10 doesn't steal the focus
        if ((message == WM_SYSCOMMAND) && (wParam == SC_KEYMENU))
            return 0;

        static const bool hasUnicode = _hasUnicodeSupport();
        return hasUnicode ? DefWindowProcW(handle, message, wParam, lParam) :
                            DefWindowProcA(handle, message, wParam, lParam);
    }

    void Window::RegisterWindowClass()
    {
        if ( _hasUnicodeSupport() )
        {
            WNDCLASSEXW windowClass;
            windowClass.cbSize = sizeof( WNDCLASSEX );
            windowClass.style = CS_VREDRAW | CS_HREDRAW;
            windowClass.lpfnWndProc = &Window::WndProc;
            windowClass.cbClsExtra = 0;
            windowClass.cbWndExtra = 0;
            windowClass.hInstance = /*WinPackage::ourInstance*/GetModuleHandle( NULL );
            windowClass.hIcon = LoadIcon(0, IDI_APPLICATION);
            windowClass.hCursor = LoadCursor(0, IDC_ARROW);
            windowClass.hbrBackground = 0;
            windowClass.lpszMenuName = 0;
            windowClass.lpszClassName = L"kTEngineWindowClass";
            windowClass.hIconSm = 0;
            RegisterClassExW( &windowClass );
        }
        else
        {
            WNDCLASSEXA windowClass;
            windowClass.cbSize = sizeof( WNDCLASSEX );
            windowClass.style = CS_VREDRAW | CS_HREDRAW;
            windowClass.lpfnWndProc = &Window::WndProc;
            windowClass.cbClsExtra = 0;
            windowClass.cbWndExtra = 0;
            windowClass.hInstance = /*WinPackage::ourInstance*/GetModuleHandle( NULL );
            windowClass.hIcon = LoadIcon(0, IDI_APPLICATION);
            windowClass.hCursor = LoadCursor(0, IDC_ARROW);
            windowClass.hbrBackground = 0;
            windowClass.lpszMenuName = 0;
            windowClass.lpszClassName = "kTEngineWindowClass";
            windowClass.hIconSm = 0;
            RegisterClassExA( &windowClass );
        }
    }

    void Window::UnregisterWindowClass()
    {
        if( _hasUnicodeSupport() )
            UnregisterClassW( L"kTEngineWindowClass", GetModuleHandle( NULL ) );
        else
            UnregisterClassA( "kTEngineWindowClass", GetModuleHandle( NULL ) );
    }

    void Window::RealWndProc( UINT uMsg, WPARAM wParam, LPARAM lParam )
    {
        // Don't process any message until window is created
        if ( myWindowHandle == 0 )
            return;

        switch ( uMsg )
        {
            // Destroy event
            case WM_DESTROY :
            {
                // Here we must cleanup resources !
                break;
            }

            // Set cursor event
            case WM_SETCURSOR :
            {
                // The mouse has moved, if the cursor is in our window we must refresh the cursor
                if (LOWORD(lParam) == HTCLIENT)
                    SetCursor( 0 );

                break;
            }

            // Close event
            case WM_CLOSE :
            {
                GUIEvent Evt;
                Evt.Type = GUIEvent::Closed;
                SendEvent( &Evt );
                break;
            }

            case WM_PAINT:
            {
                PAINTSTRUCT ps;
                BeginPaint( myWindowHandle, &ps );
                EndPaint( myWindowHandle, &ps );
                break;
            }

            // Resize event
            case WM_SIZE :
            {
                // Update window size
                RECT Rect;
                GetClientRect( myWindowHandle, &Rect );
                mySize.Width  = Rect.right - Rect.left;
                mySize.Height = Rect.bottom - Rect.top;

                GUIEvent Evt;
                Evt.Type        = GUIEvent::Resized;
                Evt.Size.Width  = mySize.Width;
                Evt.Size.Height = mySize.Height;
                SendEvent( &Evt );
                break;
            }

            // The system request the min/max window size and position
            case WM_GETMINMAXINFO :
            {
                // We override the returned information to remove the default limit
                // (the OS doesn't allow windows bigger than the desktop by default)
                MINMAXINFO* info = reinterpret_cast<MINMAXINFO*>(lParam);
                info->ptMaxTrackSize.x = 50000;
                info->ptMaxTrackSize.y = 50000;
                break;
            }

            // Gain focus event
            case WM_SETFOCUS :
            {
                GUIEvent Evt;
                Evt.Type = GUIEvent::GainedFocus;
                SendEvent( &Evt );
                break;
            }

            // Lost focus event
            case WM_KILLFOCUS :
            {
                GUIEvent Evt;
                Evt.Type = GUIEvent::LostFocus;
                SendEvent( &Evt );
                break;
            }

            // Text event
            case WM_CHAR :
            {
                GUIEvent Evt;
                Evt.Type = GUIEvent::TextEntered;
                Evt.Text.Unicode = static_cast<Uint16>(wParam);
                SendEvent( &Evt );
                break;
            }

            // Keydown event
            case WM_KEYDOWN :
            case WM_SYSKEYDOWN :
            {
                if ( myKeyRepeatEnabled == true || ((HIWORD(lParam) & KF_REPEAT) == 0) )
                {
                    GUIEvent Evt;
                    Evt.Type        = GUIEvent::KeyPressed;
                    Evt.Key.Code    = TranslateKeyCode(wParam, lParam);
                    Evt.Key.Alt     = HIWORD(GetAsyncKeyState(VK_MENU))    != 0;
                    Evt.Key.Control = HIWORD(GetAsyncKeyState(VK_CONTROL)) != 0;
                    Evt.Key.Shift   = HIWORD(GetAsyncKeyState(VK_SHIFT))   != 0;
                    Evt.Key.System  = HIWORD(GetAsyncKeyState(VK_LWIN)) || HIWORD(GetAsyncKeyState(VK_RWIN));
                    SendEvent( &Evt );
                }
                break;
            }

            // Keyup event
            case WM_KEYUP :
            case WM_SYSKEYUP :
            {
                GUIEvent Evt;
                Evt.Type        = GUIEvent::KeyReleased;
                Evt.Key.Code    = TranslateKeyCode(wParam, lParam);
                Evt.Key.Alt     = HIWORD(GetAsyncKeyState(VK_MENU))    != 0;
                Evt.Key.Control = HIWORD(GetAsyncKeyState(VK_CONTROL)) != 0;
                Evt.Key.Shift   = HIWORD(GetAsyncKeyState(VK_SHIFT))   != 0;
                Evt.Key.System  = HIWORD(GetAsyncKeyState(VK_LWIN)) || HIWORD(GetAsyncKeyState(VK_RWIN));
                SendEvent( &Evt );
                break;
            }

            // Mouse wheel event
            case WM_MOUSEWHEEL :
            {
                GUIEvent Evt;
                Evt.Type = GUIEvent::MouseWheelMoved;
                Evt.MouseWheel.Delta = static_cast<Int16>(HIWORD(wParam)) / 120;
                SendEvent( &Evt );
                break;
            }

            // Mouse left button down event
            case WM_LBUTTONDOWN :
            {
                GUIEvent Evt;
                Evt.Type               = GUIEvent::MouseButtonPressed;
                Evt.MouseButton.Button = Mouse::Left;
                SendEvent( &Evt );
                break;
            }

            // Mouse left button up event
            case WM_LBUTTONUP :
            {
                GUIEvent Evt;
                Evt.Type               = GUIEvent::MouseButtonReleased;
                Evt.MouseButton.Button = Mouse::Left;
                SendEvent( &Evt );
                break;
            }

            // Mouse right button down event
            case WM_RBUTTONDOWN :
            {
                GUIEvent Evt;
                Evt.Type               = GUIEvent::MouseButtonPressed;
                Evt.MouseButton.Button = Mouse::Right;
                SendEvent( &Evt );
                break;
            }

            // Mouse right button up event
            case WM_RBUTTONUP :
            {
                GUIEvent Evt;
                Evt.Type               = GUIEvent::MouseButtonReleased;
                Evt.MouseButton.Button = Mouse::Right;
                SendEvent( &Evt );
                break;
            }

            // Mouse wheel button down event
            case WM_MBUTTONDOWN :
            {
                GUIEvent Evt;
                Evt.Type               = GUIEvent::MouseButtonPressed;
                Evt.MouseButton.Button = Mouse::Middle;
                SendEvent( &Evt );
                break;
            }

            // Mouse wheel button up event
            case WM_MBUTTONUP :
            {
                GUIEvent Evt;
                Evt.Type               = GUIEvent::MouseButtonReleased;
                Evt.MouseButton.Button = Mouse::Middle;
                SendEvent( &Evt );
                break;
            }

            // Mouse X button down event
            case WM_XBUTTONDOWN :
            {
                GUIEvent Evt;
                Evt.Type               = GUIEvent::MouseButtonPressed;
                Evt.MouseButton.Button = HIWORD(wParam) == XBUTTON1 ? Mouse::XButton1 : Mouse::XButton2;
                SendEvent( &Evt );
                break;
            }

            // Mouse X button up event
            case WM_XBUTTONUP :
            {
                GUIEvent Evt;
                Evt.Type               = GUIEvent::MouseButtonReleased;
                Evt.MouseButton.Button = HIWORD(wParam) == XBUTTON1 ? Mouse::XButton1 : Mouse::XButton2;
                SendEvent( &Evt );
                break;
            }

            // Mouse move event
            case WM_MOUSEMOVE :
            {
                GUIEvent Evt;
                Evt.Type        = GUIEvent::MouseMoved;
                Evt.MouseMove.X = LOWORD(lParam);
                Evt.MouseMove.Y = HIWORD(lParam);
                SendEvent( &Evt );
                break;
            }
        }
    }


    Keyboard::Key Window::TranslateKeyCode( WPARAM key, LPARAM flags )
    {
        switch (key)
        {
            // Check the scancode to distinguish between left and right shift
            case VK_SHIFT :
            {
                static UINT lShift = MapVirtualKey(VK_LSHIFT, MAPVK_VK_TO_VSC);
                UINT scancode = static_cast<UINT>((flags & (0xFF << 16)) >> 16);
                return scancode == lShift ? Keyboard::LShift : Keyboard::RShift;
            }

            // Check the "extended" flag to distinguish between left and right alt
            case VK_MENU : return (HIWORD(flags) & KF_EXTENDED) ? Keyboard::RAlt : Keyboard::LAlt;

            // Check the "extended" flag to distinguish between left and right control
            case VK_CONTROL : return (HIWORD(flags) & KF_EXTENDED) ? Keyboard::RControl : Keyboard::LControl;

            // Other keys are reported properly
            case VK_LWIN :       return Keyboard::LSystem;
            case VK_RWIN :       return Keyboard::RSystem;
            case VK_APPS :       return Keyboard::Menu;
            case VK_OEM_1 :      return Keyboard::SemiColon;
            case VK_OEM_2 :      return Keyboard::Slash;
            case VK_OEM_PLUS :   return Keyboard::Equal;
            case VK_OEM_4 :      return Keyboard::LBracket;
            case VK_OEM_6 :      return Keyboard::RBracket;
            case VK_OEM_COMMA :  return Keyboard::Comma;
            case VK_OEM_PERIOD : return Keyboard::Period;
            case VK_OEM_7 :      return Keyboard::Quote;
            case VK_OEM_5 :      return Keyboard::BackSlash;
            case VK_ESCAPE :     return Keyboard::Escape;
            case VK_SPACE :      return Keyboard::Space;
            case VK_RETURN :     return Keyboard::Return;
            case VK_BACK :       return Keyboard::BackSpace;
            case VK_TAB :        return Keyboard::Tab;
            case VK_PRIOR :      return Keyboard::PageUp;
            case VK_NEXT :       return Keyboard::PageDown;
            case VK_END :        return Keyboard::End;
            case VK_HOME :       return Keyboard::Home;
            case VK_INSERT :     return Keyboard::Insert;
            case VK_DELETE :     return Keyboard::Delete;
            case VK_ADD :        return Keyboard::Add;
            case VK_SUBTRACT :   return Keyboard::Subtract;
            case VK_MULTIPLY :   return Keyboard::Multiply;
            case VK_DIVIDE :     return Keyboard::Divide;
            case VK_PAUSE :      return Keyboard::Pause;
            case VK_F1 :         return Keyboard::F1;
            case VK_F2 :         return Keyboard::F2;
            case VK_F3 :         return Keyboard::F3;
            case VK_F4 :         return Keyboard::F4;
            case VK_F5 :         return Keyboard::F5;
            case VK_F6 :         return Keyboard::F6;
            case VK_F7 :         return Keyboard::F7;
            case VK_F8 :         return Keyboard::F8;
            case VK_F9 :         return Keyboard::F9;
            case VK_F10 :        return Keyboard::F10;
            case VK_F11 :        return Keyboard::F11;
            case VK_F12 :        return Keyboard::F12;
            case VK_F13 :        return Keyboard::F13;
            case VK_F14 :        return Keyboard::F14;
            case VK_F15 :        return Keyboard::F15;
            case VK_LEFT :       return Keyboard::Left;
            case VK_RIGHT :      return Keyboard::Right;
            case VK_UP :         return Keyboard::Up;
            case VK_DOWN :       return Keyboard::Down;
            case VK_NUMPAD0 :    return Keyboard::Numpad0;
            case VK_NUMPAD1 :    return Keyboard::Numpad1;
            case VK_NUMPAD2 :    return Keyboard::Numpad2;
            case VK_NUMPAD3 :    return Keyboard::Numpad3;
            case VK_NUMPAD4 :    return Keyboard::Numpad4;
            case VK_NUMPAD5 :    return Keyboard::Numpad5;
            case VK_NUMPAD6 :    return Keyboard::Numpad6;
            case VK_NUMPAD7 :    return Keyboard::Numpad7;
            case VK_NUMPAD8 :    return Keyboard::Numpad8;
            case VK_NUMPAD9 :    return Keyboard::Numpad9;
            case 'A' :           return Keyboard::A;
            case 'Z' :           return Keyboard::Z;
            case 'E' :           return Keyboard::E;
            case 'R' :           return Keyboard::R;
            case 'T' :           return Keyboard::T;
            case 'Y' :           return Keyboard::Y;
            case 'U' :           return Keyboard::U;
            case 'I' :           return Keyboard::I;
            case 'O' :           return Keyboard::O;
            case 'P' :           return Keyboard::P;
            case 'Q' :           return Keyboard::Q;
            case 'S' :           return Keyboard::S;
            case 'D' :           return Keyboard::D;
            case 'F' :           return Keyboard::F;
            case 'G' :           return Keyboard::G;
            case 'H' :           return Keyboard::H;
            case 'J' :           return Keyboard::J;
            case 'K' :           return Keyboard::K;
            case 'L' :           return Keyboard::L;
            case 'M' :           return Keyboard::M;
            case 'W' :           return Keyboard::W;
            case 'X' :           return Keyboard::X;
            case 'C' :           return Keyboard::C;
            case 'V' :           return Keyboard::V;
            case 'B' :           return Keyboard::B;
            case 'N' :           return Keyboard::N;
            case '0' :           return Keyboard::Num0;
            case '1' :           return Keyboard::Num1;
            case '2' :           return Keyboard::Num2;
            case '3' :           return Keyboard::Num3;
            case '4' :           return Keyboard::Num4;
            case '5' :           return Keyboard::Num5;
            case '6' :           return Keyboard::Num6;
            case '7' :           return Keyboard::Num7;
            case '8' :           return Keyboard::Num8;
            case '9' :           return Keyboard::Num9;
        }

        return Keyboard::Unknown;
    }
}

#endif
