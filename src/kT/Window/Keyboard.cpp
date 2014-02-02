#include <kT/Window/Keyboard.hpp>

#include <kT/Window/WindowManager.hpp>

#if defined(KT_WM_WIN)
# include <kT/Window/Win/WinKeyboard.hpp>
# define KeyboardImpl WinKeyboard
#elif defined(KT_WM_X11)
# include <kT/Window/X11/X11Keyboard.hpp>
# define KeyboardImpl X11Keyboard
#endif

namespace kT
{
    bool KT_API Keyboard::IsKeyPressed( Keyboard::Key code )
    {
        return KeyboardImpl::IsKeyPressed( code );
    }
}