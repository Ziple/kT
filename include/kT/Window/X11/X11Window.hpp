/**
 * \file Window/X11/X11Window.hpp
 * \author Damien Hilloulin (ziple)
 * \date 21/03/2009
 * \brief Contains the implementation of the Window class for X11.
 */
#ifndef __KTX11WINDOW_HPP__
#define __KTX11WINDOW_HPP__

#include <kT/Core/Build.hpp>
#include "../Base/WindowBase.hpp"

typedef struct _XIC *XIC;
typedef unsigned long KeySym, Cursor, Atom;

namespace kT
{
    /**
     * \ingroup ktgui_module
     * \brief The class providing Window implementation on X11.
     */
    class KT_API Window: public WindowBase
    {
        public:

            /**
             * \ingroup ktgui_module
             * \brief Enumeration for windows styles.
             */
            enum WindowStyle
            {
                NoDecoration       = 0,///< No border / title bar (exclusive).
                Titlebar   = 1 << 0, ///< Title bar, fixed border
                Resizable     = 1 << 1, ///< Titlebar, resizable border, maximize button
                Closable      = 1 << 2, ///< Titlebar, close button

                /**
                 * \brief Fullscreen mode.
                 * This flag and all others are mutually exclusive.
                 * By setting this flag, the application won't change the desktop mode.
                 */
                Fullscreen = 1 << 3,
                Overlapped = Titlebar ///< Titlebar, resizable, closable.
                             | Closable
                             | Resizable
            };

            /**
             * \brief Default constructor.
             */
            Window();

            /**
             * \brief Detailed constructor.
             *
             * Creates a window with the specified caption, size and style
             * attributes by actually calling Window::Create().
             */
            Window( const std::string& caption, const Sizeui32& size, Uint32 style );

            /**
             * \brief Constructor from a native window handle.
             *
             * Doesn't change any window's attributes of the window handled.
             */
            Window( WindowHandle nativeHandle );

            /**
             * \brief Default destructor.
             *
             * Destroys the window only if it was created by the class.
             */
            ~Window();

            /**
             * \brief Creates a window from a native window handle.
             *
             * Just defers the event processing so that the class receive them
             * before the original event processor (the one specified at the native
             * window creation).
             */
            void Create( WindowHandle nativeHandle );

            /**
             * \brief The actual Create() call.
             *
             * This fonction actually create the window with the parameters.
             */
            void Create( const std::string& caption, const Sizeui32& size, Uint32 style );

            /**
             * \brief Destroys the window.
             *
             * Actually does it if the object is the owner of the window.
             */
            void Destroy();

            /**
             * \brief Changes the window's caption.
             */
            void SetCaption( const std::string& caption );

            /**
             * \brief Shows or hides the window.
             */
            void Show( bool show = true );


            /**
             * \brief Enables or disables key repeatition.
             */
            void EnableKeyRepeat( bool enabled );

            /**
             * \brief Resizes the window to the specified size.
             */
            void Resize( const Sizeui32& size );

            /**
             * \todo To implement.
             * \brief Returns the position of the cursor in window-relative coordinates.
             */
            Vector2< Uint32 > GetCursorPosition() const;

            /**
             * \brief Sets the position of the cursor.
             */
            void SetCursorPosition( const Vector2< Uint32 >& newPos );

            /**
             * \brief Shows or hides the cursor.
             */
            void ShowCursor( bool show = true );

            /**
             * \brief Pumps the pending events.
             *
             * This function must be called before attempting to getting events.
             */
            void ProcessEvents();

            Uint32 GetStyle() const {return myStyle;}

        private:

            static Uint32 ourWindowCount;

            /**
             * \brief Initialize some things.
             */
            void Initialize();

            /**
             * \brief Creates the hidden cursor so as to be able of hiding it.
             */
            void CreateHiddenCursor();

            /**
             * \brief Translates the keysym code to the Key::Code .
             */
            static Keyboard::Key TranslateKeysym( KeySym Sym );

            bool myIsExternal;
            Uint32 myStyle;
            XIC myInputContext;
            Atom myAtomClose;
            Cursor myHiddenCursor;
    };
}

#endif /* __KTX11WINDOW_HPP__ */
