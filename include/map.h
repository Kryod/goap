#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>

class Map {
public:
    struct Tile {
        enum Type {
            Dirt = 0,
            Grass,
            PavedFloor,
            Water,
        };

        Tile(Type type);

        Type type;
    };

    /**
     * ### Brief
     * Instaciate a Map
     *
     * ### Param
     * **width** width of the map
     * **height** height of the map
     * **data** representation of the map with each number corresponding to a
     * `Tile`
     *
     * ### Return
     * An instance of a Map
     */
    Map(unsigned int width, unsigned int height, const std::string& data);

    void draw(sf::RenderTarget& target);

private:
    std::vector<Tile> tiles;
    std::map<Tile::Type, sf::Sprite> sprites;
    unsigned int width;
    unsigned int height;
};
