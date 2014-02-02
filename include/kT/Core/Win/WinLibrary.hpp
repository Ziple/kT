#ifndef __KTWINLIBRARY_HPP__
#define __KTWINLIBRARY_HPP__

#include "../Build.hpp"
#include "../NonCopyable.hpp"

#include <windows.h>

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief Implementation of dynamic libraries management class under windows.
     */
    class KT_API WinLibrary: public NonCopyable
    {
        public:

            /**
             * \brief Default constructor.
             */
            WinLibrary();

            /**
             * \brief Default destructor.
             */
            ~WinLibrary();

            /**
             * \brief Loads the specified library.
             * \param filename Name of the library to load.
             * \return true if successful, false otherwise.
             */
            bool Load(const char* filename);

            /**
             * \brief Unloads the library.
             */
            void Unload();

            /**
             * \brief Returns a pointer to the symbol.
             */
            void* GetProcAddress(const char* symbol);

            /**
             * \brief Tells if the library is loaded.
             */
            bool IsLoaded() const;

        private:

            HMODULE myLibraryModule;///< Handle to the library module.
            bool myIsLoaded;        ///< Wether or not the library is loaded.
    };
}

#endif /* __KTWINLIBRARY_HPP__ */
