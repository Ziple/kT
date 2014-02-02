#ifndef __KTUNIXLIBRARY_HPP__
#define __KTUNIXLIBRARY_HPP__

#include "../Build.hpp"
#include "../NonCopyable.hpp"

namespace kT
{
    /**
     * \ingroup ktcore_module
     * \brief Implementation of dynamic libraries management class under unix.
     */
    class KT_API UnixLibrary: public NonCopyable
    {
        public:

            /**
             * \brief Default constructor.
             */
            UnixLibrary();

            /**
             * \brief Default destructor.
             */
            ~UnixLibrary();

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

            void* myLibraryModule;///< Handle to the library module.
            bool myIsLoaded;      ///< Wether or not the library is loaded.
    };
}

#endif/* __KTUNIXLIBRARY_HPP__ */
