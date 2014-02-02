/**
 * \file Window/X11/X11Package.hpp
 * \author Damien Hilloulin (ziple)
 * \date 21/03/2009
 * \brief Contains what must be kept on X11.
 */
#ifndef __KTX11PACKAGE_HPP__
#define __KTX11PACKAGE_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>

typedef struct _XDisplay Display;
typedef struct _XIM *XIM;

namespace kT
{
    /**
     * \ingroup ktgui_module
     * \brief Utility class to manages some X11 relative stuff.
     */
    class KT_API X11Package
    {
        public:

            static Display* ourDisplay;
            static int ourScreen;
            static unsigned long ourRootWindow;
            static XIM ourInputMethod;

            static Display* GetDisplay();

        protected:

            static Uint32 ourCount;

            X11Package();

            ~X11Package();
    };
}

#endif /* __KTX11PACKAGE_HPP__ */
