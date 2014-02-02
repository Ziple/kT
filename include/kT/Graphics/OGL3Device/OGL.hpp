/**
 * \file Graphics/OGL3Device/OGL.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/02/2009
 */
#ifndef __KTOGL_HPP__
#define __KTOGL_HPP__

#include <kT/Window/WindowManager.hpp>

#include <GL/glew.h>

#if defined KT_WM_WIN
# include <GL/wglew.h>
#elif defined KT_WM_X11
# include <GL/glxew.h>
#endif

#endif /* __KTOGL_HPP__ */
