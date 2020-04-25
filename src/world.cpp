#include "world.h"

World::World(Map& map) : map(map) {}

World* World::instance = nullptr;

void World::addItemStack(const ItemStack& itemStack) {
    this->itemStacks.emplace_back(itemStack);
}

ItemStack* World::findItem(Item type) {
    for (ItemStack& stack : this->itemStacks) {
        if (stack.getItem() == type) {
            return &stack;
        }
    }
    return nullptr;
}

Map& World::getMap() { return this->map; }
