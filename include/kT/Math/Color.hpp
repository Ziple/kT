/**
 * \file Math/Color.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/02/2009
 * \brief Holds the definition of the very basic kT::Color struct.
 */
#ifndef __KTCOLOR_HPP__
#define __KTCOLOR_HPP__

#include <kT/Core/Types.hpp>

namespace kT
{
    /**
     * \ingroup ktmath_module
     * \brief A generic class to represents colors.
     *
     * This structure, as it's a generic one, let you specify the type of the components
     * and, moreover, gives you some functions to convert from a format to another
     * one.
     */
    template< typename T >
    struct Color
    {
        /**
         * \brief Default Constructor.
         *
         * Initialize each component to 0.
         */
        Color();

        /**
         * \brief Constructor from specified comonents.
         *
         * Intitialize each components with the corresponding specified one.
         */
        Color( const T& r_, const T& g_, const T& b_, const T& a_ );

        /**
         * \brief Constructor from an array of components.
         *
         * The array must composed of four elements, each one representing
         * respectively the r, g, b, a ones.
         */
        Color( const T* components );

        /**
         * \brief Copy constructor.
         */
        Color( const Color< T >& other );

        T r, g, b, a;///< Color's components.
    };

    typedef Color< Uint16 > Colorui16;
    typedef Color< Uint32 > Colorui32;
    typedef Color< Float32 > Colorf32;
}

#include "Color.inl"

#endif /* __KTCOLOR_HPP__ */
