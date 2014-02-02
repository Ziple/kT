/**
 * \file Graphics/TGAImageHandler.hpp
 * \author Damien Hilloulin (ziple)
 * \date 08/08/2011
 * \brief Contains the definition of kT::TGAImageHandler providing targa image loading support.
 */
#ifndef __KTTGAIMAGEHANDLER_HPP__
#define __KTTGAIMAGEHANDLER_HPP__

#include <string>

namespace kT
{
    class Image;

    /**
     * \brief Little class to handle Targa image handling.
     */
    class TGAImageHandler
    {
        public:

            /**
             * \brief Loads a targa image from file.
             * \return A pointer to the image if successfully loaded or NULL otherwise.
             */
            static Image* LoadFromFile(
				const std::string& filename
				);
    };
}

#endif /* __KTTGAIMAGEHANDLER_HPP__ */
