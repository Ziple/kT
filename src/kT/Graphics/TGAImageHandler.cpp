#include "TGAImageHandler.hpp"

#include <kT/Graphics/Image.hpp>
#include <kT/Core/Types.hpp>

#include <cstdio>
#include <cstdlib>

namespace kT
{
    #pragma pack(push, 1)
    /* tga header */
    typedef struct tga_header
    {
        Uint8   id_lenght;          /* size of image id */
        Uint8   colormap_type;      /* 1 is has a colormap */
        Uint8   image_type;         /* compression type */

        Int16   cm_first_entry;     /* colormap origin */
        Int16   cm_length;          /* colormap length */
        Uint8   cm_size;            /* colormap size */

        Int16   x_origin;           /* bottom left x coord origin */
        Int16   y_origin;           /* bottom left y coord origin */

        Int16   width;              /* picture width (in pixels) */
        Int16   height;             /* picture height (in pixels) */

        Uint8   pixel_depth;        /* bits per pixel: 8, 16, 24 or 32 */
        Uint8   image_descriptor;   /* 24 bits = 0x00; 32 bits = 0x80 */

    } tga_header_t;
    #pragma pack(pop)

    static void GetImageInfo( tga_header_t *header, Image* image )
    {
        image->Width = header->width;
        image->Height = header->height;

        switch( header->image_type )
        {
            case 3:
            case 11:
            {
                if( header->pixel_depth == 8 )
                    image->Format = PixelFormat::R8_UINT;
                else
                    image->Format = PixelFormat::R16_UINT;

                break;
            }

            case 1:
            case 2:
            case 9:
            case 10:
            {
                image->Format = PixelFormat::RGBA8_UINT;
                break;
            }
        }
    }

    static void ReadTGA32bits( FILE *fp, Image* image )
    {
        for( Uint32 i = 0; i < image->Width * image->Height; i++ )
        {
            /* lecture et conversion de BVR en RVB */
            image->Data[ (i * 3) + 2 ] = fgetc( fp );
            image->Data[ (i * 3) + 1 ] = fgetc( fp );
            image->Data[ (i * 3) + 0 ] = fgetc( fp );
            image->Data[ (i * 3) + 3 ] = fgetc( fp );
        }
    }

    static void ReadTGA24bits( FILE *fp, Image* image )
    {
        for( Uint32 i = 0; i < image->Width * image->Height; i++ )
        {
            /* lecture et conversion de BVR en RVB */
            image->Data[ (i * 4) + 2 ] = fgetc( fp );
            image->Data[ (i * 4) + 1 ] = fgetc( fp );
            image->Data[ (i * 4) + 0 ] = fgetc( fp );
            image->Data[ (i * 4) + 3 ] = 255;
        }
    }

    static void ReadTGA16bits( FILE *fp, Image* image )
    {
        for( Uint32 i = 0; i < image->Width * image->Height; i++ )
        {
            Uint16 color = fgetc( fp ) + (fgetc( fp ) << 8);

            /* lecture et conversion de BVR en RVB */
            image->Data[ (i * 4) + 2 ] = static_cast<Uint8>( (color & 0x001f) >> 0 ) << 3;
            image->Data[ (i * 4) + 1 ] = static_cast<Uint8>( (color & 0x03E0) >> 5 ) << 3;
            image->Data[ (i * 4) + 0 ] = static_cast<Uint8>( (color & 0x7C00) >> 10 ) << 3;
            image->Data[ (i * 4) + 3 ] = 255;
        }
    }

    static void ReadTGA8bits( FILE *fp, Uint8* colormap, Image* image )
    {
        for( Uint32 i = 0; i < image->Width * image->Height; i++ )
        {
            Uint8 color = fgetc( fp );

            /* lecture et conversion de BVR en RVB */
            image->Data[ (i * 4) + 2 ] = colormap[ color * 3 + 0 ];
            image->Data[ (i * 4) + 1 ] = colormap[ color * 3 + 1 ];
            image->Data[ (i * 4) + 0 ] = colormap[ color * 3 + 2 ];
            image->Data[ (i * 4) + 3 ] = 255;
        }
    }

    static void ReadTGAgray8bits( FILE *fp, Image* image )
    {
        fread( image->Data, sizeof(Uint8), image->Width * image->Height, fp );
    }

    static void ReadTGAgray16bits( FILE *fp, Image* image )
    {
        fread( image->Data, sizeof(Uint8), image->Width * image->Height * 2, fp );
    }

