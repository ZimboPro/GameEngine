#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include <vector>

namespace GameEngine
{
    namespace graphics
    {
        class Font;

        class FontManager
        {
            public:
                static void Add(Font * font);
                static void clean();
                static Font * get(const std::string & name);
                static Font * get(const std::string & name, unsigned int size);
            private:
                FontManager();
                ~FontManager();

                static std::vector<Font *> _fonts;
        };
    }
}

#endif