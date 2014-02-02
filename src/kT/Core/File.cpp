#include <kT/Core/File.hpp>

#include <cstdio>
#include <string>

namespace kT
{
    bool KT_API File::Exist( const std::string& filename )
    {
        FILE* f = 0;
        f = fopen( filename.c_str(), "rb" );
        if ( f )
            fclose( f );
        return f ? true : false;
    }

    Uint32 KT_API File::GetSize( const std::string& filename )
    {
        return File(filename).GetSize();
    }

    Uint8 KT_API*  File::RawContent( const std::string& filename, Uint32* read )
    {
        File readFile(filename);
        Uint32 size = readFile.GetSize();
        Uint8* buff = new Uint8[size];
        readFile.RawContent(buff);

        *read = size;
        return buff;
    }

    bool KT_API File::Rename( const std::string& oldName, const std::string& newName )
    {
        return rename( oldName.c_str(), newName.c_str() ) == 0 ? true : false;
    }

    bool KT_API File::Remove( const std::string& filename )
    {
        return remove( filename.c_str() ) == 0 ? true : false;
    }

    KT_API File::File( const std::string& filename, Uint32 openingMode ):
     myFile( 0 )
    {
        if( !Open( filename, openingMode ) )
            kTLaunchException( Exception, "Can't load the file " + filename + " (check its existence)!" );
    }

    KT_API File::~File()
    {
        if ( IsOpened() )
            Close();
    }

    bool KT_API File::Open( const std::string& filename, Uint32 openingMode )
    {
        std::string mode;

        myOpeningMode = openingMode;

        if ( myOpeningMode & File::ReadFlag )
        {
            mode = "rb";
            if ( myOpeningMode & File::WriteFlag )
                mode += "+";
        }
        else if ( myOpeningMode & File::WriteFlag )
        {
            mode = "w";
            if ( myOpeningMode & File::ReadFlag )
                mode += "+";
        }
        else if ( myOpeningMode & File::AppendFlag )
        {
            mode = "a";
            if ( myOpeningMode & File::ReadFlag )
                mode += "+";
        }

	    myName = filename;

        return ( myFile = fopen( filename.c_str(), mode.c_str() ) ) ? true : false;
    }

    void KT_API File::Close()
    {
        fclose( reinterpret_cast<FILE*>( myFile ) );
        myFile = 0;
    }

    Int32 KT_API File::Tell() const
    {
        if( IsOpened() )
	        return ftell( reinterpret_cast<FILE*>( myFile ) );
        kTLaunchException( Exception, "Not any file opened" );
    }

    void KT_API File::Seek( File::PositionReferential origin, Int32 offset )
    {
	    Uint32 positionIndicatorLookupTable[] = {
		    SEEK_SET,
		    SEEK_END,
		    SEEK_CUR
	    };

	    fseek( reinterpret_cast<FILE*>( myFile ), offset, positionIndicatorLookupTable[ origin ] );
    }

    Uint32 KT_API File::GetSize()
    {
        if( IsOpened() )
        {
            Int32 pos = Tell();

            Seek( File::FileBegin, 0);
            Int32 beginPos = Tell();

            Seek( File::FileEnd, 0);
            Int32 endPos = Tell();

            Seek( File::FileBegin, pos );

            return endPos - beginPos;
        }
        else
            kTLaunchException( Exception, "Not any file loaded" );

        return 0;
    }

    Uint32 KT_API File::Write( void* bloc, Uint32 elementsSize, Uint32 nbElements )
    {
        return fwrite( bloc, elementsSize, nbElements, reinterpret_cast<FILE*>( myFile ) );
    }

    Uint32 KT_API File::Read( void* bloc, Uint32 elementsSize, Uint32 nbElements )
    {
        return fread( bloc, elementsSize, nbElements, reinterpret_cast<FILE*>( myFile ) );
    }

    void KT_API File::RawContent( Uint8* buffer )
    {
        if( IsOpened() )
        {
            Uint32 size = GetSize();
            Uint32 pos = Tell();
            Seek( File::FileBegin, 0 );
            Read( buffer, sizeof(Uint8), size);
            Seek(File::FileBegin, pos);
        }
        else
            kTLaunchException( Exception, "Not any file loaded" );
    }
}