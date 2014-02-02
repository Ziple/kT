/**
 * \file Core/FileLogger.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/02/2009
 * \brief Contains the definition of the kT::FileLogger class, used to log messages in a file.
 */
#ifndef __KTFILELOGGER_HPP__
#define __KTFILELOGGER_HPP__

#include "Build.hpp"
#include "Logger.hpp"

#include <string>
#include <fstream>

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief A class for logging into files.
     */
    class KT_API FileLogger: public Logger
    {

        public:

            /**
             * \brief Default detailed constructor.
             * \param file File to log in.
             */
            FileLogger( const std::string& file = "kT.log" );

            /**
             * \brief Default destructor.
             */
            ~FileLogger();

            /**
             * \brief Write method to log in file.
             */
            void Log( MessageType , const char* );

        private:

            std::ofstream outputFile;///< Output file.
    };
}

#endif /* __KTFILELOGGER_HPP__ */
