/**
 * \file Graphics/OGL3Device/OGL3Check.hpp
 * \author Damien Hilloulin (ziple)
 * \date 03/03/2009
 */
#ifndef __KTOGL3CHECK_HPP__
#define __KTOGL3CHECK_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>

namespace kT
{
    /**
     * \ingroup ktogl3renderer_module
     * \brief Checks for OpenGL errors and los it.
     */
    void KT_API _OGL3CheckError( const Int8* fonction, const Int8* file, Uint32 line );
}

#ifdef KT_DEBUG
 #define ktOGL3Check( a ) ( kT::_OGL3CheckError( #a, __FILE__, __LINE__ ), (a))
#else
 #define ktOGL3Check( a ) (a)
#endif

#endif /* __KTOGL3CHECK_HPP__ */
