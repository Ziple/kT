#ifndef __KT_WINKEYBOARD_HPP__
#define __KT_WINKEYBOARD_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Window/Keyboard.hpp>

namespace kT
{
    class KT_API WinKeyboard
    {
        public:

            static bool IsKeyPressed( Keyboard::Key code );
    };
}

#endif /**/