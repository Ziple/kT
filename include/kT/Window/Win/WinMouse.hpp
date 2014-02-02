#ifndef __KT_WINMOUSE_HPP__
#define __KT_WINMOUSE_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Math/Vector2.hpp>
#include <kT/Window/Mouse.hpp>

namespace kT
{
    class Window;

    class KT_API WinMouse
    {
        public:

            ////////////////////////////////////////////////////////////
            /// \brief Check if a mouse button is pressed
            ///
            /// \param button Button to check
            ///
            /// \return True if the button is pressed, false otherwise
            ///
            ////////////////////////////////////////////////////////////
            static bool IsButtonPressed(Mouse::Button button);

            ////////////////////////////////////////////////////////////
            /// \brief Get the current position of the mouse in desktop coordinates
            ///
            /// This function returns the global position of the mouse
            /// cursor on the desktop.
            ///
            /// \return Current position of the mouse
            ///
            ////////////////////////////////////////////////////////////
            static Vector2i32 GetPosition();

            ////////////////////////////////////////////////////////////
            /// \brief Get the current position of the mouse in window coordinates
            ///
            /// This function returns the current position of the mouse
            /// cursor, relative to the given window.
            ///
            /// \param relativeTo Reference window
            ///
            /// \return Current position of the mouse
            ///
            ////////////////////////////////////////////////////////////
            static Vector2i32 GetPosition(const Window& relativeTo);

            ////////////////////////////////////////////////////////////
            /// \brief Set the current position of the mouse in desktop coordinates
            ///
            /// This function sets the global position of the mouse
            /// cursor on the desktop.
            ///
            /// \param position New position of the mouse
            ///
            ////////////////////////////////////////////////////////////
            static void SetPosition(const Vector2i32& position);

            ////////////////////////////////////////////////////////////
            /// \brief Set the current position of the mouse in window coordinates
            ///
            /// This function sets the current position of the mouse
            /// cursor, relative to the given window.
            ///
            /// \param position New position of the mouse
            /// \param relativeTo Reference window
            ///
            ////////////////////////////////////////////////////////////
            static void SetPosition(const Vector2i32& position, const Window& relativeTo);
    };
}
#endif /* __KT_WINMOUSE_HPP__ */
