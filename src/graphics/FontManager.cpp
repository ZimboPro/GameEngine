#include <graphics/FontManager.hpp>
#include <graphics/Font.hpp>

namespace GameEngine
{
    namespace graphics
    {
        std::vector<Font *> FontManager::_fonts;

        FontManager::FontManager()
        {}

        FontManager::~FontManager()
        {
            clean();
        }

        void FontManager::Add(Font * font)
        {
            _fonts.push_back(font);
        }

        void FontManager::clean()
        {
            for (size_t i = 0; i < _fonts.size(); i++)
                delete _fonts[i];
            _fonts.clear();
        }

        Font * FontManager::get(const std::string & name)
        {
            for (Font * font : _fonts)
            {
                if (font->FileName() == name)
                    return font;
            }
            return nullptr;
        }

        Font * FontManager::get(const std::string & name, unsigned int size)
        {
            for (Font * font : _fonts)
            {
                if (font->Size() == size && font->FileName() == name)
                    return font;
            }
            return nullptr;
        }
    }
}