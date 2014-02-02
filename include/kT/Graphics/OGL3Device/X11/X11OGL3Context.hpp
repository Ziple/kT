/**
 * \file OGL3Device/X11/X11OGL3Context.hpp
 * \author Damien Hilloulin (ziple)
 * \date 19/04/2009
 */
#ifndef __KTX11OGL3CONTEXT_HPP__
#define __KTX11OGL3CONTEXT_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>
#include <kT/Graphics/OGL3Device/OGL.hpp>

typedef struct __GLXcontextRec *GLXContext;

namespace kT
{
    // forward declarations
    class Window;

    /**
     * \ingroup ktogl3device_module
     * \brief Implementation of the OGL3Context for X11.
     */
    class KT_API X11OGL3Context
    {
        public:

            /**
             * \brief Constructor.
             */
            X11OGL3Context( Window* Window = 0,
                               X11OGL3Context* sharedWith = 0,
                               unsigned redBits = 8,
                               unsigned greenBits = 8,
                               unsigned blueBits = 8,
                               unsigned alphaBits = 0,
                               unsigned depth = 0,
                               unsigned stencil = 0 );

            /**
             * \brief Destructor.
             */
            ~X11OGL3Context();

            /**
             * \brief Returns the handle to the context (GLXContext).
             */
            inline GLXContext GetHandle() const{return myOGLContext;}

            /**
             * \brief Returns a pointer to the fonction.
             * \return NULL if not successful.
             */
            FunctionPointer GetProcAddress( const char* procName );

            /**
             * \brief Enables/disables the framerate limitation.
             */
            void LimitFramerate( bool limit = true );

            /**
             * \brief Tells if the context is currently attached to this thread.
             */
            bool IsCurrent() const;

            /**
             * \brief Attachs the context to the thread.
             */
            void MakeCurrent();

            /**
             * \brief Swaps the buffers of the window.
             */
            void SwapBuffers();

            /**
             * \brief Returns the attached window.
             */
            inline Window* GetAttachedWindow() const{return myWindow;}

        private:

            GLXContext myOGLContext;///< OGL context.
            Window* myWindow;///< The attached window.
    };
}

#endif /* __KTX11OGL3CONTEXT_HPP__ */
