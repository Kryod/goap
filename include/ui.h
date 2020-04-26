#pragma once

#include <SFML/Graphics.hpp>

class Ui {
public:
    Ui();
    void draw(sf::RenderTarget& target, const sf::View& view);

private:
    sf::Sprite middleMouse;
    sf::Text mouseControlText;
};
