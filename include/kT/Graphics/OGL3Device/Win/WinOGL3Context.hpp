/**
 * \file OGL3Device/Win/WinOGL3Context.hpp
 * \author Damien Hilloulin (ziple)
 * \date 16/04/2009
 */
#ifndef __KTWINOGL3CONTEXT_HPP__
#define __KTWINOGL3CONTEXT_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>
#include <kT/Graphics/OGL3Device/OGL.hpp>

typedef struct HGLRC__ *HGLRC;
typedef struct HDC__ *HDC;

namespace kT
{
    // forward declarations
    class Window;

    /**
     * \ingroup ktogl3device_module
     * \brief Implementation of the OGL3Context for Windows.
     */
    class KT_API WinOGL3Context
    {
        public:

            /**
             * \brief Constructor.
             */
            WinOGL3Context( Window* Window = 0,
                               WinOGL3Context* sharedWith = 0,
                               unsigned redBits = 8,
                               unsigned greenBits = 8,
                               unsigned blueBits = 8,
                               unsigned alhaBits = 0,
                               unsigned depth = 0,
                               unsigned stencil = 0 );

            /**
             * \brief Destructor.
             */
            ~WinOGL3Context();

            /**
             * \brief Returns the handle to the context (HGLRC).
             */
            inline HGLRC GetHandle() const{return myOGLContext;}

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

            HGLRC myOGLContext; ///< The OGL context.
            HDC myDC;           ///< The DeviceContext for the window.
            Window* myWindow;///< The attached window.
    };
}
#endif /* __KTWINOGL3CONTEXT_HPP__ */
