/**
 * \file Window//Base/WindowBase.hpp
 * \author Damien Hilloulin (ziple)
 * \date 21/03/2009
 * \brief Contains the definition of the WindowBase class.
 */
#ifndef __KTWINDOWBASE_HPP__
#define __KTWINDOWBASE_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>
#include <kT/Core/NonCopyable.hpp>
#include "../GUIEvent.hpp"
#include <kT/Math/Size.hpp>
#include <kT/Math/Vector2.hpp>

#include <string>
#include <list>

#include "../WindowManager.hpp"

#if defined(KT_WM_WIN)
struct HWND__;
typedef HWND__ *WindowHandle;
#elif defined(KT_WM_X11)
typedef unsigned long WindowHandle;
#endif

namespace kT
{
    /**
     * \ingroup ktgui_module
     * \brief Base class for window classes implementations.
     *
     * This class provides some code to make it easier to code a new window
     * class implementation for a port.
     */
	class KT_API WindowBase: public NonCopyable, public EventEmitter<GUIEvent>, protected EventListener<GUIEvent>
    {
        public:

            /**
             * \brief Base constructor taking the native handle.
             */
            WindowBase( WindowHandle windowHandle );

            /**
             * \brief Get method for the window's size.
             */
            const Sizeui32& GetSize() const {return mySize;}

            /**
             * \brief Get the event on top of events stack, if any, and pop it.
             */
            bool GetEvent( GUIEvent& fillMe );

            /**
             * \brief Get the native handle of the window.
             */
            WindowHandle GetWindowHandle() const {return myWindowHandle;}

        protected:

            /**
             * \brief Adds the event at the event stack.
             *
             * It adds the event if it comes from the window itself.
             */
            void OnEvent( const EventEmitter<GUIEvent>* emitter, const GUIEvent* event );

            /**
             * \brief Utility function to convert UTF8 strings to UTF16 ones.
             */
            static Uint16 UTF8toUTF16(const Uint8* Source);

            Sizeui32 mySize;   ///< Size of the window.
            WindowHandle myWindowHandle;///< Native handle of the window.
            bool myKeyRepeatEnabled;       ///< Wether or not key-repeat is enabled.
            std::list<GUIEvent> myEvents;  ///< Pending events
    };
}

#endif /* __KTWINDOWBASE_HPP__ */
