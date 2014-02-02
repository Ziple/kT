/**
 * \file Core/NonCopyable.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/02/2009
 * \brief Contains the definition of NonCopyable, class letting create non-copyable classes.
 */
#ifndef __KTNONCOPYABLE_HPP__
#define __KTNONCOPYABLE_HPP__

#include "Build.hpp"

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief Utility base class to easily declare non-copyable classes.
     *
     * Just inherit from NonCopyable to get a non-copyable class.
     */
    class KT_API NonCopyable
    {
        protected :

            /**
             * \brief Default constructor.
             *
             * The default constructor won't be generated, so we provide it.
             */
            NonCopyable() {}

        private :

            /**
             * \brief Copy constructor.
             *
             * Placed as private and not implemented so as it can't be used.
             */
            NonCopyable(const NonCopyable&);

            /**
             * \brief Copy operator.
             *
             * Placed as private and not implemented so as it can't be used.
             */
            NonCopyable& operator =(const NonCopyable&);
    };
}

#endif /* __KTNONCOPYABLE_HPP__ */
