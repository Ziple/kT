/**
 * \file Window/Win/WinVideoMode.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/03/2009
 * \brief Contains the implementation of the VideoMode class for windows.
 */
#ifndef __KTWINVIDEOMODE_HPP__
#define __KTWINVIDEOMODE_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>

#include <vector>

namespace kT
{
    /**
     * \ingroup ktgui_module
     * \brief The class providing VideoMode implementation on windows.
     */
    class KT_API WinVideoMode
    {
        public:

            /**
             * \brief Default constructor.
             */
            WinVideoMode();

            /**
             * \brief Detailed constructor.
             */
            WinVideoMode( Uint32 width, Uint32 height, Uint32 bitsPerPixel );

            /**
             * \brief Returns the desktop video mode.
             */
            static WinVideoMode GetDesktopMode();

            /**
             * \brief Returns the number of supported modes.
             */
            static Uint32 GetModesCount();

            /**
             * \brief Return sthe specified mode.
             *
             * Must be in range of [0, GetModesCount()[.
             */
            static WinVideoMode GetMode( Uint32 index );

            /**
             * \brief Changes the desktop mode to the specified one.
             */
            static bool SetDesktopMode( const WinVideoMode& mode );

            /**
             * \brief Tells wether or not the mode is supported.
             */
            bool IsValid() const;

            /**
             * \brief Is-equal operator.
             */
            bool operator==( const WinVideoMode& other ) const;

            /**
             * \brief Is-different operator.
             */
            bool operator!=( const WinVideoMode& other ) const;

            Uint32 Width, Height, BitsPerPixel;

            /**
             * \brief Fills the array of the supported modes.
             */
            static void Initialize();

        private:

            /**
             * \brief Array of the supported modes.
             */
            static std::vector< WinVideoMode > ourSupportedModes;
    };
}

#endif /* __KTWINVIDEOMODE_HPP__ */
