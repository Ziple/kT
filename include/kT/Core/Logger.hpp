/**
 * \file Core/Logger.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/02/2009
 * \brief Contains the definition of the Logger class, abstract class for all loggers.
 */
#ifndef __KTLOGGER_HPP__
#define __KTLOGGER_HPP__

#include "Build.hpp"
#include "NonCopyable.hpp"

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief Base class for loggers.
     *
     */
    class KT_API Logger: public NonCopyable
    {
        public:

            /**
             * \brief Describes the type of the message.
             */
            enum MessageType{
                InfoMessage = 0,      ///< An informative message.
                WarningMessage,       ///< A warning message.
                ErrorMessage,         ///< A message due to an error.
                CriticalErrorMessage///< A message due to a critical error.
            };

            /**
             * \brief Virtual destructor.
             */
            virtual ~Logger() {}

            /**
             * \brief Logs a message.
             */
            virtual void Log( MessageType , const char* ) = 0;
    };
}

#endif /* __KTLOGGER_HPP__ */
