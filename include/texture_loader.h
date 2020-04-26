#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TextureLoader {
public:
    TextureLoader();
    static TextureLoader& instance();
    const sf::Texture* get(const std::string& name) const;

private:
    std::vector<std::string> listTextures(const std::string& rootDir);

    std::map<std::string, sf::Texture> textures;
};
