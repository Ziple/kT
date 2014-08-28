/**
 * \file Math/Size.hpp
 * \author Damien Hilloulin
 * \date 21/10/2008
 * \brief Contains the definition of the kT::Size< T > class.
 */
#ifndef __KTSIZE_HPP__
#define __KTSIZE_HPP__

#include "../Core/Types.hpp"
#include "../Core/Build.hpp"
#include "../Core/Compiler.hpp"

namespace kT
{
    /**
     * \ingroup ktmath_module
     * \brief Generic class for sizes.
     */
    template< typename T >
    struct KT_TEMPLATE_API Size
    {
        T Width; ///< Width
        T Height;///< Height
        T Depth; ///< Depth

        /**
         * \brief Default constructor.
         *
         * Initializes the variables to 0.
         */
        Size():
         Width( T(0) ),
         Height( T(0) ),
         Depth( T(0) )
        {
        }

        /**
         * \brief Detailed constructor.
         */
        Size( const T& width, const T& height, const T& depth  = T(0) ):
         Width( width ),
         Height( height ),
         Depth( depth )
        {
        }

        /**
         * \brief Copy constructor.
         */
        Size( const Size< T >& other ):
         Width( other.Width ),
         Height( other.Height ),
         Depth( other.Depth )
        {
        }
    };

    typedef Size< Uint16 > Sizeui16;
    typedef Size< Uint32 > Sizeui32;
    typedef Size< Int16 > Sizei16;
    typedef Size< Int32 > Sizei32;
    typedef Size< Float32 > Sizef32;
    typedef Size< Scalar > Sizesc;
}

#endif /* __KTSIZE_HPP__ */
