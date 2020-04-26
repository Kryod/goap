#include "ui.h"
#include "font_loader.h"
#include "texture_loader.h"

void Ui::draw(sf::RenderTarget& target, const sf::View& view) {
    sf::Vector2f pos(view.getSize().x -
                         this->middleMouse.getGlobalBounds().width -
                         this->mouseControlText.getGlobalBounds().width - 12,
                     8.0f);
    this->middleMouse.setPosition(pos);
    target.draw(this->middleMouse);
    pos.x += this->middleMouse.getGlobalBounds().width;
    this->mouseControlText.setPosition(pos);
    target.draw(this->mouseControlText);
}

Ui::Ui()
    : middleMouse(*TextureLoader::instance().get("ui/mouse_middle")),
      mouseControlText("Pan / Zoom", *FontLoader::instance().get("FrizQuadrataTT")) {

    this->middleMouse.setScale(0.5f, 0.5f);
    this->mouseControlText.setFillColor(sf::Color::Black);
}
