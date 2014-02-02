#include <kT/Window/WindowManager.hpp>

#if defined(KT_WM_X11)

# include <kT/Window/X11/X11VideoMode.hpp>
# include <kT/Core/Logger.hpp>
# include <kT/Window/X11/X11Package.hpp>

# include <X11/Xlib.h>
# include <X11/extensions/Xrandr.h>

# include <algorithm>

namespace kT
{
    std::vector< X11VideoMode > X11VideoMode::ourSupportedModes;

    struct CompareModes
    {
        bool operator()(const X11VideoMode& first, const X11VideoMode& second)
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

    KT_API X11VideoMode::X11VideoMode():
     Width( 0 ),
     Height( 0 ),
     BitsPerPixel( 0 )
    {}

    KT_API X11VideoMode::X11VideoMode(Uint32 width, Uint32 height, Uint32 bitsPerPixel):
     Width( width ),
     Height( height ),
     BitsPerPixel( bitsPerPixel )
    {}

    X11VideoMode KT_API X11VideoMode::GetDesktopMode()
    {
        X11VideoMode DesktopMode;

        // Get the display and default screen from X11Package
        Display* Disp   = X11Package::GetDisplay();
        int      Screen = DefaultScreen( Disp );

        // Check if the XRandR extension is present
        int Version;
        if ( XQueryExtension( Disp, "RANDR", &Version, &Version, &Version ) )
        {
            // Get the current configuration
            XRRScreenConfiguration* Config = XRRGetScreenInfo( Disp, RootWindow(Disp, Screen) );
            if ( Config )
            {
                // Get the current video mode
                Rotation CurrentRotation;
                int CurrentMode = XRRConfigCurrentConfiguration( Config, &CurrentRotation );

                // Get the available screen sizes
                int NbSizes;
                XRRScreenSize* Sizes = XRRConfigSizes( Config, &NbSizes );
                if ( Sizes && (NbSizes > 0) )
                    DesktopMode = X11VideoMode( Sizes[CurrentMode].width, Sizes[CurrentMode].height, 32 );

                // Free the configuration instance
                XRRFreeScreenConfigInfo( Config );
            }
        }

        return DesktopMode;
    }

    Uint32 KT_API X11VideoMode::GetModesCount()
    {
        if( ourSupportedModes.empty() )
            Initialize();
        return ourSupportedModes.size();
    }

    X11VideoMode KT_API X11VideoMode::GetMode( Uint32 index )
    {
        if( ourSupportedModes.empty() )
            Initialize();
        return index < ourSupportedModes.size() ?
                    ourSupportedModes[index] : X11VideoMode();
    }

    bool KT_API X11VideoMode::SetDesktopMode( const X11VideoMode& requestedMode )
    {
        if ( !requestedMode.IsValid() )
            return false;

        Display* Disp   = X11Package::GetDisplay();
        Window Root     = DefaultRootWindow( Disp );

        // Check if the XRandR extension is present
        int Version;
        if ( XQueryExtension( Disp, "RANDR", &Version, &Version, &Version ) )
        {
            // Get the current configuration
            XRRScreenConfiguration* Config = XRRGetScreenInfo( Disp,
                                                               Root );
            if ( Config )
            {
                // Get the current rotation
                Rotation CurrentRotation;

                XRRConfigCurrentConfiguration( Config, &CurrentRotation );

                // Get the available screen sizes
                int NbSizes;
                XRRScreenSize* Sizes = XRRConfigSizes( Config, &NbSizes );
                if ( Sizes && (NbSizes > 0) )
                {
                    // Search a matching size
                    for (int i = 0; i < NbSizes; ++i)
                    {
                        if ( (Sizes[i].width == static_cast<int>(requestedMode.Width)) && (Sizes[i].height == static_cast<int>(requestedMode.Height)) )
                        {
                            // Switch to fullscreen mode
                            XRRSetScreenConfig( Disp, Config, Root, i, CurrentRotation, CurrentTime );
                            break;
                        }
                    }
                }

                // Free the configuration instance
                XRRFreeScreenConfigInfo( Config );
            }
        }

        return true;
    }

    bool KT_API X11VideoMode::IsValid() const
    {
        if( ourSupportedModes.empty() )
            Initialize();

        if ( std::find( ourSupportedModes.begin(), ourSupportedModes.end(), *this) == ourSupportedModes.end() )
            return false;
        return true;
    }

    bool KT_API X11VideoMode::operator==(const X11VideoMode& other) const
    {
        return ( Width == other.Width ) &&
               ( Height == other.Height ) &&
               ( BitsPerPixel == other.BitsPerPixel ) ? true : false;
    }

    bool KT_API X11VideoMode::operator!=(const X11VideoMode& other) const
    {
        return ( Width != other.Width ) ||
               ( Height != other.Height ) ||
               ( BitsPerPixel != other.BitsPerPixel ) ? true : false;
    }

    void X11VideoMode::Initialize()
    {
        // Get the display and screen from X11Package
        Display* Disp   = X11Package::GetDisplay();
        int      Screen = DefaultScreen( Disp );

        // Check if the XRandR extension is present
        int Version;
        if ( XQueryExtension( Disp, "RANDR", &Version, &Version, &Version ) )
        {
            // Get the current configuration
            XRRScreenConfiguration* Config = XRRGetScreenInfo( Disp, RootWindow(Disp, Screen) );
            if ( Config )
            {
                // Get the available screen sizes
                int NbSizes;
                XRRScreenSize* Sizes = XRRConfigSizes( Config, &NbSizes );
                if ( Sizes && (NbSizes > 0) )
                {
                    // Add them to the video modes array
                    for (int i = 0; i < NbSizes; ++i)
                    {
                        // Convert to sfVideoMode
                        X11VideoMode Mode(Sizes[i].width, Sizes[i].height, 32);

                        // Add it only if it is not already in the array
                        if ( std::find( ourSupportedModes.begin(), ourSupportedModes.end(), Mode) == ourSupportedModes.end() )
                            ourSupportedModes.push_back(Mode);
                    }
                }

                // Free the configuration instance
                XRRFreeScreenConfigInfo(Config);
            }
        }
    }
}

#endif
