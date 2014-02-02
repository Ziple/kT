/**
 * \file Core/File.hpp
 * \author Damien Hilloulin (ziple)
 * \date 22/02/2009
 * \brief Contains the definition of the File class, used for files handling.
 */
#ifndef __KTFILE_HPP__
#define __KTFILE_HPP__

#include "Build.hpp"
#include "Types.hpp"
#include "NonCopyable.hpp"
#include "Exceptions.hpp"

#include <string>

namespace kT
{

    /**
     * \ingroup ktcore_module
     * \brief Class for files.
     *
     * Cette classe fournit des fonctions pour permettre d'écrire/lire dans des
     * fichiers, tester l'existence de ceux-ci, les renommer, supprimer etc...
     * Provides some fonctions to read from, write into, test the existence of
     * ,rename, remove files.
     */
    class KT_API File: public NonCopyable
    {
        public:

            /**
             * \brief Different opening mode flags available.
             *
             * These ones can be ORded.
             */
            enum OpeningFlag
            {
                ReadFlag = 1, ///< Opens for reading.
                WriteFlag = 2,///< Opens for writing (and place the cursor at the beginnning).
                AppendFlag = 4///< Opens in appenning mode (writing at the end).
            };

            /**
             * \brief Position referential.
             */
            enum PositionReferential
            {
	            FileBegin = 0,///< The referential is the beginning of the file.
	            FileEnd = 1,  ///< The referential is the end of the file.
	            FileCur = 2   ///< The referential is the current position of the cursor.
            };

		    /**
		     * \brief Tests wether or not the file exists.
		     * \return true if the file exists, false otherwise.
		     */
            static bool Exist( const std::string& filename );

		    /**
		     * \brief Gets the size of the file.
		     * \return size of the file if exists in bytes, 0 otherwise.
		     */
            static Uint32 GetSize( const std::string& filename );

            /**
             * \brife Reads the whole content of the file.
             * \return A buffer with the content of the file if successfull, NULL otherwise. The size is in read.
             */
            static Uint8* RawContent( const std::string& filename, Uint32* read );

		    /**
		     * \brief Rename the file named "oldName" to "newName".
		     * \return true if successful, false otherwise.
		     */
            static bool Rename( const std::string& oldName, const std::string& newName );

		    /**
		     * \brief Removes the file.
		     * \return true if successful, false otherwise.
		     */
            static bool Remove( const std::string& filename);

		    /**
		     * \brief Default constructor.
             *
             * Doesn't load any file.
		     */
            inline File(): myFile( 0 ){}

		    /**
		     * \brief Detailed constructor.
             *
             * Launch an exception if the opening of the specified file with the
             * specified opening mode failed.
		     */
            File( const std::string& filename, Uint32 openingMode = ReadFlag );

		    /**
		     * \brief Copy constructor.
             *
             * Never implemented to make the class non-copyable.
		     */
		    File( const File& other );

		    /**
		     * \brief Destructor.
             *
             * Close the file if opened.
		     */
            ~File();

		    /**
		     * \brief Tries to open the file with the specified opening mode.
		     * \return true if successful, false otherwise.
		     */
            bool Open( const std::string& filename, Uint32 openingMode = ReadFlag );

		    /**
		     * \brief Closes the file.
		     */
            void Close();

		    /**
		     * \brief Tells if the file is opened.
		     * \return true if the file is opened, false otherwise.
		     */
            inline bool IsOpened() const {return myFile ? true : false;}

		    /**
		     * \brief Gets the name of the file.
		     * \return the complete name of the file with the path.
		     */
		    const Uint8* Name() const {return reinterpret_cast<const Uint8*>( myName.c_str() );}

		    /**
		     * \brief Gets the position of the cursor.
		     * \return The position of the cursor or -1 if an error occurs.
		     */
		    Int32 Tell() const;

		    /**
		     * \brief Positions the cursor.
		     */
		    void Seek( PositionReferential origin, Int32 offset );

            /**
		     * \brief Gets the size of the file.
		     * \return size of the file in bytes.
		     */
            Uint32 GetSize();

		    /**
             * \brief Writes into the file from the buffer nbElements of elementsSize size each.
		     * \return the size of the written data.
		     */
            Uint32 Write( void* buffer, Uint32 elementsSize, Uint32 nbElements );

            /**
             * \brief Reads from the file (at the current pos) nbElements of elementsSize size each and writes it in the buffer.
             * \return the size of read data.
             */
            Uint32 Read( void* buffer, Uint32 elementsSize, Uint32 nbElements );

            /**
             * \brief Reads the whole file and writes the content in buffer.
             * Buffer must be big enough (read the size with GetSize() first!) 
             */
            void RawContent( Uint8* buffer );

        private:

            void* myFile;           ///< Handle.
		    std::string myName;     ///< File name.
            Uint32 myOpeningMode;///< Opening mode (a combination of opening mode flags).
    };

}

#endif /* __KTFILE_HPP__ */
