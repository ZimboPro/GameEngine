#include <utils/Times.hpp>
#include <utils/ImageLoad.hpp>

namespace GameEngine
{
    BYTE * load_image(const char * filename, unsigned int & width, unsigned int & height)
    {
        FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
        FIBITMAP *dib = nullptr;
        
        fif = FreeImage_GetFileType(filename, 0);
        if(fif == FIF_UNKNOWN) 
            fif = FreeImage_GetFIFFromFilename(filename);
        if(fif == FIF_UNKNOWN)
            return nullptr;

        if(FreeImage_FIFSupportsReading(fif))
            dib = FreeImage_Load(fif, filename);
        if(!dib)
            return nullptr;

        BYTE * pixels = FreeImage_GetBits(dib);
        width = FreeImage_GetWidth(dib);
        height = FreeImage_GetHeight(dib);

        unsigned int bpp = FreeImage_GetBPP(dib);

        unsigned int size = width * height * (bpp >> 3);
        BYTE *bits = new BYTE[size];
        memcpy(bits, pixels, size);

        FreeImage_Unload(dib);
        return bits;
    }
}