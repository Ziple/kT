/**
 * \file Core/Time.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/02/2009
 * \brief Contains the definition of some utility fonctions about time.
 */
#ifndef __KTTIME_HPP__
#define __KTTIME_HPP__

#include "Types.hpp"

#if defined(KT_OS_WIN)
# include "Win/WinTime.hpp"
#elif defined(KT_OS_UNIX)
# include "Unix/UnixTime.hpp"
#endif

#endif /* __KTTIME_HPP__ */
