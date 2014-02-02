/**
 * \file Window/Window.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/03/2009
 * \brief Contains the definition of the Window class.
 */
#ifndef __KTWINDOW_HPP__
#define __KTWINDOW_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Math/Size.hpp>
#include "WindowManager.hpp"

#if defined(KT_WM_WIN)
# include "Win/WinWindow.hpp"
#elif defined(KT_WM_X11)
# include "X11/X11Window.hpp"
#endif

#endif /* __KTWINDOW_HPP__ */
