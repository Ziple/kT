/**
 * \file Core/Exceptions.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/02/2009
 * \brief Contains the definitions of some classes to manage the exceptions.
 */
#ifndef __KTEXCEPTIONS_HPP__
#define __KTEXCEPTIONS_HPP__

#include "Build.hpp"

#include <exception>
#include <string>

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief Base class for exceptions.
     */
    class KT_API Exception: public std::exception
    {
        public:

            /**
             * \brief Default constructor.
             *
             * Doesn't build the full descritption of the launched exception.
             * The building of it must be done by the child.
             */
            Exception() throw() {}

            /**
             * \brief Full constructor.
             *
             * This constructor, unlike the default one, takes care of building a
             * description of the launched exception (with the provided arguments).
             */
            Exception( const std::string& description,
                         const std::string& source,
                         const std::string& file,
                         unsigned int line );

            /**
             * \brief Default destructor
             */
            virtual ~Exception() throw() {}

            /**
             * \brief Like standard std::exception::what()
             */
            virtual const std::string& What() const throw() {return myFullDescription; }

            /**
             * \brief To make it compatible whith std::exception
             */
            const char* what() const throw() {return myFullDescription.c_str(); }

        protected:

            std::string myFullDescription;

    };
}

/* Help launch exceptions*/
#define kTLaunchException( exceptionType, ... ) ( throw exceptionType ( __VA_ARGS__, __FUNCTION__, __FILE__, __LINE__ ) )

#endif /* __KTEXCEPTIONS_HPP__ */
