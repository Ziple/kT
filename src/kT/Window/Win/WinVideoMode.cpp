#include <kT/Window/WindowManager.hpp>

#if defined(KT_WM_WIN)

# include <kT/Window/Win/WinVideoMode.hpp>
# include <kT/Core/Logger.hpp>

# include <windows.h>

# include <algorithm>

namespace kT
{
    std::vector< WinVideoMode > WinVideoMode::ourSupportedModes;

    struct CompareModes
    {
        bool operator()(const WinVideoMode& first, const WinVideoMode& second)
        {
            if (first.BitsPerPixel > second.BitsPerPixel)
                    return true;
                else if (first.BitsPerPixel < second.BitsPerPixel)
                    return false;
                else if (first.Width > second.Width)
                    return true;
                else if (first.Width < second.Width)
                    return false;
                else
                    return (first.Height > second.Height);
        }
    };

    KT_API WinVideoMode::WinVideoMode():
     Width( 0 ),
     Height( 0 ),
     BitsPerPixel( 0 )
    {}

    KT_API WinVideoMode::WinVideoMode(Uint32 width, Uint32 height, Uint32 bitsPerPixel):
     Width( width ),
     Height( height ),
     BitsPerPixel( bitsPerPixel )
    {}

    WinVideoMode KT_API WinVideoMode::GetDesktopMode()
    {
        DEVMODE Win32Mode;
        Win32Mode.dmSize = sizeof(DEVMODE);
        EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &Win32Mode);

        return WinVideoMode(Win32Mode.dmPelsWidth, Win32Mode.dmPelsHeight, Win32Mode.dmBitsPerPel);
    }

    Uint32 KT_API WinVideoMode::GetModesCount()
    {
        if( ourSupportedModes.empty() )
            Initialize();
        return ourSupportedModes.size();
    }

    WinVideoMode KT_API WinVideoMode::GetMode( Uint32 index )
    {
        if( ourSupportedModes.empty() )
            Initialize();
        return index < ourSupportedModes.size() ?
                    ourSupportedModes[index] : WinVideoMode();
    }

    bool KT_API WinVideoMode::SetDesktopMode(const WinVideoMode& requestedMode)
    {
        if ( !requestedMode.IsValid() )
            return false;

        DEVMODE dmScreenSettings;
        dmScreenSettings.dmSize = sizeof(dmScreenSettings);
        dmScreenSettings.dmPelsWidth = requestedMode.Width;
        dmScreenSettings.dmPelsHeight = requestedMode.Height;
        dmScreenSettings.dmBitsPerPel = requestedMode.BitsPerPixel;
        dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        if ( ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN ) == DISP_CHANGE_SUCCESSFUL )
            return true;
        return false;
    }

    bool KT_API WinVideoMode::IsValid() const
    {
        if( ourSupportedModes.empty() )
            Initialize();

        if ( std::find( ourSupportedModes.begin(), ourSupportedModes.end(), *this) == ourSupportedModes.end() )
            return false;
        return true;
    }

    bool KT_API WinVideoMode::operator==(const WinVideoMode& other) const
    {
        return ( Width == other.Width ) &&
               ( Height == other.Height ) &&
               ( BitsPerPixel == other.BitsPerPixel ) ? true : false;
    }

    bool KT_API WinVideoMode::operator!=(const WinVideoMode& other) const
    {
        return ( Width != other.Width ) ||
               ( Height != other.Height ) ||
               ( BitsPerPixel != other.BitsPerPixel ) ? true : false;
    }


    void KT_API WinVideoMode::Initialize()
    {
        DEVMODE Win32Mode;
        Win32Mode.dmSize = sizeof(DEVMODE);
        for (int Count = 0; EnumDisplaySettings(NULL, Count, &Win32Mode); ++Count)
        {
            WinVideoMode Mode(Win32Mode.dmPelsWidth, Win32Mode.dmPelsHeight, Win32Mode.dmBitsPerPel);

            if ( std::find( ourSupportedModes.begin(), ourSupportedModes.end(), Mode) == ourSupportedModes.end() )
                ourSupportedModes.push_back(Mode);
        }

        std::sort( ourSupportedModes.begin(), ourSupportedModes.end(), CompareModes() );
    }
}
#endif
