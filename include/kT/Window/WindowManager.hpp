/**
 * \file Window/WindowManager.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/03/2009
 * \brief Detects the window manager of the system.
 */
#ifndef __KTWINDOWMANAGER_HPP__
#define __KTWINDOWMANAGER_HPP__

#include <kT/Core/Build.hpp>

#if defined(KT_OS_LINUX)
# define KT_WM_X11
#elif defined(KT_OS_WIN)
# define KT_WM_WIN
#elif defined(KT_OS_MACOS)
# define KT_WM_MACOS
#endif

#endif /* __KTWINDOWMANAGER_HPP__ */
