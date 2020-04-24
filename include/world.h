#pragma once

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

    ~World();

private:
    Map map;
    std::vector<Building> buildings;
    std::vector<ItemStack> itemStacks;
};
