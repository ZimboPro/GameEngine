#ifndef IMAGELOAD_HPP
#define IMAGELOAD_HPP

#include <FreeImage.h>
#include <string>

namespace GameEngine
{
    static BYTE * load_image(const char * path, unsigned int & width, unsigned int & height);
}
#endif