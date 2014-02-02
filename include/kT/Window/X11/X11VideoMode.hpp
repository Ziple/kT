/**
 * \file Window/X11/X11VideoMode.hpp
 * \author Damien Hilloulin (ziple)
 * \date 23/02/2009
 * \brief Contains the implementation of the VideoMode class for X11.
 */
#ifndef __KTX11VIDEOMODE_HPP__
#define __KTX11VIDEOMODE_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>

#include <vector>

namespace kT
{
    /**
     * \ingroup ktgui_module
     * \brief The class providing VideoMode implementation on windows.
     */
    class KT_API X11VideoMode
    {
        public:

            /**
             * \brief Default constructor.
             */
            X11VideoMode();

            /**
             * \brief Detailed constructor.
             */
            X11VideoMode( Uint32 width, Uint32 height, Uint32 bitsPerPixel );

            /**
             * \brief Returns the desktop video mode.
             */
            static X11VideoMode GetDesktopMode();

            /**
             * \brief Returns the number of supported modes.
             */
            static Uint32 GetModesCount();

            /**
             * \brief Return sthe specified mode.
             *
             * Must be in range of [0, GetModesCount()[.
             */
            static X11VideoMode GetMode( Uint32 index );

            /**
             * \brief Changes the desktop mode to the specified one.
             */
            static bool SetDesktopMode( const X11VideoMode& mode );

            /**
             * \brief Tells wether or not the mode is supported.
             */
            bool IsValid() const;

            /**
             * \brief Is-equal operator.
             */
            bool operator==( const X11VideoMode& other ) const;

            /**
             * \brief Is-different operator.
             */
            bool operator!=( const X11VideoMode& other ) const;

            Uint32 Width, Height, BitsPerPixel;

            /**
             * \brief Fills the array of the supported modes.
             */
            static void Initialize();

        private:

            /**
             * \brief Array of the supported modes.
             */
            static std::vector< X11VideoMode > ourSupportedModes;
    };
}

#endif /* __KTX11VIDEOMODE_HPP__ */