    static void ReadTGA32bitsRLE( FILE* fp, Image* image )
    {
        Uint8* ptr = image->Data;
        Uint8* dataEnd = ptr + image->Width * image->Height * 4;

        while( ptr < dataEnd )
        {
            Uint8 packet = fgetc( fp );

            Uint8 size = 1 + (packet & 0x7F);

            // pixels semblables
            if( packet & 0x80 )
            {
                Uint8 color[4];
                color[2] = fgetc( fp );
                color[1] = fgetc( fp );
                color[0] = fgetc( fp );
                color[3] = fgetc( fp );

                for( Uint8 i = 0; i < size; i++ )
                {
                    ptr[ i * 4 + 0 ] = color[0];
                    ptr[ i * 4 + 1 ] = color[1];
                    ptr[ i * 4 + 2 ] = color[2];
                    ptr[ i * 4 + 3 ] = color[3];
                }
            }
            else
            {
                for( Uint8 i = 0; i < size; i++ )
                {
                    ptr[ i * 4 + 2 ] = fgetc( fp );
                    ptr[ i * 4 + 1 ] = fgetc( fp );
                    ptr[ i * 4 + 0 ] = fgetc( fp );
                    ptr[ i * 4 + 3 ] = fgetc( fp );
                }
            }

            ptr += size * 4;
        }
    }

    static void ReadTGA24bitsRLE( FILE* fp, Image* image )
    {
        Uint8* ptr = image->Data;
        Uint8* dataEnd = ptr + image->Width * image->Height * 4;

        while( ptr < dataEnd )
        {
            Uint8 packet = fgetc( fp );

            Uint8 size = 1 + (packet & 0x7F);

            // pixels semblables
            if( packet & 0x80 )
            {
                Uint8 color[3];
                color[2] = fgetc( fp );
                color[1] = fgetc( fp );
                color[0] = fgetc( fp );

                for( Uint8 i = 0; i < size; i++ )
                {
                    ptr[ i * 4 + 0 ] = color[0];
                    ptr[ i * 4 + 1 ] = color[1];
                    ptr[ i * 4 + 2 ] = color[2];
                    ptr[ i * 4 + 3 ] = 255;
                }
            }
            else
            {
                for( Uint8 i = 0; i < size; i++ )
                {
                    ptr[ i * 4 + 2 ] = fgetc( fp );
                    ptr[ i * 4 + 1 ] = fgetc( fp );
                    ptr[ i * 4 + 0 ] = fgetc( fp );
                    ptr[ i * 4 + 3 ] = 255;
                }
            }

            ptr += size * 4;
        }
    }

    static void ReadTGA16bitsRLE( FILE* fp, Image* image )
    {
        Uint8* ptr = image->Data;
        Uint8* dataEnd = ptr + image->Width * image->Height * 4;

        while( ptr < dataEnd )
        {
            Uint8 packet = fgetc( fp );

            Uint8 size = 1 + (packet & 0x7F);

            // pixels semblables
            if( packet & 0x80 )
            {
                Uint16 packedColor = fgetc( fp ) + (fgetc( fp ) << 8);
                Uint8 color[3];
                color[0] = static_cast<Uint8>( (packedColor & 0x7C00) >> 10) << 3;
                color[1] = static_cast<Uint8>( (packedColor & 0x03E0) >> 5 ) << 3;
                color[2] = static_cast<Uint8>( (packedColor & 0x001f) >> 0 ) << 3;

                for( Uint8 i = 0; i < size; i++ )
                {
                    ptr[ i * 4 + 0 ] = color[0];
                    ptr[ i * 4 + 1 ] = color[1];
                    ptr[ i * 4 + 2 ] = color[2];
                    ptr[ i * 4 + 3 ] = 255;
                }
            }
            else
            {
                for( Uint8 i = 0; i < size; i++ )
                {
                    Uint16 packedColor = fgetc( fp ) + (fgetc( fp ) << 8);
                    ptr[ i * 4 + 0 ] = static_cast<Uint8>( (packedColor & 0x7C00) >> 10) << 3;
                    ptr[ i * 4 + 1 ] = static_cast<Uint8>( (packedColor & 0x03E0) >> 5 ) << 3;
                    ptr[ i * 4 + 2 ] = static_cast<Uint8>( (packedColor & 0x001f) >> 0 ) << 3;
                    ptr[ i * 4 + 3 ] = 255;
                }
            }

            ptr += size * 4;
        }
    }

    static void ReadTGA8bitsRLE( FILE* fp, Uint8* colormap, Image* image )
    {
        Uint8* ptr = image->Data;
        Uint8* dataEnd = ptr + image->Width * image->Height * 4;

        while( ptr < dataEnd )
        {
            Uint8 packet = fgetc( fp );

            Uint8 size = 1 + (packet & 0x7F);

            // pixels semblables
            if( packet & 0x80 )
            {
                Uint8 index = fgetc( fp );
                for( Uint8 i = 0; i < size; i++ )
                {
                    ptr[ i * 4 + 0 ] = colormap[ index * 3 + 2 ];
                    ptr[ i * 4 + 1 ] = colormap[ index * 3 + 1 ];
                    ptr[ i * 4 +  2 ] = colormap[ index * 3 + 0 ];
                    ptr[ i * 4 + 3 ] = 255;
                }
            }
            else
            {
                for( Uint8 i = 0; i < size; i++ )
                {
                    Uint8 index = fgetc( fp );
                    ptr[ i * 4 + 0 ] = colormap[ index * 3 + 2 ];
                    ptr[ i * 4 + 1 ] = colormap[ index * 3 + 1 ];
                    ptr[ i * 4 + 2 ] = colormap[ index * 3 + 0 ];
                    ptr[ i * 4 + 3 ] = 255;
                }
            }

            ptr += size * 4;
        }
    }

