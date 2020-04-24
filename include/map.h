#pragma once

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

    Map(unsigned int width, unsigned int height, const std::string& data);

private:
    std::vector<Tile> tiles;
    unsigned int width;
    unsigned int height;
};
