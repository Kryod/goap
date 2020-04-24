#include "map.h"

Map::Map(unsigned int width, unsigned int height, const std::string& data)
    : width(width), height(height) {

    unsigned int size = width * height;
    this->tiles.reserve(size);

    for (unsigned int i = 0; i < size; ++i) {
        char tileChar = data.at(i);
        Map::Tile::Type t = static_cast<Map::Tile::Type>(tileChar - '0');

        this->tiles.emplace_back(t);
    }
}

Map::Tile::Tile(Map::Tile::Type type) : type(type) {}
