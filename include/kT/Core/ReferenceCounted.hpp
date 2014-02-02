/**
 * \file Core/ReferenceCounted.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/02/2009
 * \brief Contains the definition of the ReferenceCounted class.
 */
#ifndef __KTREFERENCECOUNTED_HPP__
#define __KTREFERENCECOUNTED_HPP__

#include "Types.hpp"

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief Utility base class to easily declare reference-counted classes.
     *
     * An object descending from this class gets a reference counter (which is
     * initialized to 1 in the constructor) and can be incremented to mark the
     * addition of a reference or decremented when a reference to the object is
     * dropped.
     * The object is deleted when the counter gets to 0.
     */
    template< typename T>
    class ReferenceCounted
    {
        public:

            /**
             * \brief Default constructor.
             */
            ReferenceCounted():
             myCounter( 1 )
            {}

            /**
             * \brief Increments the internal counter.
             */
            void AddRef() const
            {
                ++myCounter;
            }

            /**
             * \brief Decrements the internal counter.
             */
            void Release() const
            {
                --myCounter;

                if( !myCounter )
                    delete static_cast<const T*>( this );
            }

        private:

            mutable Uint32 myCounter;///< Internal counter.
    };
}

#endif /* __KTREFERENCECOUNTED_HPP__ */
