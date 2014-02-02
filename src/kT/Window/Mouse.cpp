#include <kT/Window/Mouse.hpp>
#include <kT/Window/WindowManager.hpp>

#if defined(KT_WM_WIN)
# include <kT/Window/Win/WinMouse.hpp>
# define MouseImpl WinMouse
#elif defined(KT_WM_X11)
# include <kT/Window/X11/X11Mouse.hpp>
# define MouseImpl X11Mouse
#endif 

namespace kT
{
    ////////////////////////////////////////////////////////////
    bool KT_API Mouse::IsButtonPressed(Mouse::Button button)
    {
        return MouseImpl::IsButtonPressed(button);
    }


    ////////////////////////////////////////////////////////////
    Vector2i32 KT_API Mouse::GetPosition()
    {
        return MouseImpl::GetPosition();
    }


    ////////////////////////////////////////////////////////////
    Vector2i32 KT_API Mouse::GetPosition(const Window& relativeTo)
    {
        return MouseImpl::GetPosition(relativeTo);
    }


    ////////////////////////////////////////////////////////////
    void KT_API Mouse::SetPosition(const Vector2i32& position)
    {
        MouseImpl::SetPosition(position);
    }


    ////////////////////////////////////////////////////////////
    void KT_API Mouse::SetPosition(const Vector2i32& position, const Window& relativeTo)
    {
        MouseImpl::SetPosition(position, relativeTo);
    }
}