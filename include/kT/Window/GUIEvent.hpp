/**
 * \file Window/GUIEvent.hpp
 * \author Damien Hilloulin (ziple)
 * \date 21/03/2009
 * \brief Contains the definition of the windowing events.
 */
#ifndef __KTGUIEVENT_HPP__
#define __KTGUIEVENT_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>
#include <kT/Core/Event.hpp>

#include <kT/Window/Keyboard.hpp>
#include <kT/Window/Mouse.hpp>

namespace kT
{

    /**
     * \ingroup ktgui_module
     * \brief Struct for windowing events.
     */
	struct GUIEvent
    {
        /**
         * \ingroup ktgui_module
         * \brief Infos about a key pressed/release event.
         */
        struct KeyEvent
        {
            Keyboard::Key Code;///< Pressed/released key code.
            bool      Alt;    ///< Wether or not the Alt key is pressed.
            bool      Control;///< Wether or not the Ctrl key is pressed.
            bool      Shift;  ///< Wether or not the Shift key is pressed.
            bool      System;///< Wether or not the System key is pressed.
        };

        /**
         * \ingroup ktgui_module
         * \brief Text event info.
         */
        struct TextEvent
        {
            Uint16 Unicode;///< Contains the UTF-32 code of the entered character.
        };

        /**
         * \ingroup ktgui_module
         * \brief Mouse movement infos.
         */
        struct MouseMoveEvent
        {
            Uint32 X;///< New X (relative to the top left corner of the window).
            Uint32 Y;///< New Y (relative to the top left corner of the window).
        };

        /**
         * \ingroup ktgui_module
         * \brief Mouse button pression/release infos.
         */
        struct MouseButtonEvent
        {
            Mouse::Button Button;///< Contains the buttons that is pressed / released.
        };

        /**
         * \ingroup ktgui_module
         * \brief Mouse wheel movement infos.
         */
        struct MouseWheelEvent
        {
            /**
             * Contains the mouse wheel move (positive if forward, negative if backward).
             */
            Int32 Delta;
        };

        /**
         * \ingroup ktgui_module
         * \brief Contains the new width and Height of the resized element.
         */
        struct SizeEvent
        {
            Uint32 Width;
            Uint32 Height;
        };

        /**
         * \ingroup ktgui_module
         * \brief Enumeration of all the possible event types.
         */
        enum EventType
        {
            Closed,
            Resized,
            LostFocus,
            GainedFocus,
            TextEntered,
            KeyPressed,
            KeyReleased,
            MouseWheelMoved,
            MouseButtonPressed,
            MouseButtonReleased,
            MouseMoved
        };

        // Member data
        EventType Type;///< Type of event.

        union
        {
            KeyEvent         Key;
            TextEvent        Text;
            MouseMoveEvent   MouseMove;
            MouseButtonEvent MouseButton;
            MouseWheelEvent  MouseWheel;
            SizeEvent        Size;
        };
    };
}

#endif /* __KTGUIEVENT_HPP__ */
