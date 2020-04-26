#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class FontLoader {
public:
    FontLoader();
    static FontLoader& instance();
    const sf::Font* get(const std::string& name) const;

private:
    std::map<std::string, sf::Font> fonts;
};
