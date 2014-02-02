#ifndef __KT_X11KEYBOARD_HPP__
#define __KT_X11KEYBOARD_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Window/Keyboard.hpp>

namespace kT
{
    class KT_API X11Keyboard
    {
        public:

            static bool IsKeyPressed( Keyboard::Key code );
    };
}

#endif /* __KT_X11KEYBOARD_HPP__ */
