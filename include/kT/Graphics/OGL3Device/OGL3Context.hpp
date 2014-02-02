/**
 * \file Graphics/OGL3Device/OGL3Context.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/02/2009
 */
#ifndef __KTOGL3CONTEXT_HPP__
#define __KTOGL3CONTEXT_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Window/WindowManager.hpp>

#if defined(KT_WM_WIN)
# include "Win/WinOGL3Context.hpp"
# define OGL3ContextImpl WinOGL3Context
#elif defined(KT_WM_X11)
# include "X11/X11OGL3Context.hpp"
# define OGL3ContextImpl X11OGL3Context
#endif

namespace kT
{
    class Window;

    /**
     * \ingroup ktogl3device_module
     * \brief Class managing an OGL context.
     */
    class KT_API OGL3Context: public OGL3ContextImpl
    {
        public:

            /**
             * \brief Constructor.
             *
             * Make the context current too.
             */
            OGL3Context( Window* window = 0,
                            OGL3Context* sharedWith = 0,
                            unsigned redBits = 8,
                            unsigned greenBits = 8,
                            unsigned blueBits = 8,
                            unsigned alphaBits = 0,
                            unsigned depth = 0,
                            unsigned stencil = 0  );

            /**
             * \brief Tells wether or not an extension is present.
             */
            bool IsExtensionPresent( const char* extensionName ) const;
    };
}
#endif /* __KTOGL3CONTEXT_HPP__ */
