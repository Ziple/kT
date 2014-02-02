/**
 * \file Window/VideoMode.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/03/2009
 * \brief Contains the definition of the VideoMode class.
 */
#ifndef __KTVIDEOMODE_HPP__
#define __KTVIDEOMODE_HPP__

#include <kT/Core/Types.hpp>

#include "WindowManager.hpp"

#if defined(KT_WM_WIN)
# include "Win/WinVideoMode.hpp"
# define VideoModeImpl WinVideoMode
#elif defined(KT_WM_X11)
# include "X11/X11VideoMode.hpp"
# define VideoModeImpl X11VideoMode
#endif

#include <kT/Math/Size.hpp>

namespace kT
{
    /**
     * \ingroup ktgui_module
     * \brief Class to list, test and set video modes.
     *
     * Don't forget to change the video mode to the user's one at the end if
     * you have switched it (it's not assured on X11).
     */
    class VideoMode: public VideoModeImpl
    {
        public:

            /**
             * \brief Default constructor.
             */
            inline VideoMode() {}

            /**
             * \brief Detailed constructor.
             */
            inline VideoMode( Uint32 width, Uint32 height, Uint32 bitsPerPixel ):
             VideoModeImpl( width, height, bitsPerPixel )
            {}

            /**
             * \brief Copy constructor.
             */
            inline VideoMode( const VideoModeImpl& o ):
             VideoModeImpl( o.Width, o.Height, o.BitsPerPixel )
            {}

			 kT::Sizeui32 GetSize() const { return kT::Sizeui32( Width, Height, BitsPerPixel ); }

            /**
             * \brief Equal operator.
             */
            VideoMode& operator=( const VideoModeImpl& o )
            {
                Width = o.Width;
                Height = o.Height;
                BitsPerPixel = o.BitsPerPixel;
                return *this;
            }
    };
}
#endif /* __KTVIDEOMODE_HPP__ */
