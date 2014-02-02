#ifndef __KT_MOUSE_HPP__
#define __KT_MOUSE_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Math/Vector2.hpp>

namespace kT
{
    class Window;

    ////////////////////////////////////////////////////////////
    /// \brief Give access to the real-time state of the mouse
    ///
    ////////////////////////////////////////////////////////////
    class KT_API Mouse
    {
        public :

            ////////////////////////////////////////////////////////////
            /// \brief Mouse buttons
            ///
            ////////////////////////////////////////////////////////////
            enum Button
            {
                Left,       ///< The left mouse button
                Right,      ///< The right mouse button
                Middle,     ///< The middle (wheel) mouse button
                XButton1,   ///< The first extra mouse button
                XButton2,   ///< The second extra mouse button

                ButtonCount ///< Keep last -- the total number of mouse buttons
            };

            ////////////////////////////////////////////////////////////
            /// \brief Check if a mouse button is pressed
            ///
            /// \param button Button to check
            ///
            /// \return True if the button is pressed, false otherwise
            ///
            ////////////////////////////////////////////////////////////
            static bool IsButtonPressed(Button button);

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

#endif /* __KT_MOUSE_HPP__ */