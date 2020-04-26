#include <vector>

#include "cute_files.h"
#include "m_assert.h"
#include "texture_loader.h"
#include "utils.h"

TextureLoader::TextureLoader() {
    std::vector<std::string> texturePaths;
    Utils::listFiles("resources/textures", { ".png" }, texturePaths);

    for (const std::string& path : texturePaths) {
        std::string fileName = path.substr(0, path.find_last_of('.'));
        this->textures[fileName] = sf::Texture();
        this->textures[fileName].setSmooth(false);
        this->textures[fileName].loadFromFile(path);
    }
}

TextureLoader& TextureLoader::instance() {
    static TextureLoader instance;
    return instance;
}

const sf::Texture* TextureLoader::get(const std::string& name) const {
    std::string key = "resources/textures/" + name;
    M_ASSERT(this->textures.find(key) != this->textures.end(),
             "Texture \"" + key + "\" not found");
    return &this->textures.at(key);
}
