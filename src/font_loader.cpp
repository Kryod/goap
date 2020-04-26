#include "font_loader.h"
#include "cute_files.h"
#include "m_assert.h"
#include "utils.h"

FontLoader::FontLoader() {
    std::vector<std::string> fontPaths;
    Utils::listFiles("resources/fonts", { ".ttf" }, fontPaths);

    for (const std::string& path : fontPaths) {
        std::string fileName = path.substr(0, path.find_last_of('.'));
        this->fonts[fileName] = sf::Font();
        this->fonts[fileName].loadFromFile(path);
    }
}

FontLoader& FontLoader::instance() {
    static FontLoader instance;
    return instance;
}

const sf::Font* FontLoader::get(const std::string& name) const {
    std::string key = "resources/fonts/" + name;
    M_ASSERT(this->fonts.find(key) != this->fonts.end(),
             "Font \"" + key + "\" not found");
    return &this->fonts.at(key);
}
