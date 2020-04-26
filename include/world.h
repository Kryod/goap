#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

#include "building.h"
#include "item_stack.h"
#include "map.h"

class World {
public:
    World(Map& map);

    static World* instance;

    void addItemStack(const ItemStack& itemStack);
    ItemStack* findItem(Item type);

    void draw(sf::RenderTarget& target);

private:
    Map map;
    std::vector<Building> buildings;
    std::vector<ItemStack> itemStacks;
    std::map<Item, sf::Sprite> itemSprites;
};