    static void ReadTGAgray16bitsRLE( FILE* fp, Image* image )
    {
        Uint8* ptr = image->Data;
        Uint8* dataEnd = ptr + image->Width * image->Height * 2;

        while( ptr < dataEnd )
        {
            Uint8 packet = fgetc( fp );

            Uint8 size = 1 + (packet & 0x7F);

            // pixels semblables
            if( packet & 0x80 )
            {
                Uint8 gray[2];
                gray[0] = fgetc( fp );
                gray[1] = fgetc( fp );

                for( Uint8 i = 0; i < size; i++ )
                {
                    ptr[ i * 2 + 0 ] = gray[0];
                    ptr[ i * 2 + 1 ] = gray[1];
                }
            }
            else
            {
                for( Uint8 i = 0; i < size; i++ )
                {
                    ptr[ i * 2 + 0 ] = fgetc( fp );
                    ptr[ i * 2 + 1 ] = fgetc( fp );
                }
            }

            ptr += size * 2;
        }
    }

    static void ReadTGAgray8bitsRLE( FILE* fp, Image* image )
    {
        Uint8* ptr = image->Data;
        Uint8* dataEnd = ptr + image->Width * image->Height;

        while( ptr < dataEnd )
        {
            Uint8 packet = fgetc( fp );

            Uint8 size = 1 + (packet & 0x7F);

            // pixels semblables
            if( packet & 0x80 )
            {
                Uint8 gray = fgetc( fp );
                for( Uint8 i = 0; i < size; i++ )
                    ptr[i] = gray;
            }
            else
            {
                for( Uint8 i = 0; i < size; i++ )
                    ptr[i] = fgetc( fp );
            }

            ptr += size;
        }
    }

    Image* TGAImageHandler::LoadFromFile( const std::string& filename )
    {
        Image* image = new Image();

        FILE *fp;
        tga_header_t header;
        Uint8 *colormap = NULL;

        fp = fopen( filename.c_str(), "rb" );
        if( !fp ) {
            /* erreur ! */
            return 0;
        }

        /* lecture de l'en-tête */
        fread( &header, sizeof( tga_header_t ), 1, fp );
        GetImageInfo( &header, image);
        fseek( fp, header.id_lenght, SEEK_CUR );

        /* lecture de la palette... */
        if( header.colormap_type )
        {
            /* palette BVR */
            colormap = (Uint8*)malloc( sizeof( Uint8 ) * header.cm_length * (header.cm_size >> 3));
            fread( colormap, sizeof( Uint8 ), header.cm_length * (header.cm_size >> 3), fp );
        }
        /* allocations mémoire nécessaires... */
        image->Data = new Uint8[ image->Width * image->Height * PixelUtility::GetPixelFormatDescriptor( image->Format ).GetSize() ];
        if( !image->Data )
            return 0;
        /* lecture des données pixels de l'image... */
        switch( header.image_type )
        {
            case 1:
            {
                ReadTGA8bits( fp, colormap, image );
                break;
            }
            case 2:
            {
                if( header.pixel_depth == 16 )
                    ReadTGA16bits( fp, image );
                else if( header.pixel_depth == 24 )
                    ReadTGA24bits( fp, image );
                else
                    ReadTGA32bits( fp, image );

                break;
            }
            case 3:
            {
                if( header.pixel_depth == 8 )
                    ReadTGAgray8bits( fp, image );
                else
                    ReadTGAgray16bits( fp, image );

                break;
            }
            case 9:
            {
                ReadTGA8bitsRLE( fp, colormap, image );
                break;
            }
            case 10:
            {
                if( header.pixel_depth == 16 )
                    ReadTGA16bitsRLE( fp, image );
                else if( header.pixel_depth == 24 )
                    ReadTGA24bitsRLE( fp, image );
                else
                    ReadTGA32bitsRLE( fp, image );

                break;
            }
            case 11:
            {
                if( header.pixel_depth == 8 )
                    ReadTGAgray8bitsRLE( fp, image );
                else
                    ReadTGAgray16bitsRLE( fp, image );

                break;
            }
        }
        /* désallocations mémoire nécessaires... */
        if( header.colormap_type )
            free( colormap );

        fclose( fp );
        return image;
    }
}
