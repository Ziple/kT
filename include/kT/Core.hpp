/**
 * \file Core.hpp
 * \author Damien Hilloulin (ziple)
 * \date 23/03/2009
 * \brief Includes all the headers of the core module.
 */
#ifndef __KTCORE_HPP__
#define __KTCORE_HPP__

/**
 * \defgroup ktcore_module Core module
 * \brief Core module.
 *
 * This module provides some headers to configure the engine during the
 * compilation, some helpers classes for file manipulation, logging, exceptions,
 * dynamic libraries management...
 */

#include "Core/Build.hpp"
#include "Core/Types.hpp"
#include "Core/Exceptions.hpp"

#include "Core/Logger.hpp"
#include "Core/FileLogger.hpp"

#include "Core/Library.hpp"

#include "Core/Time.hpp"
#include "Core/Clock.hpp"

#include "Core/Thread.hpp"
#include "Core/Mutex.hpp"
#include "Core/Semaphore.hpp"

#endif /* __KTCORE_HPP__ */
