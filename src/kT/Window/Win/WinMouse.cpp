#include <kT/Window/WindowManager.hpp>

#if defined(KT_WM_WIN)
# include <kT/Window/Win/WinMouse.hpp>
# include <kT/Window/Window.hpp>
# include <windows.h>

namespace kT
{
    ////////////////////////////////////////////////////////////
    bool KT_API WinMouse::IsButtonPressed(Mouse::Button button)
    {
        int vkey = 0;
        switch (button)
        {
            case Mouse::Left:     vkey = GetSystemMetrics(SM_SWAPBUTTON) ? VK_RBUTTON : VK_LBUTTON; break;
            case Mouse::Right:    vkey = GetSystemMetrics(SM_SWAPBUTTON) ? VK_LBUTTON : VK_RBUTTON; break;
            case Mouse::Middle:   vkey = VK_MBUTTON;  break;
            case Mouse::XButton1: vkey = VK_XBUTTON1; break;
            case Mouse::XButton2: vkey = VK_XBUTTON2; break;
            default:              vkey = 0;           break;
        }

        return (GetAsyncKeyState(vkey) & 0x8000) != 0;
    }


    ////////////////////////////////////////////////////////////
    Vector2i32 KT_API WinMouse::GetPosition()
    {
        POINT point;
        GetCursorPos(&point);
        return Vector2i32(point.x, point.y);
    }


    ////////////////////////////////////////////////////////////
    Vector2i32 KT_API WinMouse::GetPosition(const Window& relativeTo)
    {
        WindowHandle handle = relativeTo.GetWindowHandle();
        if (handle)
        {
            POINT point;
            GetCursorPos(&point);
            ScreenToClient(handle, &point);
            return Vector2i32(point.x, point.y);
        }
        else
        {
            return Vector2i32();
        }
    }


    ////////////////////////////////////////////////////////////
    void KT_API WinMouse::SetPosition(const Vector2i32& position)
    {
        SetCursorPos(position.x, position.y);
    }


    ////////////////////////////////////////////////////////////
    void KT_API WinMouse::SetPosition(const Vector2i32& position, const Window& relativeTo)
    {
        WindowHandle handle = relativeTo.GetWindowHandle();
        if (handle)
        {
            POINT point = {position.x, position.y};
            ClientToScreen(handle, &point);
            SetCursorPos(point.x, point.y);
        }
    }
}
#endif