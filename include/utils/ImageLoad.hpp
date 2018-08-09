#ifndef IMAGELOAD_HPP
#define IMAGELOAD_HPP

#include <string>
#include <FreeImage.h>

namespace GameEngine
{
    static BYTE * load_image(const char * path, unsigned int & width, unsigned int & height);
}
#endif