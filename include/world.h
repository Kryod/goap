#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <unordered_set>

#include "building.h"
#include "item_stack.h"
#include "map.h"

class World {
public:
    World(Map& map);

    static World* instance;
    static std::map<std::string, Item> itemTypes;
    static std::map<Item, std::string> stateMap;

    void addItemStack(const ItemStack& itemStack);
    ItemStack* getNearestItemStack(const Item item, const sf::Vector2f& pos) const;
    ItemStack* findItem(Item type);

    std::unordered_set<std::string> getState() const;
    void draw(sf::RenderTarget& target);

private:
    Map map;
    std::vector<Building> buildings;
    std::vector<ItemStack> itemStacks;
    std::map<Item, sf::Sprite> itemSprites;
};
