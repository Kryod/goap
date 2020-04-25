#include "map.h"
#include "texture_loader.h"

Map::Map(unsigned int width, unsigned int height, const std::string& data)
    : width(width), height(height) {
    TextureLoader& tl = TextureLoader::instance();

    this->sprites[Tile::Type::Dirt] = sf::Sprite(*tl.get("tile/medievalTile_01"));
    this->sprites[Tile::Type::Grass] = sf::Sprite(*tl.get("tile/medievalTile_57"));
    this->sprites[Tile::Type::PavedFloor] = sf::Sprite(*tl.get("tile/medievalTile_15"));
    this->sprites[Tile::Type::Water] = sf::Sprite(*tl.get("tile/medievalTile_27"));

    unsigned int size = width * height;
    this->tiles.reserve(size);

    for (unsigned int i = 0; i < size; ++i) {
        char tileChar = data.at(i);
        Map::Tile::Type t = static_cast<Map::Tile::Type>(tileChar - '0');

        this->tiles.emplace_back(t);
    }
}

void Map::draw(sf::RenderTarget& target) const {}

Map::Tile::Tile(Map::Tile::Type type) : type(type) {}
