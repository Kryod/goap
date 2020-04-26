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
    ItemStack* getNearestItemStack(const Item item, const sf::Vector2f& pos);
    ItemStack* findItem(Item type);
    float distance(sf::Vector2f p1, sf::Vector2f p2) const;

    std::unordered_set<std::string> getState() const;
    void draw(sf::RenderTarget& target);

private:
    Map map;
    std::vector<Building> buildings;
    std::vector<ItemStack> itemStacks;
    std::map<Item, sf::Sprite> itemSprites;
};
